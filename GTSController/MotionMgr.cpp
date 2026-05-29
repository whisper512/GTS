#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMessageBox>
#include <QCoreApplication>
#include "TotalMgr.h"
#include "MotionMgr.h"


MotionMgr::MotionMgr(CTotalMgr* totalMgr, QObject* parent)
    : QObject(parent)
    , m_pTotalMgr(totalMgr)
{
}


MotionMgr::~MotionMgr() {
    
}

bool MotionMgr::setAxisMotionMode(short axis, short mode)
{
    if (!checkProfile(axis)) return false;
    if (mode == 0) {
        // 点位运动模式 (Trap)
        return setTrapMode(axis);
    }
    else if (mode == 1) {
        // Jog 持续运动模式
        return setJogMode(axis);
    }
    else {
        // 无效模式
        m_lastError = -1;
        emit errorOccurred(axis, m_lastError, QStringLiteral("无效的运动模式: %1 (仅支持 0=点位, 1=Jog)").arg(mode));
        return false;
    }
}

void MotionMgr::getAxisMotionInfo(std::vector<stuAxis>& vecAxis)
{
    for (auto& axis : vecAxis) {
        short axisIndex = axis.axisIndex;           // 轴号 1~4
        axis.dPrfPos = axisProfilePos(axisIndex);   // 规划位置
        axis.dPrfVel = axisProfileVel(axisIndex);   // 规划速度
        axis.dPrfAcc = axisProfileAcc(axisIndex);   // 规划加速度
    }
}

void MotionMgr::getCommonMotionInfo(std::vector<stuAxis>& vecAxis)
{
    for (auto& axis : vecAxis) {
        short profile = axis.axisIndex;           // 轴号 1-4
        axis.dMotionVel = targetVel(profile);     // 运动速度
        axis.lPrfMode = profileMode(profile);     // 运动模式
    }
}

bool MotionMgr::setCommonParam(short axisId)
{
    if (!checkProfile(axisId)) return false;
    int idx = axisId - 1;
    stuAxis* pAxis = m_pTotalMgr->getAxisRef(idx);
    if (!pAxis) return false;
    // 通用参数：写入运动速度
    if (!setTargetVel(axisId, pAxis->dMotionVel)) {
        return false;
    }
    return true;
}

void MotionMgr::getTrapMotionInfo(std::vector<stuAxis>& vecTrap)
{
    for (auto& axis : vecTrap) {
        short profile = axis.axisIndex;  // 轴号 1-4
        TTrapPrm prm;
        if (getTrapParams(profile, prm)) {
            // 从 TTrapPrm 读取
            axis.trapParam.acc = prm.acc;                       // 加速度
            axis.trapParam.dec = prm.dec;                       // 减速度
            axis.trapParam.somoothTime = prm.smoothTime;        // 平滑时间
        }
    }
}

bool MotionMgr::setTrapParam(short axisId, const stuTrapParam& param)
{
    if (!checkProfile(axisId)) return false;
    TTrapPrm prm;
    prm.acc = param.acc;                 // 加速度
    prm.dec = param.dec;                 // 减速度
    prm.smoothTime = param.somoothTime;  // 平滑时间
    if (!setTrapParams(axisId, prm)) {
        return false;
    }

    return true;
}

bool MotionMgr::startTrapMotion(short profile, long stepSize)
{
    if (!checkProfile(profile)) return false;

    int idx = profile - 1;
    stuAxis* pAxis = m_pTotalMgr->getAxisRef(idx);
    if (!pAxis) return false;

    const stuTrapParam& trap = pAxis->trapParam;

    // 单次模式（cycleTimes <= 0）
    if (trap.cycleTimes <= 0) {
        return singleTrapMotion(profile, stepSize, trap.acc, trap.dec, trap.somoothTime, pAxis->dMotionVel);
    }

    // 循环模式
    long currentStep = stepSize;  // 第一次为正方向
    int times = trap.cycleTimes;

    for (int i = 0; i < times; ++i) {
        // 正方向运动
        if (!singleTrapMotion(profile, currentStep, trap.acc, trap.dec, trap.somoothTime, pAxis->dMotionVel))
            return false;
        // 等待运动完成
        waitMotionDone(profile);
        // 到位延时
        if (trap.Delay > 0) {
            GtsHal::delay(static_cast<unsigned short>(trap.Delay));
        }
        // 反方向运动（步长取反）
        if (!singleTrapMotion(profile, -currentStep, trap.acc, trap.dec, trap.somoothTime, pAxis->dMotionVel))
            return false;
        // 等待运动完成
        waitMotionDone(profile);

        // 到位延时
        if (trap.Delay > 0) {
            GtsHal::delay(static_cast<unsigned short>(trap.Delay));
        }
    }
    return true;
}

void MotionMgr::getJogMotionInfo(std::vector<stuAxis>& vecAxis)
{
    for (auto& axis : vecAxis) {
        short profile = axis.axisIndex;  // 轴号 1-4
        TJogPrm prm;
        if (getJogParams(profile, prm)) {
            // 从 TJogPrm 映射到 stuJobParam
            axis.jogParam.acc = prm.acc;          // 加速度
            axis.jogParam.dec = prm.dec;          // 减速度
        }
    }
}
bool MotionMgr::setJogParam(short axisId, const stuJobParam& param)
{
    if (!checkProfile(axisId)) return false;
    // 构造 TJogPrm，从 stuJobParam 映射
    TJogPrm prm;
    prm.acc = param.acc;     // 加速度
    prm.dec = param.dec;     // 减速度
    prm.smooth = 0.0;        // 平滑时间，参考 trap 给默认值 0
    // 写入板卡
    if (!setJogParams(axisId, prm)) {
        return false;
    }

    return true;
}

bool MotionMgr::startJogMotion(short profile, short direction)
{
    if (!checkProfile(profile)) return false;

    int idx = profile - 1;
    stuAxis* pAxis = m_pTotalMgr->getAxisRef(idx);
    if (!pAxis) return false;

    const stuJobParam& jog = pAxis->jogParam;

    // 设置为 Jog 模式
    m_lastError = GtsHal::prfJog(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置 Jog 参数 (acc, dec, smooth)
    TJogPrm prm;
    prm.acc = jog.acc;
    prm.dec = jog.dec;
    prm.smooth = 0.0;
    m_lastError = GtsHal::setJogPrm(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置速度（方向：正方向 vel > 0，反方向 vel < 0）
    double targetVel = (direction > 0) ? pAxis->dMotionVel: -pAxis->dMotionVel;
    m_lastError = GtsHal::setVel(profile, targetVel);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 启动运动
    long mask = 1L << (profile - 1);
    m_lastError = GtsHal::update(mask);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    return true;
}


bool MotionMgr::checkProfile(short profile) const
{
    if (profile < 1 || profile > m_axisCount) {
        return false;
    }
    return true;
}

// 抽取的单次运动函数
bool MotionMgr::singleTrapMotion(short profile, long stepSize, double acc, double dec, int smoothTime, double vel)
{
    // 设为点位模式
    m_lastError = GtsHal::prfTrap(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    // 设置梯形参数
    TTrapPrm prm = {};
    prm.acc = acc;
    prm.dec = dec;
    prm.smoothTime = static_cast<short>(smoothTime);
    m_lastError = GtsHal::setTrapPrm(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 目标位置 = 当前位置 + 步长
    double curPos = profilePos(profile);
    long targetPos = static_cast<long>(curPos) + stepSize;
    m_lastError = GtsHal::setPos(profile, targetPos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置速度
    m_lastError = GtsHal::setVel(profile, vel);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 启动运动
    long mask = 1L << (profile - 1);
    m_lastError = GtsHal::update(mask);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    return true;
}

// 等待运动完成（规划停止 bit10 = 0x400）
void MotionMgr::waitMotionDone(short profile)
{
    long sts = 0;
    do {
        GtsHal::getSts(profile, &sts);
        QCoreApplication::processEvents();  // 保持界面响应
    } while (sts & 0x400);  // 0x400 = 规划中，运动未完成
}


bool MotionMgr::setProfilePos(short profile, long pos) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPrfPos(profile, pos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

double MotionMgr::profilePos(short profile) const {
    if (!checkProfile(profile)) return 0.0;
    double pos = 0.0;
    GtsHal::getPrfPos(profile, &pos);
    return pos;
}

double MotionMgr::profileVel(short profile) const {
    if (!checkProfile(profile)) return 0.0;
    double vel = 0.0;
    GtsHal::getPrfVel(profile, &vel);
    return vel;
}

double MotionMgr::profileAcc(short profile) const {
    if (!checkProfile(profile)) return 0.0;
    double acc = 0.0;
    GtsHal::getPrfAcc(profile, &acc);
    return acc;
}

long MotionMgr::profileMode(short profile) const {
    if (!checkProfile(profile)) return -1;
    long mode = 0;
    GtsHal::getPrfMode(profile, &mode);
    return mode;
}

double MotionMgr::axisProfilePos(short axis) const {
    if (!checkProfile(axis)) return 0.0;
    double pos = 0.0;
    GtsHal::getAxisPrfPos(axis, &pos);
    return pos;
}

double MotionMgr::axisProfileVel(short axis) const {
    if (!checkProfile(axis)) return 0.0;
    double vel = 0.0;
    GtsHal::getAxisPrfVel(axis, &vel);
    return vel;
}

double MotionMgr::axisProfileAcc(short axis) const {
    if (!checkProfile(axis)) return 0.0;
    double acc = 0.0;
    GtsHal::getAxisPrfAcc(axis, &acc);
    return acc;
}

bool MotionMgr::setTargetPos(short profile, long pos) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPos(profile, pos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setTargetVel(short profile, double vel) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setVel(profile, vel);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

long MotionMgr::targetPos(short profile) const {
    if (!checkProfile(profile)) return 0;
    long pos = 0;
    GtsHal::getPos(profile, &pos);
    return pos;
}

double MotionMgr::targetVel(short profile) const {
    if (!checkProfile(profile)) return 0.0;
    double vel = 0.0;
    GtsHal::getVel(profile, &vel);
    return vel;
}

bool MotionMgr::update(long mask) {
    m_lastError = GtsHal::update(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setProfileScale(short axis, long alpha, long beta) {
    if (!checkProfile(axis)) return false;
    m_lastError = GtsHal::setProfileScale(axis, alpha, beta);
    return m_lastError == 0;
}

bool MotionMgr::getProfileScale(short axis, long& alpha, long& beta) const {
    if (!checkProfile(axis)) return false;
    m_lastError = GtsHal::getProfileScale(axis, &alpha, &beta);
    return m_lastError == 0;
}


bool MotionMgr::setTrapMode(short profile) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfTrap(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setTrapParams(short profile, const TTrapPrm& prm) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setTrapPrm(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getTrapParams(short profile, TTrapPrm& prm) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getTrapPrm(profile, &prm);
    return m_lastError == 0;
}

bool MotionMgr::getTrapTime(short profile, TTrapTime& time) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getTrapTime(profile, &time);
    return m_lastError == 0;
}


bool MotionMgr::setJogMode(short profile) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfJog(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setJogParams(short profile, const TJogPrm& prm) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setJogPrm(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getJogParams(short profile, TJogPrm& prm) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getJogPrm(profile, &prm);
    return m_lastError == 0;
}


bool MotionMgr::moveAbsolute(short profile, long pos, double vel, double acc, double dec) {
    if (!checkProfile(profile)) return false;

    TMoveAbsolutePrm prm;
    prm.pos = pos;
    prm.vel = vel;
    prm.acc = acc;
    prm.dec = dec;

    m_lastError = GtsHal::moveAbsolute(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::moveVelocity(short profile, double vel, double acc) {
    if (!checkProfile(profile)) return false;

    TMoveVelocityPrm prm;
    prm.vel = vel;
    prm.acc = acc;

    m_lastError = GtsHal::moveVelocity(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getMoveAbsoluteParams(short profile, TMoveAbsolutePrm& prm) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getMoveAbsolute(profile, &prm);
    return m_lastError == 0;
}

bool MotionMgr::getMoveVelocityParams(short profile, TMoveVelocityPrm& prm) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getMoveVelocity(profile, &prm);
    return m_lastError == 0;
}


bool MotionMgr::setPtMode(short profile, short mode) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfPt(profile, mode);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setPtLoop(short profile, long loop) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPtLoop(profile, loop);
    return m_lastError == 0;
}

long MotionMgr::getPtLoop(short profile) const {
    if (!checkProfile(profile)) return 0;
    long loop = 0;
    GtsHal::getPtLoop(profile, &loop);
    return loop;
}

short MotionMgr::ptFreeSpace(short profile, short fifo) const {
    if (!checkProfile(profile)) return -1;
    short space = 0;
    GtsHal::ptSpace(profile, &space, fifo);
    return space;
}

bool MotionMgr::ptAddData(short profile, double pos, long time, short type, short fifo) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptData(profile, pos, time, type, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::ptAddDataWithSeg(short profile, double pos, long time,
    short type, long segNum, short fifo) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptDataWN(profile, pos, time, type, segNum, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::ptClear(short profile, short fifo) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptClear(profile, fifo);
    return m_lastError == 0;
}

bool MotionMgr::ptStart(long mask, long option) {
    m_lastError = GtsHal::ptStart(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setPtMemory(short profile, short memory) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPtMemory(profile, memory);
    return m_lastError == 0;
}

short MotionMgr::getPtMemory(short profile) const {
    if (!checkProfile(profile)) return -1;
    short mem = 0;
    GtsHal::getPtMemory(profile, &mem);
    return mem;
}

long MotionMgr::ptCurrentSegment(short profile) const {
    if (!checkProfile(profile)) return -1;
    long seg = 0;
    GtsHal::ptGetSegNum(profile, &seg);
    return seg;
}

bool MotionMgr::ptAddDoBit(short profile, short doType, short index, short value, short fifo) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptDoBit(profile, doType, index, value, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::ptAddAo(short profile, short aoType, short index, double value, short fifo) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptAo(profile, aoType, index, value, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}


bool MotionMgr::setGearMode(short profile, short dir) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfGear(profile, dir);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setGearMaster(short profile, short masterIndex, short masterType, short masterItem) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setGearMaster(profile, masterIndex, masterType, masterItem);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getGearMaster(short profile, short& masterIndex,
    short& masterType, short& masterItem) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getGearMaster(profile, &masterIndex, &masterType, &masterItem);
    return m_lastError == 0;
}

bool MotionMgr::setGearRatio(short profile, long masterEven, long slaveEven, long masterSlope) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setGearRatio(profile, masterEven, slaveEven, masterSlope);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getGearRatio(short profile, long& masterEven, long& slaveEven, long& masterSlope) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getGearRatio(profile, &masterEven, &slaveEven, &masterSlope);
    return m_lastError == 0;
}

bool MotionMgr::gearStart(long mask) {
    m_lastError = GtsHal::gearStart(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setGearEvent(short profile, short event, long startPara0, long startPara1) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setGearEvent(profile, event, startPara0, startPara1);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getGearEvent(short profile, short& event, long& startPara0, long& startPara1) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getGearEvent(profile, &event, &startPara0, &startPara1);
    return m_lastError == 0;
}


bool MotionMgr::setFollowMode(short profile, short dir) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfFollow(profile, dir);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setFollowMaster(short profile, short masterIndex, short masterType, short masterItem) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowMaster(profile, masterIndex, masterType, masterItem);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getFollowMaster(short profile, short& masterIndex,
    short& masterType, short& masterItem) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getFollowMaster(profile, &masterIndex, &masterType, &masterItem);
    return m_lastError == 0;
}

bool MotionMgr::setFollowLoop(short profile, long loop) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowLoop(profile, loop);
    return m_lastError == 0;
}

long MotionMgr::getFollowLoop(short profile) const {
    if (!checkProfile(profile)) return 0;
    long loop = 0;
    GtsHal::getFollowLoop(profile, &loop);
    return loop;
}

bool MotionMgr::setFollowEvent(short profile, short event, short masterDir, long pos) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowEvent(profile, event, masterDir, pos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getFollowEvent(short profile, short& event, short& masterDir, long& pos) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getFollowEvent(profile, &event, &masterDir, &pos);
    return m_lastError == 0;
}

short MotionMgr::followFreeSpace(short profile, short fifo) const {
    if (!checkProfile(profile)) return -1;
    short space = 0;
    GtsHal::followSpace(profile, &space, fifo);
    return space;
}

bool MotionMgr::followAddData(short profile, long masterSegment, double slaveSegment,
    short type, short fifo) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::followData(profile, masterSegment, slaveSegment, type, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::followClear(short profile, short fifo) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::followClear(profile, fifo);
    return m_lastError == 0;
}

bool MotionMgr::followStart(long mask, long option) {
    m_lastError = GtsHal::followStart(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::followSwitch(long mask) {
    m_lastError = GtsHal::followSwitch(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setFollowMemory(short profile, short memory) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowMemory(profile, memory);
    return m_lastError == 0;
}

short MotionMgr::getFollowMemory(short profile) const {
    if (!checkProfile(profile)) return -1;
    short mem = 0;
    GtsHal::getFollowMemory(profile, &mem);
    return mem;
}

bool MotionMgr::getFollowStatus(short profile, short& fifoNum, short& switchStatus) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getFollowStatus(profile, &fifoNum, &switchStatus);
    return m_lastError == 0;
}


bool MotionMgr::setPvtMode(short profile) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfPvt(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setPvtLoop(short profile, long loop) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPvtLoop(profile, loop);
    return m_lastError == 0;
}

bool MotionMgr::getPvtLoop(short profile, long& loopCount, long& loop) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getPvtLoop(profile, &loopCount, &loop);
    return m_lastError == 0;
}

bool MotionMgr::pvtStatus(short profile, short& tableId, double& time) const {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::pvtStatus(profile, &tableId, &time);
    return m_lastError == 0;
}

bool MotionMgr::pvtTableClear(short tableId) {
    m_lastError = GtsHal::pvtTableClear(tableId);
    return m_lastError == 0;
}

bool MotionMgr::pvtStart(long mask) {
    m_lastError = GtsHal::pvtStart(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSelect(short profile, short tableId) {
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::pvtTableSelect(profile, tableId);
    return m_lastError == 0;
}

bool MotionMgr::pvtTableSet(short tableId, long count, double* time, double* pos, double* vel) {
    m_lastError = GtsHal::pvtTable(tableId, count, time, pos, vel);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSetEx(short tableId, long count, double* time, double* pos,
    double* velBegin, double* velEnd) {
    m_lastError = GtsHal::pvtTableEx(tableId, count, time, pos, velBegin, velEnd);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSetComplete(short tableId, long count, double* time, double* pos,
    double* a, double* b, double* c,
    double velBegin, double velEnd) {
    m_lastError = GtsHal::pvtTableComplete(tableId, count, time, pos, a, b, c, velBegin, velEnd);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSetPercent(short tableId, long count, double* time, double* pos,
    double* percent, double velBegin) {
    m_lastError = GtsHal::pvtTablePercent(tableId, count, time, pos, percent, velBegin);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}


bool MotionMgr::moveTo(short profile, long pos, double vel, double acc, double dec) {
    if (!checkProfile(profile)) return false;

    // 设置梯形模式
    m_lastError = GtsHal::prfTrap(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置梯形参数
    TTrapPrm trapPrm;
    trapPrm.acc = acc;
    trapPrm.dec = dec;
    trapPrm.velStart = 0.0;
    trapPrm.smoothTime = 0.0;

    m_lastError = GtsHal::setTrapPrm(profile, trapPrm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置目标位置和速度
    m_lastError = GtsHal::setPos(profile, pos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    m_lastError = GtsHal::setVel(profile, vel);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 启动运动
    m_lastError = GtsHal::update(1L << profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    emit motionDone(profile);
    return true;
}

bool MotionMgr::jog(short profile, double vel, double acc) {
    if (!checkProfile(profile)) return false;

    // 设置为 Jog 模式
    m_lastError = GtsHal::prfJog(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置 Jog 参数
    TJogPrm jogPrm;
    jogPrm.acc = acc;
    jogPrm.dec = acc;  // 减速度等于加速度

    m_lastError = GtsHal::setJogPrm(profile, jogPrm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 启动
    m_lastError = GtsHal::update(1L << (profile - 1));
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    return true;
}

bool MotionMgr::stop(short profile, long option) {
    if (!checkProfile(profile)) return false;
    long mask = 1L << (profile - 1);
    m_lastError = GtsHal::stop(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

QString MotionMgr::lastErrorString() const {
    return GtsErrorToString(m_lastError);
}
