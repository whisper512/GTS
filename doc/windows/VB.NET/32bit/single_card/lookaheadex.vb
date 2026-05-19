Module gts_la
    Public Const LA_AXIS_NUM As Short = 8
    Public Const LA_WORK_AXIS_NUM As Short = 6
    Public Const LA_MACHINE_AXIS_NUM As Short = 5

    Public Const AXIS_LIMIT_NONE As Short = 0
    Public Const AXIS_LIMIT_MAX_VEL As Short = 1
    Public Const DAXIS_LIMIT_MAX_ACC As Short = 2
    Public Const AXIS_LIMIT_MAX_DV As Short = 4
    Public Const KIN_MSG_BUFFER_SIZE As Short = 32

    '工件坐标系下轨迹是否限制速度模式
    Public Enum EWorkLimitMode
        WORK_LIMIT_INVALID = 0        '不限制
        WORK_LIMIT_VALID        '限制生效
    End Enum

    '设置的速度定义规则
    Public Enum EVelSettingDef
        NORMAL_DEF_VEL = 0        '输入为轴坐标系所有轴的合成速度
        NUM_DEF_VEL         '以NUM系统的规则定义
        CUT_DEF_VEL         '速度为切削速度
    End Enum
    '设置的加速度定义规则
    Public Enum EAccSettingDef
        NORMAL_DEF_ACC = 0               '输入即输出
        LONG_AXIS_ACC                  '长轴最大速度
    End Enum

    '机床类型
    Public Enum EMachineMode
        NORMAL_THREE_AXIS = 0     '标准三轴机床模式
        MULTI_AXES         '多轴联动模式
        FIVE_AXIS          '五轴机床模式，轴坐标系为主，工件坐标系为辅
        FIVE_AXIS_WORK          '五轴机床模式，工件坐标系为主，轴坐标系为辅
        ROBOT
    End Enum

    '前瞻参数结构体
    Public Structure TLookAheadParameter
        Dim lookAheadNum As Integer                 '前瞻段数
        Dim time As Double                          '时间常数
        Dim radiusRatio As Double                   '曲率限制调节参数
        Dim vMax1 As Double                        '各轴的最大速度
        Dim vMax2 As Double
        Dim vMax3 As Double
        Dim vMax4 As Double
        Dim vMax5 As Double
        Dim vMax6 As Double
        Dim vMax7 As Double
        Dim vMax8 As Double
        Dim aMax1 As Double                        '各轴的最大加速度
        Dim aMax2 As Double
        Dim aMax3 As Double
        Dim aMax4 As Double
        Dim aMax5 As Double
        Dim aMax6 As Double
        Dim aMax7 As Double
        Dim aMax8 As Double
        Dim DVMax1 As Double                       '各轴的最大速度变化量（在时间常数内）
        Dim DVMax2 As Double
        Dim DVMax3 As Double
        Dim DVMax4 As Double
        Dim DVMax5 As Double
        Dim DVMax6 As Double
        Dim DVMax7 As Double
        Dim DVMax8 As Double
        Dim scale1 As Double                       '各轴的脉冲当量
        Dim scale2 As Double
        Dim scale3 As Double
        Dim scale4 As Double
        Dim scale5 As Double
        Dim scale6 As Double
        Dim scale7 As Double
        Dim scale8 As Double
        Dim axisRelation1 As Short                 '输入坐标和内部坐标的对应关系
        Dim axisRelation2 As Short
        Dim axisRelation3 As Short
        Dim axisRelation4 As Short
        Dim axisRelation5 As Short
        Dim axisRelation6 As Short
        Dim axisRelation7 As Short
        Dim axisRelation8 As Short
        Dim machineCfgFileName As String            '机床配置文件名
    End Structure

    Public Structure RC_KIN_CONFIG
        Dim RobotType As Short
        Dim reserved1 As Short

        Dim KinParUse1 As Short
        Dim KinParUse2 As Short
        Dim KinParUse3 As Short
        Dim KinParUse4 As Short
        Dim KinParUse5 As Short
        Dim KinParUse6 As Short
        Dim KinParUse7 As Short
        Dim KinParUse8 As Short
        Dim KinParUse9 As Short
        Dim KinParUse10 As Short
        Dim KinParUse11 As Short
        Dim KinParUse12 As Short
        Dim KinParUse13 As Short
        Dim KinParUse14 As Short
        Dim KinParUse15 As Short
        Dim KinParUse16 As Short
        Dim KinParUse17 As Short
        Dim KinParUse18 As Short

        Dim KinPar1 As Double
        Dim KinPar2 As Double
        Dim KinPar3 As Double
        Dim KinPar4 As Double
        Dim KinPar5 As Double
        Dim KinPar6 As Double
        Dim KinPar7 As Double
        Dim KinPar8 As Double
        Dim KinPar9 As Double
        Dim KinPar10 As Double
        Dim KinPar11 As Double
        Dim KinPar12 As Double
        Dim KinPar13 As Double
        Dim KinPar14 As Double
        Dim KinPar15 As Double
        Dim KinPar16 As Double
        Dim KinPar17 As Double
        Dim KinPar18 As Double

        Dim KinLimitUse1 As Short
        Dim KinLimitUse2 As Short
        Dim KinLimitUse3 As Short
        Dim KinLimitUse4 As Short
        Dim KinLimitUse5 As Short
        Dim KinLimitUse6 As Short
        Dim KinLimitUse7 As Short
        Dim KinLimitUse8 As Short
        Dim KinLimitUse9 As Short
        Dim KinLimitUse10 As Short
        Dim KinLimitUse11 As Short
        Dim KinLimitUse12 As Short

        Dim KinLimitMin1 As Double
        Dim KinLimitMin2 As Double
        Dim KinLimitMin3 As Double
        Dim KinLimitMin4 As Double
        Dim KinLimitMin5 As Double
        Dim KinLimitMin6 As Double
        Dim KinLimitMin7 As Double
        Dim KinLimitMin8 As Double
        Dim KinLimitMin9 As Double
        Dim KinLimitMin10 As Double
        Dim KinLimitMin11 As Double
        Dim KinLimitMin12 As Double

        Dim KinLimitMax1 As Double
        Dim KinLimitMax2 As Double
        Dim KinLimitMax3 As Double
        Dim KinLimitMax4 As Double
        Dim KinLimitMax5 As Double
        Dim KinLimitMax6 As Double
        Dim KinLimitMax7 As Double
        Dim KinLimitMax8 As Double
        Dim KinLimitMax9 As Double
        Dim KinLimitMax10 As Double
        Dim KinLimitMax11 As Double
        Dim KinLimitMax12 As Double

        Dim KinLimitMinShift1 As Double
        Dim KinLimitMinShift2 As Double
        Dim KinLimitMinShift3 As Double
        Dim KinLimitMinShift4 As Double
        Dim KinLimitMinShift5 As Double
        Dim KinLimitMinShift6 As Double
        Dim KinLimitMinShift7 As Double
        Dim KinLimitMinShift8 As Double
        Dim KinLimitMinShift9 As Double
        Dim KinLimitMinShift10 As Double
        Dim KinLimitMinShift11 As Double
        Dim KinLimitMinShift12 As Double

        Dim KinLimitMaxShift1 As Double
        Dim KinLimitMaxShift2 As Double
        Dim KinLimitMaxShift3 As Double
        Dim KinLimitMaxShift4 As Double
        Dim KinLimitMaxShift5 As Double
        Dim KinLimitMaxShift6 As Double
        Dim KinLimitMaxShift7 As Double
        Dim KinLimitMaxShift8 As Double
        Dim KinLimitMaxShift9 As Double
        Dim KinLimitMaxShift10 As Double
        Dim KinLimitMaxShift11 As Double
        Dim KinLimitMaxShift12 As Double

        Dim AxisUse1 As Short
        Dim AxisUse2 As Short
        Dim AxisUse3 As Short
        Dim AxisUse4 As Short
        Dim AxisUse5 As Short
        Dim AxisUse6 As Short
        Dim AxisUse7 As Short
        Dim AxisUse8 As Short

        Dim AxisPosSignSwitch As String

        Dim AxisPosOffset1 As Double
        Dim AxisPosOffset2 As Double
        Dim AxisPosOffset3 As Double
        Dim AxisPosOffset4 As Double
        Dim AxisPosOffset5 As Double
        Dim AxisPosOffset6 As Double
        Dim AxisPosOffset7 As Double
        Dim AxisPosOffset8 As Double

        Dim CartUnitUse1 As Short
        Dim CartUnitUse2 As Short
        Dim CartUnitUse3 As Short
        Dim CartUnitUse4 As Short
        Dim CartUnitUse5 As Short
        Dim CartUnitUse6 As Short
        Dim CartPosKCSSignSwitch As String
        Dim reserved21 As Short
        Dim reserved22 As Short
        Dim reserved23 As Short
        Dim CartPosKCSOffset1 As Double
        Dim CartPosKCSOffset2 As Double
        Dim CartPosKCSOffset3 As Double
        Dim CartPosKCSOffset4 As Double
        Dim CartPosKCSOffset5 As Double
        Dim CartPosKCSOffset6 As Double
    End Structure

    Public Structure RC_ERROR_INTERFACE
        Dim Error1 As Char
        Dim ErrorID As Short
        Dim Message As String
    End Structure

    Public Structure RC_MSG_BUFFER_ELEMENT
        Dim ErrorID As Short
        Dim Message As String
        Dim LogTime As String
        Dim InternalID As Long
    End Structure

    Public Structure RC_MSG_BUFFER
        Dim LastMsgIndex As Short
        Dim MsgElement1 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement2 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement3 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement4 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement5 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement6 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement7 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement8 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement9 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement10 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement11 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement12 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement13 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement14 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement15 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement16 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement17 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement18 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement19 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement20 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement21 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement22 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement23 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement24 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement25 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement26 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement27 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement28 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement29 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement30 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement31 As RC_MSG_BUFFER_ELEMENT
        Dim MsgElement32 As RC_MSG_BUFFER_ELEMENT

        Dim LastMsgID As Long
    End Structure

    '旋转轴范围设置
    Public Structure TRotationAxisRange
        Dim primaryAxisRangeOn As Integer              '//第一旋转轴限定范围是否生效，0：不生效，1：生效
        Dim slaveAxisRangeOn As Integer                '//第二旋转轴限定范围是否生效，0：不生效，1：生效
        Dim maxPrimaryAngle As Double              '//第一旋转轴最大值
        Dim minPrimaryAngle As Double              '//第一旋转轴最小值
        Dim maxSlaveAngle As Double                '//第二旋转轴最大值
        Dim minSlaveAgnle As Double                '//第二旋转轴最小值
    End Structure

    '选解参数
    Public Enum EGroupSelect
        Continuous = 0
        Group_1
        Group_2
    End Enum

    Public Structure TPos
        Dim machinePos1 As Double
        Dim machinePos2 As Double
        Dim machinePos3 As Double
        Dim machinePos4 As Double
        Dim machinePos5 As Double
        Dim workPos1 As Double
        Dim workPos2 As Double
        Dim workPos3 As Double
        Dim workPos4 As Double
        Dim workPos5 As Double
        Dim workPos6 As Double
    End Structure

    Public Enum EVelMode
        T_CURVE = 0
        S_CURVE
        S_CURVE_NEW
        VEL_MODE_MAX = &H10000
    End Enum

    Public Enum OptimizeState
        OPT_OFF
        OPT_ON
    End Enum

    Public Enum OptimizeMethod
        NO_OPT
        OPT_BLENDING
        OPT_CIRCLEFITTING
        OPT_CUBICSPLINE
        OPT_BSPLINE
    End Enum

    Public Enum ErrorID
        INIT_ERROR                              '没有进行参数初始化
        PASSWORD_ERROR                          '密码错误，请在固高运动控制平台上运行
        INDATA_ERROR                            '输入数据错误（检查圆弧数据是否正确）
        PRE_PROCESS_ERROR
        TOOL_RADIUS_COMPENSATE_ERROR_INOUT      '刀具半径补偿错误：进入/结束刀补处不能是圆弧
        TOOL_RADIUS_COMPENSATE_ERROR_NOCROSS    '刀具半径补偿错误：数据不合理，无法计算交点
        USERDATA_ERROR
    End Enum

    Public Structure TOptimizeParamUser
        Dim usePathOptimize As OptimizeState    '是否使用路径优化：OPT_OFF:不使用	OPT_ON:使用

        Dim tolerance As Double             '公差(suggest: rough:0.1, pre-finish:0.05, finish:0.01)

        Dim optimizeMethod As OptimizeMethod   '选择曲线优化方式

        Dim keepLargeArc As OptimizeState      '是否保留大圆弧：OPT_OFF：不保留， OPT_ON：保留

        Dim blendingMinError As Double          'blending的最小设定误差

        Dim blendingMaxAngle As Double           'blending的最大角度限制（即当线段向量角度大于该角度时，不做blending，单位：度）

    End Structure

    Public Structure TErrorInfo
        Dim errorID As ErrorID
        Dim errorRowNum As Long
    End Structure

    Public Structure TPreStartPos
        Dim Pos1 As Double
        Dim Pos2 As Double
        Dim Pos3 As Double
        Dim Pos4 As Double
        Dim Pos5 As Double
        Dim Pos6 As Double
        Dim Pos7 As Double
        Dim Pos8 As Double
    End Structure

    Public Structure TBufIoDelayData
        Dim doType As UShort
        Dim doMask As UShort
        Dim doValue As UShort
        Dim delayTime As UShort
        Dim fifo As Short
    End Structure

    Public Structure TBufDoBitPulseData
        Dim doType As Short
        Dim doIndex As Short
        Dim highLevelTime As UShort
        Dim lowLevelTime As UShort
        Dim pulseNum As Integer
        Dim firstLevel As Short
        Dim fifo As Short
    End Structure

    Public Structure TBufDaData
        Dim channel As Short
        Dim daValue As Short
        Dim fifo As Short
    End Structure

    Public Structure TBufLaserData
        Dim channel As Short
        Dim fifo As Short
        Dim source As Short
        Dim laserPower As Double
        Dim ratio As Double
        Dim minPower As Double
        Dim maxPower As Double
        Dim tableId As Short
    End Structure

    Public Structure TBufGearData
        Dim axis As Short
        Dim deltaPos As Double
        Dim fifo As Short
        Dim smoothFlag As Short
        Dim accPercent As Short
        Dim decPercent As Short
    End Structure

    Public Structure TBufMoveData
        Dim axis As Short
        Dim pos As Double
        Dim vel As Double
        Dim acc As Double
        Dim modal As Short
        Dim fifo As Short
    End Structure

    Public Structure TBufSegNumData
        Dim segNum As Integer
        Dim fifo As Short
    End Structure

    Public Declare Function GT_SetupLookAheadCrd Lib "gts.dll" (ByVal crd As Short, ByVal machineMode As EMachineMode) As Short
    Public Declare Function GT_SetFollowAxisParaLa Lib "gts.dll" (ByVal crd As Short, ByRef pAxisLimitMode As Short, ByRef pVmax As Double, ByRef pAmax As Double, ByRef pDVmax As Double) As Short
    Public Declare Function GT_SetVelDefineModeLa Lib "gts.dll" (ByVal crd As Short, ByRef velDefMode As EVelSettingDef) As Short
    Public Declare Function GT_SetAxisLimitModeLa Lib "gts.dll" (ByVal crd As Short, ByRef pAxisLimitMode As Integer) As Short
    Public Declare Function GT_SetWorkLimitModeLa Lib "gts.dll" (ByVal crd As Short, ByRef workLimitMode As EWorkLimitMode) As Short
    Public Declare Function GT_SetAxisVelValidModeLa Lib "gts.dll" (ByVal crd As Short, ByVal velValidAxis As Integer) As Short
    Public Declare Function GT_SetVelSmoothMode Lib "gts.dll" (ByVal crd As Short, ByVal smoothMode As Integer) As Short
    Public Declare Function GT_SetArcAllowErrorLa Lib "gts.dll" (ByVal crd As Short, ByVal error1 As Double) As Short
    Public Declare Function GT_InitLookAheadEx Lib "gts.dll" (ByVal crd As Short, ByRef pLookAheadPara As TLookAheadParameter, ByVal fifo As Short, ByVal motionMode As Short, ByVal pPreStartPos As Integer) As Short
    Public Declare Function GT_PrintLACmdLa Lib "gts.dll" (ByVal crd As Short, ByVal printFlag As Integer, ByVal clearFile As Integer) As Short
    Public Declare Function GT_InitLookAheadPara Lib "gts.dll" (ByVal crd As Short, ByVal lookAheadNum As Integer, ByVal time As Double, ByVal radiusRatio As Double, ByVal scale As Double, ByVal fifo As Short) As Short

    Public Declare Function GT_LnXYEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_LnXYG0Ex Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_LnXYZEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_LnXYZG0Ex Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_LnXYZAEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_LnXYZAG0Ex Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_LnXYZACEx Lib "gts.dll" (ByVal crd As Short, ByRef pPos As Double, ByVal posMask As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_LnXYZACG0Ex Lib "gts.dll" (ByVal crd As Short, ByRef pPos As Double, ByVal posMask As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, ByVal fifo As Short) As Short

    Public Declare Function GT_LnXYZACUVWEx Lib "gts.dll" (ByVal crd As Short, ByRef pPos As Double, ByVal posMask As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_LnXYZACUVWG0Ex Lib "gts.dll" (ByVal crd As Short, ByRef pPos As Double, ByVal posMask As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, ByVal fifo As Short) As Short

    Public Declare Function GT_ArcXYREx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal radius As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_ArcYZREx Lib "gts.dll" (ByVal crd As Short, ByVal y As Double, ByVal z As Double, ByVal radius As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_ArcZXREx Lib "gts.dll" (ByVal crd As Short, ByVal z As Double, ByVal x As Double, ByVal radius As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_ArcXYCEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal xCenter As Double, ByVal yCenter As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_ArcYZCEx Lib "gts.dll" (ByVal crd As Short, ByVal y As Double, ByVal z As Double, ByVal yCenter As Double, ByVal zCenter As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_ArcZXCEx Lib "gts.dll" (ByVal crd As Short, ByVal z As Double, ByVal x As Double, ByVal zCenter As Double, ByVal xCenter As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_ArcXYZEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal interX As Double, ByVal interY As Double, ByVal interZ As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_HelixXYRZEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal radius As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_HelixXYCZEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal xCenter As Double, ByVal yCenter As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Short, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_BufDelayEx Lib "gts.dll" (ByVal crd As Short, ByVal delayTime As UShort, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_BufGearEx Lib "gts.dll" (ByVal crd As Short, ByVal gearAxis As Short, ByVal deltaPos As Double, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_BufMoveEx Lib "gts.dll" (ByVal crd As Short, ByVal moveAxis As Short, ByVal pos As Double, ByVal vel As Double, ByVal acc As Integer, ByVal modal As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_BufIOEx Lib "gts.dll" (ByVal crd As Short, ByVal doType As UShort, ByVal doMask As UShort, ByVal doValue As UShort, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_BufDAEx Lib "gts.dll" (ByVal crd As Short, ByVal chn As Short, ByVal daValue As Short, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_SetUserSegNumEx Lib "gts.dll" (ByVal crd As Short, ByVal segNum As Long, Optional ByVal fifo As Short = 0) As Short

    'Add By lin.ga 20150330
    Public Declare Function GT_BufLaserOnEx Lib "gts.dll" (ByVal crd As Short, Optional ByVal fifo As Short = 0, Optional ByVal channel As Short = 0) As Short
    Public Declare Function GT_BufLaserOffEx Lib "gts.dll" (ByVal crd As Short, Optional ByVal fifo As Short = 0, Optional ByVal channel As Short = 0) As Short
    Public Declare Function GT_BufLaserPrfCmdEx Lib "gts.dll" (ByVal crd As Short, ByVal laserPower As Double, Optional ByVal fifo As Short = 0, Optional ByVal channel As Short = 0) As Short
    Public Declare Function GT_BufLaserFollowRatioEx Lib "gts.dll" (ByVal crd As Short, ByVal ratio As Double, ByVal minPower As Double, ByVal maxPower As Double, Optional ByVal fifo As Short = 0, Optional ByVal channel As Short = 0) As Short
    Public Declare Function GT_BufLaserFollowModeEx Lib "gts.dll" (ByVal crd As Short, Optional ByVal source As Short = 0, Optional ByVal fifo As Short = 0, Optional ByVal channel As Short = 0) As Short
    Public Declare Function GT_BufLaserFollowSplineEx Lib "gts.dll" (ByVal crd As Short, ByVal tableId As Short, ByVal minPower As Double, ByVal maxPower As Double, Optional ByVal fifo As Short = 0, Optional ByVal channel As Short = 0) As Short
    Public Declare Function GT_BufLaserFollowOffEx Lib "gts.dll" (ByVal crd As Short, Optional ByVal fifo As Short = 0, Optional ByVal channel As Short = 0) As Short

    Public Declare Function GT_BufDisableDoBitPulseEx Lib "gts.dll" (ByVal crd As Short, ByVal doType As Short, ByVal doIndex As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_BufEnableDoBitPulseEx Lib "gts.dll" (ByVal crd As Short, ByVal doType As Short, ByVal doIndex As Short, ByVal highLevelTime As UShort, ByVal lowLevelTime As UShort, ByVal pulseNum As Long, ByVal firstLevel As Short, ByVal fifo As Short) As Short

    Public Declare Function GT_CrdDataEx Lib "gts.dll" (ByVal crd As Short, ByVal pCrdData As Integer, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_CrdDataExEx Lib "gts.dll" (ByVal crd As Short, ByVal pCrdData As Integer, Optional ByVal fifo As Short = 0) As Short
    Public Declare Function GT_GetLookAheadSegCountEx Lib "gts.dll" (ByVal crd As Short, ByRef pSegCount As Long, Optional ByVal fifo As Short = 0) As Short

    Public Declare Function GT_GetMotionTimeEx Lib "gts.dll" (ByVal crd As Short, ByRef pTime As Double, ByVal fifo As Short) As Short

    Public Declare Function GT_SetPathOptPara Lib "gts.dll" (ByVal crd As Short, ByRef optPrm As TOptimizeParamUser, ByVal fifo As Short) As Short
    Public Declare Function GT_GetPathOptErrorInfo Lib "gts.dll" (ByVal crd As Short, ByRef errorInfo As TErrorInfo, ByVal fifo As Short) As Short

    '5AXIS
    Public Declare Function GT_CrdRTCPOn Lib "gts.dll" (ByVal crd As Short, Optional ByVal crd As Short = 0) As Short
    Public Declare Function GT_CrdRTCPOff Lib "gts.dll" (ByVal crd As Short, Optional ByVal crd As Short = 0) As Short
    Public Declare Function GT_UpdateMachineBuildingFile Lib "gts.dll" (ByVal crd As Short, ByVal update As Integer) As Short
    Public Declare Function GT_InitialMachineBuilding Lib "gts.dll" (ByVal crd As Short, ByVal pMachineCfgFileName As String, ByRef machineCoordCenter As Double, ByRef workCoordCenter As Double, ByVal toolLength As Double) As Short
    Public Declare Function GT_SetRotationAxisRange Lib "gts.dll" (ByVal crd As Short, ByRef pRotationAxisRange As TRotationAxisRange) As Short
    Public Declare Function GT_SetInverseSolutionSelectPara Lib "gts.dll" (ByVal crd As Short, ByVal groupSelect As EGroupSelect, ByVal priorAxisSet As Integer) As Short
    Public Declare Function GT_MachineForwardTrans Lib "gts.dll" (ByVal crd As Short, ByRef pMachinePos As Double, ByRef pWorkPos As Double) As Short
    Public Declare Function GT_MachineRTCPTrans Lib "gts.dll" (ByVal crd As Short, ByRef pInputPos As Double, ByRef pMachinePos As Double, ByRef pWorkPos As Double) As Short
    Public Declare Function GT_MachineTransformation Lib "gts.dll" (ByVal crd As Short, ByVal posType As Integer, ByRef pPrePos As Double, ByRef pPos As Double, ByRef pPosNum As Integer, ByRef pReturnPos As TPos) As Short
    Public Declare Function GT_SetCompToolLength Lib "gts.dll" (ByVal crd As Short, ByVal compToolLength As Double) As Short
    Public Declare Function GT_SetCompWorkCoordOffset Lib "gts.dll" (ByVal crd As Short, ByRef pCompWorkOffset As Double) As Short
    Public Declare Function GT_SetNonlinearErrorControl Lib "gts.dll" (ByVal crd As Short, ByVal enable As Integer, ByVal nonlinearError As Double) As Short
    Public Declare Function GT_EnableDiscreateArc Lib "gts.dll" (ByVal crd As Short, ByVal enable As Short, ByVal arcError As Double) As Short
    Public Declare Function GT_StartXYCMachineMode Lib "gts.dll" (ByVal crd As Short, ByVal dir As Short, ByVal contactAngle As Double, ByVal rotationAngle As Double, ByRef pTranslation As Double, ByVal aValue As Double, ByVal fifo As Short) As Short
    Public Declare Function GT_EndXYCMachineMode Lib "gts.dll" (ByVal crd As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_SetWorkCrdPlane Lib "gts.dll" (ByVal crd As Short, ByVal enable As Short, ByRef pNormVector As Double, ByRef pPoint As Double, ByVal fifo As Short) As Short
    Public Declare Function GT_SetStartPointProcessMode Lib "gts.dll" (ByVal crd As Short, ByVal enable As Short, ByVal z As Double, ByVal fifo As Short) As Short
    Public Declare Function GT_InitialMachineBuildingEx Lib "gts.dll" (ByVal crd As Short, ByVal pMachineCfgFileName As String, ByRef machineCoordCenter As Double, ByRef workCoordCenter As Double, ByVal toolLength As Double) As Short
    Public Declare Function GT_SetWorkCrdLaserFollowMode Lib "gts.dll" (ByVal crd As Short, ByVal enbale As Short, ByVal fifo As Short, ByVal chn As Short) As Short
    Public Declare Function GT_ArcXYRACEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal a As Double, ByVal c As Double, ByVal radius As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Integer, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_ArcXYCACEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal a As Double, ByVal c As Double, ByVal xCenter As Double, ByVal yCenter As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Integer, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_ArcXYZACEx Lib "gts.dll" (ByVal crd As Short, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal c As Double, ByVal interX As Double, ByVal interY As Double, ByVal interZ As Double, ByVal interA As Double, ByVal interC As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Integer, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_ArcYZRACEx Lib "gts.dll" (ByVal crd As Short, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal c As Double, ByVal radius As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Integer, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_ArcYZCACEx Lib "gts.dll" (ByVal crd As Short, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal c As Double, ByVal yCenter As Double, ByVal zCenter As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Integer, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_ArcZXRACEx Lib "gts.dll" (ByVal crd As Short, ByVal z As Double, ByVal x As Double, ByVal a As Double, ByVal c As Double, ByVal radius As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Integer, ByVal override2 As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_ArcZXCACEx Lib "gts.dll" (ByVal crd As Short, ByVal z As Double, ByVal x As Double, ByVal a As Double, ByVal c As Double, ByVal zCenter As Double, ByVal xCenter As Double, ByVal circleDir As Short, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Integer, ByVal override2 As Short, ByVal fifo As Short) As Short

End Module