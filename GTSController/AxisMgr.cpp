#include "AxisMgr.h"

AxisMgr::AxisMgr(QObject* parent)
    : QObject(parent)
{
}

AxisMgr::~AxisMgr() {
    // 析构时禁止所有轴
    disableAll();
}

bool AxisMgr::isValidAxis(short axis)  {
    bool valid = (axis >= 0 && axis < m_axisCount);
    if (!valid) {
        emit errorOccurred(axis, -1, QStringLiteral("轴号无效: %1 (有效范围 0-%2)")
            .arg(axis).arg(m_axisCount - 1));
    }
    return valid;
}

bool AxisMgr::enable(short axis) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::axisOn(axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::disable(short axis) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::axisOff(axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::enableMulti(unsigned long mask) {
    m_lastError = GtsHal::multiAxisOn(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::disableMulti(unsigned long mask) {
    m_lastError = GtsHal::multiAxisOff(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::enableAll() {
    unsigned long mask = (1UL << m_axisCount) - 1;
    return enableMulti(mask);
}

bool AxisMgr::disableAll() {
    unsigned long mask = (1UL << m_axisCount) - 1;
    return disableMulti(mask);
}

bool AxisMgr::isEnabled(short axis)  {
    if (!isValidAxis(axis)) return false;

    long sts = 0;
    GtsHal::getSts(axis, &sts);
    // 轴状态中某一位表示使能(具体位需参考固高文档，通常 bit 0 或 bit 1)
    // 这里返回原始状态，由上层判断
    return (sts != -1);  // -1 通常表示轴不存在或错误
}

bool AxisMgr::setOnDelayTime(unsigned short ms) {
    m_lastError = GtsHal::setAxisOnDelayTime(ms);
    return m_lastError == 0;
}

unsigned short AxisMgr::onDelayTime() {
    unsigned short ms = 0;
    GtsHal::getAxisOnDelayTime(&ms);
    return ms;
}


bool AxisMgr::stop(short axis, long option) {
    if (!isValidAxis(axis)) return false;

    long mask = 1L << axis;
    m_lastError = GtsHal::stop(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::stopAll(long option) {
    long mask = (1L << m_axisCount) - 1;
    m_lastError = GtsHal::stop(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::stopMulti(long mask, long option) {
    m_lastError = GtsHal::stop(mask, option);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}


bool AxisMgr::alarmOn(short axis) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::alarmOn(axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    emit alarmTriggered(axis);
    return true;
}

bool AxisMgr::alarmOff(short axis) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::alarmOff(axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::isAlarm(short axis) {
    if (!isValidAxis(axis)) return false;

    long sts = 0;
    GtsHal::getSts(axis, &sts);
    return (sts & 0x02) != 0;  // 假设 bit1 表示报警
}

bool AxisMgr::limitOn(short axis, short limitType) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::lmtsOn(axis, limitType);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::limitOff(short axis, short limitType) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::lmtsOff(axis, limitType);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::setLimitSense(unsigned short sense) {
    m_lastError = GtsHal::lmtSns(sense);
    return m_lastError == 0;
}

bool AxisMgr::setSoftLimit(short axis, long positive, long negative) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::setSoftLimit(axis, positive, negative);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::getSoftLimit(short axis, long& positive, long& negative) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::getSoftLimit(axis, &positive, &negative);
    return m_lastError == 0;
}


long AxisMgr::status(short axis) {
    if (!isValidAxis(axis)) return -1;

    long sts = 0;
    m_lastError = GtsHal::getSts(axis, &sts);
    return sts;
}

bool AxisMgr::clearStatus(short axis) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::clrSts(axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::zeroPosition(short axis) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::zeroPos(axis);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::syncPosition(long mask) {
    m_lastError = GtsHal::synchAxisPos(mask);
    if (m_lastError != 0) {
        emit errorOccurred(-1, m_lastError, lastErrorString());
        return false;
    }
    return true;
}


bool AxisMgr::setControlMode(short axis, short mode) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::ctrlMode(axis, mode);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::setAxisMode(short axis, short mode) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::setAxisMode(axis, mode);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

short AxisMgr::getAxisMode(short axis) {
    if (!isValidAxis(axis)) return -1;

    short mode = 0;
    m_lastError = GtsHal::getAxisMode(axis, &mode);
    return mode;
}

bool AxisMgr::setFollowErrorLimit(short control, long error) {
    m_lastError = GtsHal::setPosErr(control, error);
    if (m_lastError != 0) {
        emit errorOccurred(control, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

long AxisMgr::getFollowErrorLimit(short control) {
    long error = 0;
    m_lastError = GtsHal::getPosErr(control, &error);
    return error;
}

bool AxisMgr::setFollowErrorMode(short axis, short mode) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::setAxisFollowErrorMode(axis, mode);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

short AxisMgr::getFollowErrorMode(short axis) {
    if (!isValidAxis(axis)) return -1;

    short mode = 0;
    m_lastError = GtsHal::getAxisFollowErrorMode(axis, &mode);
    return mode;
}


bool AxisMgr::setStopDecel(short profile, double smooth, double abrupt) {
    m_lastError = GtsHal::setStopDec(profile, smooth, abrupt);
    if (m_lastError != 0) {
        emit errorOccurred(profile, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

bool AxisMgr::getStopDecel(short profile, double& smooth, double& abrupt) {
    m_lastError = GtsHal::getStopDec(profile, &smooth, &abrupt);
    return m_lastError == 0;
}

bool AxisMgr::setStopIO(short axis, short stopType, short inputType, short inputIndex) {
    if (!isValidAxis(axis)) return false;

    m_lastError = GtsHal::setStopIo(axis, stopType, inputType, inputIndex);
    if (m_lastError != 0) {
        emit errorOccurred(axis, m_lastError, lastErrorString());
        return false;
    }
    return true;
}

double AxisMgr::encoderPosition(short axis) {
    if (!isValidAxis(axis)) return 0.0;

    double pos = 0.0;
    GtsHal::getAxisEncPos(axis, &pos);
    return pos;
}

double AxisMgr::encoderVelocity(short axis){
    if (!isValidAxis(axis)) return 0.0;

    double vel = 0.0;
    GtsHal::getAxisEncVel(axis, &vel);
    return vel;
}

double AxisMgr::encoderAcceleration(short axis) {
    if (!isValidAxis(axis)) return 0.0;

    double acc = 0.0;
    GtsHal::getAxisEncAcc(axis, &acc);
    return acc;
}

double AxisMgr::trackingError(short axis) {
    if (!isValidAxis(axis)) return 0.0;

    double err = 0.0;
    GtsHal::getAxisError(axis, &err);
    return err;
}


QString AxisMgr::lastErrorString(){
    return GtsErrorToString(m_lastError);
}

QString AxisMgr::statusToString(long sts) {
    QStringList desc;
    if (sts & 0x0001) desc << "使能中";
    if (sts & 0x0002) desc << "报警";
    if (sts & 0x0004) desc << "正限位";
    if (sts & 0x0008) desc << "负限位";
    if (sts & 0x0010) desc << "回零中";
    if (sts & 0x0020) desc << "运动中";
    if (sts & 0x0040) desc << "急停";
    if (sts & 0x0080) desc << "跟随误差超限";
    if (sts & 0x0100) desc << "正软限位";
    if (sts & 0x0200) desc << "负软限位";

    if (desc.isEmpty()) return QStringLiteral("正常");
    return desc.join(" | ");
}
