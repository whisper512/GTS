#include <QMessageBox>
#include <QCoreApplication>
#include <QThread>

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
        return false;
    }
}

void MotionMgr::getAxisMotionInfo(std::vector<stuAxis>& vecAxis)
{
    for (auto& axis : vecAxis) {
        short axisIndex = axis.axisIndex;           // 轴号 1~4
        axis.dPrfPosOriginal = axisProfilePos(axisIndex);   // 规划位置
        axis.dPrfVelOriginal = axisProfileVel(axisIndex);   // 规划速度
        axis.dPrfAccOriginal = axisProfileAcc(axisIndex);   // 规划加速度
    }
}

void MotionMgr::getCommonMotionInfo(std::vector<stuAxis>& vecAxis)
{
    for (auto& axis : vecAxis) {
        short profile = axis.axisIndex;                     // 轴号 1-4
        axis.lPrfMode = profileMode(profile);               // 运动模式
        axis.trapParam.dMotionVel = targetVel(profile);     // 读取trap的运动速度
    }
}


void MotionMgr::getTrapMotionInfo(std::vector<stuAxis>& vecTrap)
{
    for (auto& axis : vecTrap) {
        short profile = axis.axisIndex;  // 轴号 1-4
        TTrapPrm prm = {};
        if (getTrapParams(profile, prm)) {
            axis.trapParam.acc = prm.acc;
            axis.trapParam.dec = prm.dec;
            axis.trapParam.somoothTime = prm.smoothTime;
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

bool MotionMgr::startTrapMotion(short profile, long stepSize, const stuTrapParam& trap)
{
    if (!checkProfile(profile)) return false;

    // 检查参数
    if (trap.dMotionVel <= 0.0) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 运动速度无效 (dMotionVel = %2)，必须 > 0")
            .arg(profile).arg(trap.dMotionVel, 0, 'f', 3));
        return false;
    }
    if (stepSize == 0) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 步长为 0，无法运动").arg(profile));
        return false;
    }
    if (trap.acc <= 0.0) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 加速度无效 (acc = %2)，必须 > 0")
            .arg(profile).arg(trap.acc, 0, 'f', 6));
        return false;
    }
    if (trap.acc < 1e-4) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 加速度过小 (acc = %2)，换算后低于硬件有效范围")
            .arg(profile).arg(trap.acc, 0, 'f', 6));
        return false;
    }
    if (trap.dec <= 0.0) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 减速度无效 (dec = %2)，必须 > 0")
            .arg(profile).arg(trap.dec, 0, 'f', 6));
        return false;
    }
    if (trap.dec < 1e-4) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 减速度过小 (dec = %2)，换算后低于硬件有效范围")
            .arg(profile).arg(trap.dec, 0, 'f', 6));
        return false;
    }
    if (trap.somoothTime < 0) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 平滑时间无效 (smoothTime = %2)，不能为负数")
            .arg(profile).arg(trap.somoothTime));
        return false;
    }
    // 单次模式（cycleTimes <= 0）
    if (trap.cycleTimes <= 0) {
        return singleTrapMotion(profile, stepSize, trap.acc, trap.dec, trap.somoothTime, trap.dMotionVel);
    }
    // 循环模式
    long currentStep = stepSize;
    int times = trap.cycleTimes;
    for (int i = 0; i < times; ++i) {
        if (!singleTrapMotion(profile, currentStep, trap.acc, trap.dec, trap.somoothTime, trap.dMotionVel))
            return false;
        waitMotionDone(profile);
        if (trap.Delay > 0) {
            GtsHal::delay(static_cast<unsigned short>(trap.Delay));
        }
        if (!singleTrapMotion(profile, -currentStep, trap.acc, trap.dec, trap.somoothTime, trap.dMotionVel))
            return false;
        waitMotionDone(profile);
        if (trap.Delay > 0) {
            GtsHal::delay(static_cast<unsigned short>(trap.Delay));
        }
    }
    return true;
}


bool MotionMgr::trapMotion(short profile, double lengthMm)
{
    if (!checkProfile(profile)) return false;

    // 获取当量参数
    long prfAlpha = 1, prfBeta = 1;
    prfAlpha = m_pTotalMgr->configMgr()->profileScaleAlpha(profile);
    prfBeta = m_pTotalMgr->configMgr()->profileScaleBeta(profile);

    if (prfBeta == 0) {
        emit errorOccurred(profile, -1,
            QStringLiteral("当量参数无效 prfAlpha=%1 prfBeta=%2")
            .arg(prfAlpha).arg(prfBeta));
        return false;
    }

    if (m_pTotalMgr->pulsePerMm(profile) == 0.0) { /*报错*/ }
    long stepSize = m_pTotalMgr->mmToPulse(profile, lengthMm);
   

    // 长度非零但换算后脉冲为 0
    if (stepSize == 0 && lengthMm != 0.0) {
        emit errorOccurred(profile, -1,
            QStringLiteral("下发 %.4f mm 换算脉冲 = %1，被截断为 0，请检查当量")
            .arg(lengthMm, 0, 'f', 4).arg(stepSize));
        return false;
    }

    // 准备运动参数：从轴对象获取 trapParam
    int idx = profile - 1;
    stuAxis* pAxis = m_pTotalMgr->getAxisRef(idx);
    if (!pAxis) return false;

    // 运动参数单位换算：mm/s → pulse/ms, mm/s² → pulse/ms²
    stuTrapParam trapPrm = pAxis->trapParam;          
    trapPrm.dMotionVel = m_pTotalMgr->mmpsToPulsePerMs(profile, trapPrm.dMotionVel);
    trapPrm.acc = m_pTotalMgr->mmps2ToPulsePerMs2(profile, trapPrm.acc);
    trapPrm.dec = m_pTotalMgr->mmps2ToPulsePerMs2(profile, trapPrm.dec);

    return startTrapMotion(profile, stepSize, trapPrm);
}

void MotionMgr::getJogMotionInfo(std::vector<stuAxis>& vecAxis)
{
    for (auto& axis : vecAxis) {
        short profile = axis.axisIndex;  // 轴号 1-4
        TJogPrm prm = {};
        if (getJogParams(profile, prm)) {
            // 读到了才更新内存
            axis.jogParam.acc = prm.acc;
            axis.jogParam.dec = prm.dec;
        }
    }
}

bool MotionMgr::setJogParam(short axisId, const stuJogParam& param)
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
    int idx = profile - 1;
    stuAxis* pAxis = m_pTotalMgr->getAxisRef(idx);
    if (!pAxis) return false;

    const stuJogParam& jog = pAxis->jogParam;

    // Jog 运动参数单位换算：mm/s → pulse/ms, mm/s² → pulse/ms²
    if (m_pTotalMgr->pulsePerMm(profile) == 0.0) {
        emit errorOccurred(profile, -1,
            QStringLiteral("当量参数无效"));
        return false;
    }
    double jogVel = m_pTotalMgr->mmpsToPulsePerMs(profile, jog.dMotionVel);
    double jogAcc = m_pTotalMgr->mmps2ToPulsePerMs2(profile, jog.acc);
    double jogDec = m_pTotalMgr->mmps2ToPulsePerMs2(profile, jog.dec);


    // 参数检查
    if (jogVel <= 0.0) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 Jog速度无效 (dMotionVel = %2)，必须 > 0")
            .arg(profile).arg(jog.dMotionVel, 0, 'f', 3));
        return false;
    }
    if (jogAcc < 1e-4) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 Jog加速度过小 (acc = %2 → %3 pulse/ms^2)，低于硬件有效范围")
            .arg(profile).arg(jog.acc, 0, 'f', 6).arg(jogAcc, 0, 'f', 6));
        return false;
    }
    if (jogDec < 1e-4) {
        QMessageBox::warning(nullptr, QStringLiteral("参数错误"),
            QStringLiteral("轴%1 Jog减速度过小 (dec = %2 → %3 pulse/ms^2)，低于硬件有效范围")
            .arg(profile).arg(jog.dec, 0, 'f', 6).arg(jogDec, 0, 'f', 6));
        return false;
    }

    // 设置为 Jog 模式
    m_lastError = GtsHal::prfJog(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置 Jog 参数 (acc, dec, smooth) —— 已换算为 pulse/ms²
    TJogPrm prm;
    prm.acc = jogAcc;
    prm.dec = jogDec;
    prm.smooth = 0.0;
    m_lastError = GtsHal::setJogPrm(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }

    // 设置速度（方向：正方向 vel > 0，反方向 vel < 0）—— 已换算为 pulse/ms
    double targetVel = (direction > 0) ? jogVel : -jogVel;
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


bool MotionMgr::homeStart(short axis)
{
    if (!checkProfile(axis)) return false;

    ConfigMgr* cfg = m_pTotalMgr->configMgr();
    homeMode mode = cfg->homeModeValue(axis);
    double homeVelMm = cfg->homeVel(axis);
    double homeAccMm = cfg->homeAcc(axis);
    double homeRangeMm = cfg->homeRange(axis);
    double homeOffsetMm = cfg->homeOffset(axis);

    // ── 当量换算 ──
    if (m_pTotalMgr->pulsePerMm(axis) == 0.0) {
        emit errorOccurred(axis, -1,
            QStringLiteral("轴%1 当量参数无效，无法换算").arg(axis));
        return false;
    }
    double vel = m_pTotalMgr->mmpsToPulsePerMs(axis, homeVelMm);
    double acc = m_pTotalMgr->mmps2ToPulsePerMs2(axis, homeAccMm);
    long   range = m_pTotalMgr->mmToPulse(axis, homeRangeMm);
    long   offset = m_pTotalMgr->mmToPulse(axis, homeOffsetMm);


    // ── 搜索方向 ──
    bool searchPos = false;
    QString modeName;
    switch (mode) {
    case homeMode::HomeMode_nLlimit:   searchPos = false; modeName = QStringLiteral("负限位");  break;
    case homeMode::HomeMode_pLlimit:   searchPos = true;  modeName = QStringLiteral("正限位");  break;
    case homeMode::HomeMode_Home:      searchPos = false; modeName = QStringLiteral("原点DI");  break;
    case homeMode::HomeMode_HomeIndex: searchPos = false; modeName = QStringLiteral("原点+Index"); break;
    case homeMode::HomeMode_Index:     searchPos = false; modeName = QStringLiteral("Index");   break;
    }
    long searchStep = searchPos ? range : -range;

    // ★ 回零开始
    emit homeStatus(axis, QStringLiteral("回零开始 模式=%1 Vel=%2mm/s Acc=%3mm/s^2 Range=%4mm Offset=%5mm")
        .arg(modeName).arg(homeVelMm).arg(homeAccMm).arg(homeRangeMm).arg(homeOffsetMm));

    // ── 步骤1: 梯形模式 ──
    m_lastError = GtsHal::prfTrap(axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }

    // ── 步骤2: 梯形参数 ──
    TTrapPrm prm;
    prm.acc = acc;
    prm.dec = acc;
    prm.velStart = 0.0;
    prm.smoothTime = 0;
    m_lastError = GtsHal::setTrapPrm(axis, prm);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }

    // ── 步骤3: 确定检测方式 ──
    bool useCapture = false;
    short captureType = 0;
    bool useDI = false;
    short diType = 0;
    int   triggerBit = 0;

    switch (mode) {
    case homeMode::HomeMode_nLlimit:
        break;
    case homeMode::HomeMode_pLlimit:
        break;
    case homeMode::HomeMode_Home:
        useDI = true;
        diType = MC_HOME;
        triggerBit = 1;
        break;
    case homeMode::HomeMode_HomeIndex:
        useCapture = true;
        captureType = 1;
        break;
    case homeMode::HomeMode_Index:
        useCapture = true;
        captureType = 2;
        break;
    }

    if (useCapture) {
        m_lastError = GT_SetCaptureMode(axis, captureType);
        if (m_lastError != 0) {
            emit errorOccurred(axis, m_lastError,
                QStringLiteral("轴%1 GT_SetCaptureMode(%2) 失败")
                .arg(axis).arg(captureType));
            return false;
        }
        emit homeStatus(axis, QStringLiteral("硬件捕获模式已配置 captureType=%1").arg(captureType));
    }
    else if (useDI) {
        emit homeStatus(axis, QStringLiteral("检测方式=DI轮询(原点信号)"));
    }
    else {
        emit homeStatus(axis, QStringLiteral("检测方式=限位DI轮询"));
    }

    // ── 步骤4: 启动搜索运动 ──
    double curPos = profilePos(axis);
    long targetPos = static_cast<long>(curPos) + searchStep;
    long mask = 1L << (axis - 1);

    emit homeStatus(axis, QStringLiteral("启动搜索运动 curPos=%1 targetPos=%2 step=%3 pulse")
        .arg(curPos, 0, 'f', 0).arg(targetPos).arg(searchStep));

    m_lastError = GtsHal::setPos(axis, targetPos);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    m_lastError = GtsHal::setVel(axis, vel);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    m_lastError = GtsHal::update(mask);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    emit homeStatus(axis, QStringLiteral("搜索运动已启动 GT_Update OK"));

    // ── 步骤5: 等待触发 ──
    if (useDI) {
        // === DI 检测模式（模式2: Home） ===
        emit homeStatus(axis, QStringLiteral("等待原点DI触发..."));
        long sts = 0;
        long diVal = 0;
        int axisBit = axis - 1;

        do {
            GtsHal::getSts(axis, &sts);
            GtsHal::getDi(diType, &diVal);
            QCoreApplication::processEvents();

            if (!(sts & 0x400)) {
                emit errorOccurred(axis, -1,
                    QStringLiteral("轴%1 回零失败:运动停止但未检测到原点信号 sts=0x%2 di=0x%3")
                    .arg(axis).arg(sts, 0, 16).arg(diVal, 0, 16));
                return false;
            }
        } while (((diVal >> axisBit) & 1) != triggerBit);

        emit homeStatus(axis, QStringLiteral("原点DI触发! di=0x%1 立即停止").arg(diVal, 0, 16));

        stop(axis, 0);
        do {
            GtsHal::getSts(axis, &sts);
            QCoreApplication::processEvents();
        } while (sts & 0x400);
        emit homeStatus(axis, QStringLiteral("轴已停止"));

        double capPos = profilePos(axis);
        emit homeStatus(axis, QStringLiteral("触发位置=%1 offset=%2 → 移动到=%3")
            .arg(capPos, 0, 'f', 0).arg(offset).arg(static_cast<long>(capPos) + offset));

        long finalTarget = static_cast<long>(capPos) + offset;
        m_lastError = GtsHal::setPos(axis, finalTarget);
        if (m_lastError != 0) {
            emit errorOccurred(axis, m_lastError, lastErrorString());
            return false;
        }
        m_lastError = GtsHal::update(mask);
        if (m_lastError != 0) {
            emit errorOccurred(axis, m_lastError, lastErrorString());
            return false;
        }
        waitMotionDone(axis);
        emit homeStatus(axis, QStringLiteral("偏移移动完成"));
    }
    else if (useCapture) {
        // === 硬件捕获模式（模式3/4: Index） ===
        emit homeStatus(axis, QStringLiteral("等待硬件捕获(Index/Z相)..."));
        short capture = 0;
        long  capPos = 0;
        long  sts = 0;

        do {
            GtsHal::getSts(axis, &sts);
            GT_GetCaptureStatus(axis, &capture, &capPos);
            QCoreApplication::processEvents();

            if (!(sts & 0x400)) {
                emit errorOccurred(axis, -1,
                    QStringLiteral("轴%1 回零失败:运动停止但未捕获到信号 sts=0x%2 capture=%3")
                    .arg(axis).arg(sts, 0, 16).arg(capture));
                return false;
            }
        } while (capture == 0);

        emit homeStatus(axis, QStringLiteral("捕获 capPos=%1 → 移动到=%2")
            .arg(capPos).arg(capPos + offset));

        long finalTarget = capPos + offset;
        m_lastError = GtsHal::setPos(axis, finalTarget);
        if (m_lastError != 0) {
            emit errorOccurred(axis, m_lastError, lastErrorString());
            return false;
        }
        m_lastError = GtsHal::update(mask);
        if (m_lastError != 0) {
            emit errorOccurred(axis, m_lastError, lastErrorString());
            return false;
        }
        waitMotionDone(axis);
        emit homeStatus(axis, QStringLiteral("偏移移动完成"));
    }
    else {
        // === 限位模式（模式0/1）—— 与 500ms 定时器同机制的 DI 检测 ===
        QString lmtName = (mode == homeMode::HomeMode_nLlimit) ? QStringLiteral("负限位") : QStringLiteral("正限位");
        emit homeStatus(axis, QStringLiteral("等待%1DI触发...").arg(lmtName));

        long sts = 0;
        long diVal = 0;
        short diType = (mode == homeMode::HomeMode_nLlimit)
            ? MC_LIMIT_NEGATIVE
            : MC_LIMIT_POSITIVE;
        int axisBit = axis - 1;

        do {
            GtsHal::getSts(axis, &sts);
            GtsHal::getDi(diType, &diVal);
            QCoreApplication::processEvents();

            if (!(sts & 0x400)) break;
        } while (((diVal >> axisBit) & 1) == 0);

        GtsHal::getDi(diType, &diVal);

        if (((diVal >> axisBit) & 1) == 0) {
            emit errorOccurred(axis, -1,
                QStringLiteral("轴%1 回零失败:未触发限位"
                    "(搜索范围=%2 pulse, sts=0x%3, di=0x%4)")
                .arg(axis).arg(range).arg(sts, 0, 16).arg(diVal, 0, 16));
            return false;
        }

        emit homeStatus(axis, QStringLiteral("%1DI触发! di=0x%2 立即停止")
            .arg(lmtName).arg(diVal, 0, 16));

        stop(axis, 0);
        do {
            GtsHal::getSts(axis, &sts);
            QCoreApplication::processEvents();
        } while (sts & 0x400);
        emit homeStatus(axis, QStringLiteral("轴已停止,清除限位状态"));

        GtsHal::clrSts(axis, axis);

        long escapeStep = searchPos ? -offset : offset;
        curPos = profilePos(axis);
        emit homeStatus(axis, QStringLiteral("脱离限位 curPos=%1 escape=%2 → target=%3")
            .arg(curPos, 0, 'f', 0).arg(escapeStep).arg(static_cast<long>(curPos) + escapeStep));

        m_lastError = GtsHal::setPos(axis, static_cast<long>(curPos) + escapeStep);
        if (m_lastError != 0) {
            emit errorOccurred(axis, m_lastError, lastErrorString());
            return false;
        }
        m_lastError = GtsHal::update(mask);
        if (m_lastError != 0) {
            emit errorOccurred(axis, m_lastError, lastErrorString());
            return false;
        }
        waitMotionDone(axis);
        emit homeStatus(axis, QStringLiteral("脱离限位+偏移完成"));
    }

    // ── 步骤6: 位置清零 ──
    emit homeStatus(axis, QStringLiteral("位置清零"));
    m_lastError = GtsHal::zeroPos(axis, axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }

    // 清除状态
    QThread::msleep(1000);
    m_pTotalMgr->axisMgr()->clearStatus(axis);

    emit homeStatus(axis, QStringLiteral("回零完成"));
    emit motionDone(axis);
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


bool MotionMgr::setProfilePos(short profile, long pos) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPrfPos(profile, pos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

double MotionMgr::profilePos(short profile) const 
{
    if (!checkProfile(profile)) return 0.0;
    double pos = 0.0;
    GtsHal::getPrfPos(profile, &pos);
    return pos;
}

double MotionMgr::profileVel(short profile) const 
{
    if (!checkProfile(profile)) return 0.0;
    double vel = 0.0;
    GtsHal::getPrfVel(profile, &vel);
    return vel;
}

double MotionMgr::profileAcc(short profile) const 
{
    if (!checkProfile(profile)) return 0.0;
    double acc = 0.0;
    GtsHal::getPrfAcc(profile, &acc);
    return acc;
}

long MotionMgr::profileMode(short profile) const 
{
    if (!checkProfile(profile)) return -1;
    long mode = 0;
    GtsHal::getPrfMode(profile, &mode);
    return mode;
}

double MotionMgr::axisProfilePos(short axis) const 
{
    if (!checkProfile(axis)) return 0.0;
    double pos = 0.0;
    GtsHal::getAxisPrfPos(axis, &pos);
    return pos;
}

double MotionMgr::axisProfileVel(short axis) const 
{
    if (!checkProfile(axis)) return 0.0;
    double vel = 0.0;
    GtsHal::getAxisPrfVel(axis, &vel);
    return vel;
}

double MotionMgr::axisProfileAcc(short axis) const 
{
    if (!checkProfile(axis)) return 0.0;
    double acc = 0.0;
    GtsHal::getAxisPrfAcc(axis, &acc);
    return acc;
}

bool MotionMgr::setTargetPos(short profile, long pos) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPos(profile, pos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setTargetVel(short profile, double vel) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setVel(profile, vel);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

long MotionMgr::targetPos(short profile) const 
{
    if (!checkProfile(profile)) return 0;
    long pos = 0;
    GtsHal::getPos(profile, &pos);
    return pos;
}

double MotionMgr::targetVel(short profile) const 
{
    if (!checkProfile(profile)) return 0.0;
    double vel = 0.0;
    GtsHal::getVel(profile, &vel);
    return vel;
}

bool MotionMgr::update(long mask) 
{
    m_lastError = GtsHal::update(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setProfileScale(short axis, long alpha, long beta) 
{
    if (!checkProfile(axis)) return false;
    m_lastError = GtsHal::setProfileScale(axis, alpha, beta);
    return m_lastError == 0;
}

bool MotionMgr::getProfileScale(short axis, long& alpha, long& beta) const 
{
    if (!checkProfile(axis)) return false;
    m_lastError = GtsHal::getProfileScale(axis, &alpha, &beta);
    return m_lastError == 0;
}


bool MotionMgr::setTrapMode(short profile) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfTrap(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setTrapParams(short profile, const TTrapPrm& prm) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setTrapPrm(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getTrapParams(short profile, TTrapPrm& prm) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getTrapPrm(profile, &prm);
    return m_lastError == 0;
}

bool MotionMgr::getTrapTime(short profile, TTrapTime& time) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getTrapTime(profile, &time);
    return m_lastError == 0;
}


bool MotionMgr::setJogMode(short profile) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfJog(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setJogParams(short profile, const TJogPrm& prm) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setJogPrm(profile, prm);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getJogParams(short profile, TJogPrm& prm) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getJogPrm(profile, &prm);
    return m_lastError == 0;
}


bool MotionMgr::moveAbsolute(short profile, long pos, double vel, double acc, double dec) 
{
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

bool MotionMgr::moveVelocity(short profile, double vel, double acc) 
{
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

bool MotionMgr::getMoveAbsoluteParams(short profile, TMoveAbsolutePrm& prm) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getMoveAbsolute(profile, &prm);
    return m_lastError == 0;
}

bool MotionMgr::getMoveVelocityParams(short profile, TMoveVelocityPrm& prm) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getMoveVelocity(profile, &prm);
    return m_lastError == 0;
}


bool MotionMgr::setPtMode(short profile, short mode) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfPt(profile, mode);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setPtLoop(short profile, long loop) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPtLoop(profile, loop);
    return m_lastError == 0;
}

long MotionMgr::getPtLoop(short profile) const 
{
    if (!checkProfile(profile)) return 0;
    long loop = 0;
    GtsHal::getPtLoop(profile, &loop);
    return loop;
}

short MotionMgr::ptFreeSpace(short profile, short fifo) const 
{
    if (!checkProfile(profile)) return -1;
    short space = 0;
    GtsHal::ptSpace(profile, &space, fifo);
    return space;
}

bool MotionMgr::ptAddData(short profile, double pos, long time, short type, short fifo) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptData(profile, pos, time, type, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::ptAddDataWithSeg(short profile, double pos, long time,
    short type, long segNum, short fifo) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptDataWN(profile, pos, time, type, segNum, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::ptClear(short profile, short fifo) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptClear(profile, fifo);
    return m_lastError == 0;
}

bool MotionMgr::ptStart(long mask, long option) 
{
    m_lastError = GtsHal::ptStart(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setPtMemory(short profile, short memory) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPtMemory(profile, memory);
    return m_lastError == 0;
}

short MotionMgr::getPtMemory(short profile) const 
{
    if (!checkProfile(profile)) return -1;
    short mem = 0;
    GtsHal::getPtMemory(profile, &mem);
    return mem;
}

long MotionMgr::ptCurrentSegment(short profile) const 
{
    if (!checkProfile(profile)) return -1;
    long seg = 0;
    GtsHal::ptGetSegNum(profile, &seg);
    return seg;
}

bool MotionMgr::ptAddDoBit(short profile, short doType, short index, short value, short fifo) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptDoBit(profile, doType, index, value, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::ptAddAo(short profile, short aoType, short index, double value, short fifo) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::ptAo(profile, aoType, index, value, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}


bool MotionMgr::setGearMode(short profile, short dir) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfGear(profile, dir);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setGearMaster(short profile, short masterIndex, short masterType, short masterItem) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setGearMaster(profile, masterIndex, masterType, masterItem);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getGearMaster(short profile, short& masterIndex,
    short& masterType, short& masterItem) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getGearMaster(profile, &masterIndex, &masterType, &masterItem);
    return m_lastError == 0;
}

bool MotionMgr::setGearRatio(short profile, long masterEven, long slaveEven, long masterSlope) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setGearRatio(profile, masterEven, slaveEven, masterSlope);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getGearRatio(short profile, long& masterEven, long& slaveEven, long& masterSlope) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getGearRatio(profile, &masterEven, &slaveEven, &masterSlope);
    return m_lastError == 0;
}

bool MotionMgr::gearStart(long mask) 
{
    m_lastError = GtsHal::gearStart(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setGearEvent(short profile, short event, long startPara0, long startPara1) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setGearEvent(profile, event, startPara0, startPara1);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getGearEvent(short profile, short& event, long& startPara0, long& startPara1) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getGearEvent(profile, &event, &startPara0, &startPara1);
    return m_lastError == 0;
}


bool MotionMgr::setFollowMode(short profile, short dir) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfFollow(profile, dir);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setFollowMaster(short profile, short masterIndex, short masterType, short masterItem) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowMaster(profile, masterIndex, masterType, masterItem);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getFollowMaster(short profile, short& masterIndex,
    short& masterType, short& masterItem) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getFollowMaster(profile, &masterIndex, &masterType, &masterItem);
    return m_lastError == 0;
}

bool MotionMgr::setFollowLoop(short profile, long loop) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowLoop(profile, loop);
    return m_lastError == 0;
}

long MotionMgr::getFollowLoop(short profile) const 
{
    if (!checkProfile(profile)) return 0;
    long loop = 0;
    GtsHal::getFollowLoop(profile, &loop);
    return loop;
}

bool MotionMgr::setFollowEvent(short profile, short event, short masterDir, long pos) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowEvent(profile, event, masterDir, pos);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::getFollowEvent(short profile, short& event, short& masterDir, long& pos) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getFollowEvent(profile, &event, &masterDir, &pos);
    return m_lastError == 0;
}

short MotionMgr::followFreeSpace(short profile, short fifo) const 
{
    if (!checkProfile(profile)) return -1;
    short space = 0;
    GtsHal::followSpace(profile, &space, fifo);
    return space;
}

bool MotionMgr::followAddData(short profile, long masterSegment, double slaveSegment,
    short type, short fifo) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::followData(profile, masterSegment, slaveSegment, type, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::followClear(short profile, short fifo) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::followClear(profile, fifo);
    return m_lastError == 0;
}

bool MotionMgr::followStart(long mask, long option) 
{
    m_lastError = GtsHal::followStart(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::followSwitch(long mask) 
{
    m_lastError = GtsHal::followSwitch(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setFollowMemory(short profile, short memory) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setFollowMemory(profile, memory);
    return m_lastError == 0;
}

short MotionMgr::getFollowMemory(short profile) const 
{
    if (!checkProfile(profile)) return -1;
    short mem = 0;
    GtsHal::getFollowMemory(profile, &mem);
    return mem;
}

bool MotionMgr::getFollowStatus(short profile, short& fifoNum, short& switchStatus) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getFollowStatus(profile, &fifoNum, &switchStatus);
    return m_lastError == 0;
}


bool MotionMgr::setPvtMode(short profile) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::prfPvt(profile);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::setPvtLoop(short profile, long loop) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::setPvtLoop(profile, loop);
    return m_lastError == 0;
}

bool MotionMgr::getPvtLoop(short profile, long& loopCount, long& loop) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::getPvtLoop(profile, &loopCount, &loop);
    return m_lastError == 0;
}

bool MotionMgr::pvtStatus(short profile, short& tableId, double& time) const 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::pvtStatus(profile, &tableId, &time);
    return m_lastError == 0;
}

bool MotionMgr::pvtTableClear(short tableId) 
{
    m_lastError = GtsHal::pvtTableClear(tableId);
    return m_lastError == 0;
}

bool MotionMgr::pvtStart(long mask) 
{
    m_lastError = GtsHal::pvtStart(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSelect(short profile, short tableId) 
{
    if (!checkProfile(profile)) return false;
    m_lastError = GtsHal::pvtTableSelect(profile, tableId);
    return m_lastError == 0;
}

bool MotionMgr::pvtTableSet(short tableId, long count, double* time, double* pos, double* vel) 
{
    m_lastError = GtsHal::pvtTable(tableId, count, time, pos, vel);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSetEx(short tableId, long count, double* time, double* pos,
    double* velBegin, double* velEnd) 
{
    m_lastError = GtsHal::pvtTableEx(tableId, count, time, pos, velBegin, velEnd);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSetComplete(short tableId, long count, double* time, double* pos,
    double* a, double* b, double* c,
    double velBegin, double velEnd) 
{
    m_lastError = GtsHal::pvtTableComplete(tableId, count, time, pos, a, b, c, velBegin, velEnd);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool MotionMgr::pvtTableSetPercent(short tableId, long count, double* time, double* pos,
    double* percent, double velBegin) 
{
    m_lastError = GtsHal::pvtTablePercent(tableId, count, time, pos, percent, velBegin);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}


bool MotionMgr::moveTo(short profile, long pos, double vel, double acc, double dec) 
{
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

bool MotionMgr::jog(short profile, double vel, double acc) 
{
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

bool MotionMgr::stop(short profile, long option) 
{
    if (!checkProfile(profile)) return false;
    long mask = 1L << (profile - 1);
    m_lastError = GtsHal::stop(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

QString MotionMgr::lastErrorString() const 
{
    return GtsErrorToString(m_lastError);
}
