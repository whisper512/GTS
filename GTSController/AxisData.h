#pragma once

struct stuAxis
{
    short axisIndex;   // 轴号1-4；
    bool bAlarm;       // 报警
    bool bMError;      // 跟随误差越限
    bool bPosLimit;    // 正限位触发
    bool bNegLimit;    // 负限位触发
    bool bSmoothStop;  // 平滑停止
    bool bAbruptStop;  // 急停
    bool bServoOn;     // 伺服使能
    bool bMotion;      // 规划器运动
    double dCurPos;    // 当前位置
    double dPrfPos;    // 规划位置
    double dCurVel;    // 当前速度
    double dPrfVel;    // 规划速度
    double dCurAcc;    // 当前加速度
    double dPrfAcc;    // 规划加速度
    long lPrfMode;     // 运动模式
    long AxisStatus;   // 轴状态

    stuAxis() {
        axisIndex = 0;
        bAlarm = false;
        bMError = false;
        bPosLimit = false;
        bNegLimit = false;
        bSmoothStop = false;
        bAbruptStop = false;
        bServoOn = false;
        bMotion = false;
        dCurPos = 0.0;
        dPrfPos = 0.0;
        dCurVel = 0.0;
        dPrfVel = 0.0;
        dCurAcc = 0.0;
        dPrfAcc = 0.0;
        lPrfMode = 0;
        AxisStatus = 0;
    }
    // 解析轴状态
    void parseStatus(long status) {
        AxisStatus = status;
        bAlarm = (status & 0x02) != 0;
        bMError = (status & 0x10) != 0;
        bPosLimit = (status & 0x20) != 0;
        bNegLimit = (status & 0x40) != 0;
        bSmoothStop = (status & 0x80) != 0;
        bAbruptStop = (status & 0x100) != 0;
        bServoOn = (status & 0x200) != 0;
        bMotion = (status & 0x400) != 0;
    }
};