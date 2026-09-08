#include "GtsCoordMgr.h"
#include "GtsMgr.h"
#include "ControllerData.h"

CoordMgr::CoordMgr(QObject* parent)
    : QObject(parent)
{
}

CoordMgr::~CoordMgr() 
{
    // 停止所有坐标系
    for (short crd = 0; crd < 2; crd++) {
        GtsHal::crdClear(crd, 0);
    }
}

bool CoordMgr::checkCrd(short crd) const 
{
    return (crd >= 0 && crd < CRD_MAX);
}

long CoordMgr::toPulse(AxisName name, double val) const
{
    short axis = m_gtsMgr ? m_gtsMgr->axisIndexByName(name) : -1;
    return (axis >= 1 && m_gtsMgr) ? m_gtsMgr->mmToPulse(axis, val) : 0;
}

double CoordMgr::velToPulse(AxisName name, double val) const
{
    short axis = m_gtsMgr ? m_gtsMgr->axisIndexByName(name) : -1;
    return (axis >= 1 && m_gtsMgr) ? m_gtsMgr->mmpsToPulsePerMs(axis, val) : 0.0;
}

bool CoordMgr::setCrdParams(short crd, const TCrdPrm& prm) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setCrdPrm(crd, prm);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setCrdPrm: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::getCrdParams(short crd, TCrdPrm& prm) const 
{
    if (!checkCrd(crd)) return false;
    m_lastError = GtsHal::getCrdPrm(crd, &prm);
    return m_lastError == 0;
}

bool CoordMgr::setCrdSmooth(short crd, const TCrdSmooth& smooth) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setCrdSmooth(crd, smooth);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setCrdSmooth: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::getCrdSmooth(short crd, TCrdSmooth& smooth) const 
{
    if (!checkCrd(crd)) return false;
    m_lastError = GtsHal::getCrdSmooth(crd, &smooth);
    return m_lastError == 0;
}

bool CoordMgr::setCrdJerk(short crd, double jerkMax) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setCrdJerk(crd, jerkMax);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setCrdJerk: ") + lastErrorString());
        return false;
    }
    return true;
}

double CoordMgr::getCrdJerk(short crd) const 
{
    if (!checkCrd(crd)) return 0.0;
    double jerk = 0.0;
    GtsHal::getCrdJerk(crd, &jerk);
    return jerk;
}

bool CoordMgr::setCrdMapBase(short crd, short base) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setCrdMapBase(crd, base);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setCrdMapBase: ") + lastErrorString());
        return false;
    }
    return true;
}

short CoordMgr::getCrdMapBase(short crd) const 
{
    if (!checkCrd(crd)) return -1;
    short base = 0;
    GtsHal::getCrdMapBase(crd, &base);
    return base;
}

bool CoordMgr::setArcAllowError(short crd, double error) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setArcAllowError(crd, error);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setArcAllowError: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::setCrdStopDecel(short crd, double decSmooth, double decAbrupt) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setCrdStopDec(crd, decSmooth, decAbrupt);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setCrdStopDec: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::getCrdStopDecel(short crd, double& decSmooth, double& decAbrupt) const 
{
    if (!checkCrd(crd)) return false;
    m_lastError = GtsHal::getCrdStopDec(crd, &decSmooth, &decAbrupt);
    return m_lastError == 0;
}

bool CoordMgr::lineXY(short crd, double x, double y, double synVel, double synAcc,
    double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px  = toPulse(AxisName::X, x);
    long   py  = toPulse(AxisName::Y, y);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);
    // 加速度暂不转换 (插补段无独立加速度数据)

    m_lastError = GtsHal::lnXY(crd, px, py, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXY: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::lineXYZ(short crd, double x, double y, double z, double synVel, double synAcc,
    double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px  = toPulse(AxisName::X, x);
    long   py  = toPulse(AxisName::Y, y);
    long   pz  = toPulse(AxisName::Z, z);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::lnXYZ(crd, px, py, pz, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXYZ: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::lineXYZA(short crd, double x, double y, double z, double a,
    double synVel, double synAcc, double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px  = toPulse(AxisName::X, x);
    long   py  = toPulse(AxisName::Y, y);
    long   pz  = toPulse(AxisName::Z, z);
    long   pa  = toPulse(AxisName::A, a);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::lnXYZA(crd, px, py, pz, pa, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXYZA: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::lineXYG0(short crd, double x, double y, double synVel, double synAcc, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px = toPulse(AxisName::X, x);
    long   py = toPulse(AxisName::Y, y);
    double pv = velToPulse(AxisName::X, synVel);

    m_lastError = GtsHal::lnXYG0(crd, px, py, pv, synAcc, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXYG0: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::lineXYZG0(short crd, double x, double y, double z, double synVel, double synAcc, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px = toPulse(AxisName::X, x);
    long   py = toPulse(AxisName::Y, y);
    long   pz = toPulse(AxisName::Z, z);
    double pv = velToPulse(AxisName::X, synVel);

    m_lastError = GtsHal::lnXYZG0(crd, px, py, pz, pv, synAcc, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXYZG0: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::lineXYZAG0(short crd, double x, double y, double z, double a,
    double synVel, double synAcc, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px = toPulse(AxisName::X, x);
    long   py = toPulse(AxisName::Y, y);
    long   pz = toPulse(AxisName::Z, z);
    long   pa = toPulse(AxisName::A, a);
    double pv = velToPulse(AxisName::X, synVel);

    m_lastError = GtsHal::lnXYZAG0(crd, px, py, pz, pa, pv, synAcc, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXYZAG0: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::lineXYZACUVW(short crd, long* pPos, short posMask,
    double synVel, double synAcc, double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::lnXYZACUVW(crd, pPos, posMask, synVel, synAcc, velEnd, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXYZACUVW: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::arcXYByRadius(short crd, double x, double y, double radius, short circleDir,
    double synVel, double synAcc, double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px  = toPulse(AxisName::X, x);
    long   py  = toPulse(AxisName::Y, y);
    double pr  = toPulse(AxisName::X, radius);         // 半径也是 mm
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::arcXYR(crd, px, py, pr, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("arcXYR: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::arcXYByCenter(short crd, double x, double y, double xCenter, double yCenter,
    short circleDir, double synVel, double synAcc,
    double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px   = toPulse(AxisName::X, x);
    long   py   = toPulse(AxisName::Y, y);
    double pxc  = toPulse(AxisName::X, xCenter);
    double pyc  = toPulse(AxisName::Y, yCenter);
    double pv   = velToPulse(AxisName::X, synVel);
    double pve  = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::arcXYC(crd, px, py, pxc, pyc, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("arcXYC: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::arcYZByRadius(short crd, double y, double z, double radius, short circleDir,
    double synVel, double synAcc, double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   py  = toPulse(AxisName::Y, y);
    long   pz  = toPulse(AxisName::Z, z);
    double pr  = toPulse(AxisName::Y, radius);
    double pv  = velToPulse(AxisName::Y, synVel);
    double pve = velToPulse(AxisName::Y, velEnd);

    m_lastError = GtsHal::arcYZR(crd, py, pz, pr, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("arcYZR: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::arcYZByCenter(short crd, double y, double z, double yCenter, double zCenter,
    short circleDir, double synVel, double synAcc,
    double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   py  = toPulse(AxisName::Y, y);
    long   pz  = toPulse(AxisName::Z, z);
    double pyc = toPulse(AxisName::Y, yCenter);
    double pzc = toPulse(AxisName::Z, zCenter);
    double pv  = velToPulse(AxisName::Y, synVel);
    double pve = velToPulse(AxisName::Y, velEnd);

    m_lastError = GtsHal::arcYZC(crd, py, pz, pyc, pzc, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("arcYZC: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::arcZXByRadius(short crd, double z, double x, double radius, short circleDir,
    double synVel, double synAcc, double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   pz  = toPulse(AxisName::Z, z);
    long   px  = toPulse(AxisName::X, x);
    double pr  = toPulse(AxisName::X, radius);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::arcZXR(crd, pz, px, pr, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("arcZXR: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::arcZXByCenter(short crd, double z, double x, double zCenter, double xCenter,
    short circleDir, double synVel, double synAcc,
    double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   pz  = toPulse(AxisName::Z, z);
    long   px  = toPulse(AxisName::X, x);
    double pzc = toPulse(AxisName::Z, zCenter);
    double pxc = toPulse(AxisName::X, xCenter);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::arcZXC(crd, pz, px, pzc, pxc, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("arcZXC: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::arcXYZ(short crd, double x, double y, double z,
    double interX, double interY, double interZ,
    double synVel, double synAcc, double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px  = toPulse(AxisName::X, x);
    long   py  = toPulse(AxisName::Y, y);
    long   pz  = toPulse(AxisName::Z, z);
    double pxi = toPulse(AxisName::X, interX);
    double pyi = toPulse(AxisName::Y, interY);
    double pzi = toPulse(AxisName::Z, interZ);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::arcXYZ(crd, px, py, pz, pxi, pyi, pzi, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("arcXYZ: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::helixXYRZ(short crd, double x, double y, double z, double radius, short circleDir,
    double synVel, double synAcc, double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px  = toPulse(AxisName::X, x);
    long   py  = toPulse(AxisName::Y, y);
    long   pz  = toPulse(AxisName::Z, z);
    double pr  = toPulse(AxisName::X, radius);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::helixXYRZ(crd, px, py, pz, pr, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("helixXYRZ: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::helixXYCZ(short crd, double x, double y, double z, double xCenter, double yCenter,
    short circleDir, double synVel, double synAcc,
    double velEnd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px  = toPulse(AxisName::X, x);
    long   py  = toPulse(AxisName::Y, y);
    long   pz  = toPulse(AxisName::Z, z);
    double pxc = toPulse(AxisName::X, xCenter);
    double pyc = toPulse(AxisName::Y, yCenter);
    double pv  = velToPulse(AxisName::X, synVel);
    double pve = velToPulse(AxisName::X, velEnd);

    m_lastError = GtsHal::helixXYCZ(crd, px, py, pz, pxc, pyc, circleDir, pv, synAcc, pve, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("helixXYCZ: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::bufIO(short crd, unsigned short doType, unsigned short doMask,
    unsigned short doValue, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::bufIO(crd, doType, doMask, doValue, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("bufIO: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::bufDelay(short crd, unsigned short delayTime, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::bufDelay(crd, delayTime, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("bufDelay: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::bufDA(short crd, short chn, short daValue, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::bufDA(crd, chn, daValue, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("bufDA: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::bufMove(short crd, short moveAxis, long pos, double vel, double acc,
    short modal, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::bufMove(crd, moveAxis, pos, vel, acc, modal, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("bufMove: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::bufGear(short crd, short gearAxis, long pos, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::bufGear(crd, gearAxis, pos, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("bufGear: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::bufStop(short crd, long mask, long option, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::bufStop(crd, mask, option, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("bufStop: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::bufMoveJog(short crd, short moveAxis, double vel, double acc,
    short modal, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::bufMoveJog(crd, moveAxis, vel, acc, modal, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("bufMoveJog: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::start(short mask, short option) 
{
    m_lastError = GtsHal::crdStart(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, QStringLiteral("crdStart: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::startStep(short mask, short option) 
{
    m_lastError = GtsHal::crdStartStep(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, QStringLiteral("crdStartStep: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::setStepMode(short mask, short option) 
{
    m_lastError = GtsHal::crdStepMode(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, QStringLiteral("crdStepMode: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::clear(short crd, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::crdClear(crd, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("crdClear: ") + lastErrorString());
        return false;
    }
    return true;
}

long CoordMgr::freeSpace(short crd, short fifo) const 
{
    if (!checkCrd(crd)) return -1;
    long space = 0;
    GtsHal::crdSpace(crd, &space, fifo);
    return space;
}

bool CoordMgr::status(short crd, short& running, long& segment, short fifo) const 
{
    if (!checkCrd(crd)) return false;
    m_lastError = GtsHal::crdStatus(crd, &running, &segment, fifo);
    return m_lastError == 0;
}

bool CoordMgr::getCrdPosition(short crd, double* pPos) const 
{
    if (!checkCrd(crd)) return false;
    m_lastError = GtsHal::getCrdPos(crd, pPos);
    return m_lastError == 0;
}

double CoordMgr::getCrdVelocity(short crd) const 
{
    if (!checkCrd(crd)) return 0.0;
    double vel = 0.0;
    GtsHal::getCrdVel(crd, &vel);
    return vel;
}

bool CoordMgr::setOverride(short crd, double synVelRatio) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setOverride(crd, synVelRatio);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setOverride: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::setOverride2(short crd, double synVelRatio) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setOverride2(crd, synVelRatio);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setOverride2: ") + lastErrorString());
        return false;
    }
    return true;
}

bool CoordMgr::setMaxOverrideLA(double maxSynVelRatio) 
{
    m_lastError = GtsHal::setMaxOverrideLA(maxSynVelRatio);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, QStringLiteral("setMaxOverrideLA: ") + lastErrorString());
        return false;
    }
    return true;
}


bool CoordMgr::setUserSegment(short crd, long segNum, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setUserSegNum(crd, segNum, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setUserSegNum: ") + lastErrorString());
        return false;
    }
    return true;
}

long CoordMgr::getUserSegment(short crd, short fifo) const 
{
    if (!checkCrd(crd)) return -1;
    long seg = 0;
    GtsHal::getUserSegNum(crd, &seg, fifo);
    return seg;
}

long CoordMgr::getRemainingSegment(short crd, short fifo) const 
{
    if (!checkCrd(crd)) return -1;
    long seg = 0;
    GtsHal::getRemainderSegNum(crd, &seg, fifo);
    return seg;
}

bool CoordMgr::setBufferMode(short crd, short bufferMode, short fifo) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    m_lastError = GtsHal::setCrdBufferMode(crd, bufferMode, fifo);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("setCrdBufferMode: ") + lastErrorString());
        return false;
    }
    return true;
}

short CoordMgr::getBufferMode(short crd, short fifo) const 
{
    if (!checkCrd(crd)) return -1;
    short mode = 0;
    GtsHal::getCrdBufferMode(crd, &mode, fifo);
    return mode;
}


bool CoordMgr::moveToXY(short crd, double x, double y, double vel, double acc) 
{
    // 快速直线移动：先清空缓冲区，添加直线段，启动
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    if (!m_gtsMgr) {
        emit errorOccurred(crd, -1, QStringLiteral("未注入 GtsMgr, 无法做当量换算"));
        return false;
    }

    long   px = toPulse(AxisName::X, x);
    long   py = toPulse(AxisName::Y, y);
    double pv = velToPulse(AxisName::X, vel);

    // 清除缓冲区
    GtsHal::crdClear(crd, 0);
    GtsHal::crdClear(crd, 1);

    // 添加直线插补段
    m_lastError = GtsHal::lnXY(crd, px, py, pv, acc, 0, 0);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("lnXY: ") + lastErrorString());
        return false;
    }

    // 启动运动
    m_lastError = GtsHal::crdStart(1L << crd, 0);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("crdStart: ") + lastErrorString());
        return false;
    }

    return true;
}

bool CoordMgr::stop(short crd, long option) 
{
    if (!checkCrd(crd)) {
        emit errorOccurred(crd, -1, QStringLiteral("坐标系号无效: %1").arg(crd));
        return false;
    }
    long mask = 1L << crd;
    m_lastError = GtsHal::stop(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(crd, m_lastError, QStringLiteral("stop: ") + lastErrorString());
        return false;
    }
    return true;
}

QString CoordMgr::lastErrorString() const 
{
    return GtsErrorToString(m_lastError);
}
