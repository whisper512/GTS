Attribute VB_Name = "gts"

Public Const DLL_VERSION_0 As Integer = 2
Public Const DLL_VERSION_1 As Integer = 1
Public Const DLL_VERSION_2 As Integer = 0
Public Const DLL_VERSION_3 As Integer = 1
Public Const DLL_VERSION_4 As Integer = 5
Public Const DLL_VERSION_5 As Integer = 0
Public Const DLL_VERSION_6 As Integer = 6
Public Const DLL_VERSION_7 As Integer = 0
Public Const DLL_VERSION_8 As Integer = 7

Public Const MC_NONE As Integer = -1

Public Const MC_LIMIT_POSITIVE As Integer = 0
Public Const MC_LIMIT_NEGATIVE As Integer = 1
Public Const MC_ALARM As Integer = 2
Public Const MC_HOME As Integer = 3
Public Const MC_GPI As Integer = 4
Public Const MC_ARRIVE As Integer = 5
Public Const MC_MPG As Integer = 6

Public Const MC_ENABLE As Integer = 10
Public Const MC_CLEAR As Integer = 11
Public Const MC_GPO As Integer = 12

Public Const MC_DAC As Integer = 20
Public Const MC_STEP As Integer = 21
Public Const MC_PULSE As Integer = 22
Public Const MC_ENCODER As Integer = 23
Public Const MC_ADC As Integer = 24

Public Const MC_AXIS As Integer = 30
Public Const MC_PROFILE As Integer = 31
Public Const MC_CONTROL As Integer = 32

Public Const CAPTURE_HOME As Integer = 1
Public Const CAPTURE_INDEX As Integer = 2
Public Const CAPTURE_PROBE As Integer = 3
Public Const CAPTURE_HSIO0 As Integer = 6
Public Const CAPTURE_HSIO1 As Integer = 7
Public Const CAPTURE_HOME_GPI As Integer = 8

Public Const PT_MODE_STATIC As Integer = 0
Public Const PT_MODE_DYNAMIC As Integer = 1

Public Const PT_SEGMENT_NORMAL As Integer = 0
Public Const PT_SEGMENT_EVEN As Integer = 1
Public Const PT_SEGMENT_STOP As Integer = 2

Public Const GEAR_MASTER_ENCODER As Integer = 1
Public Const GEAR_MASTER_PROFILE As Integer = 2
Public Const GEAR_MASTER_AXIS As Integer = 3

Public Const FOLLOW_MASTER_ENCODER As Integer = 1
Public Const FOLLOW_MASTER_PROFILE As Integer = 2
Public Const FOLLOW_MASTER_AXIS As Integer = 3

Public Const FOLLOW_EVENT_START As Integer = 1
Public Const FOLLOW_EVENT_PASS As Integer = 2

Public Const GEAR_EVENT_START As Integer = 1
Public Const GEAR_EVENT_PASS As Integer = 2
Public Const GEAR_EVENT_AREA As Integer = 5

Public Const FOLLOW_SEGMENT_NORMAL As Integer = 0
Public Const FOLLOW_SEGMENT_EVEN As Integer = 1
Public Const FOLLOW_SEGMENT_STOP As Integer = 2
Public Const FOLLOW_SEGMENT_CONTINUE As Integer = 3

Public Const INTERPOLATION_AXIS_MAX = 4
Public Const CRD_FIFO_MAX = 4096
Public Const FIFO_MAX = 2
Public Const CRD_MAX = 2
Public Const CRD_OPERATION_DATA_EXT_MAX = 2

Public Const CRD_OPERATION_TYPE_NONE = 0
Public Const CRD_OPERATION_TYPE_BUF_IO_DELAY = 1
Public Const CRD_OPERATION_TYPE_LASER_ON = 2
Public Const CRD_OPERATION_TYPE_LASER_OFF = 3
Public Const CRD_OPERATION_TYPE_BUF_DA = 4
Public Const CRD_OPERATION_TYPE_LASER_CMD = 5
Public Const CRD_OPERATION_TYPE_LASER_FOLLOW = 6
Public Const CRD_OPERATION_TYPE_LMTS_ON = 7
Public Const CRD_OPERATION_TYPE_LMTS_OFF = 8
Public Const CRD_OPERATION_TYPE_SET_STOP_IO = 9
Public Const CRD_OPERATION_TYPE_BUF_MOVE = 10
Public Const CRD_OPERATION_TYPE_BUF_GEAR = 11
Public Const CRD_OPERATION_TYPE_SET_SEG_NUM = 12
Public Const CRD_OPERATION_TYPE_STOP_MOTION = 13
Public Const CRD_OPERATION_TYPE_SET_VAR_VALUE = 14
Public Const CRD_OPERATION_TYPE_JUMP_NEXT_SEG = 15
Public Const CRD_OPERATION_TYPE_SYNCH_PRF_POS = 16
Public Const CRD_OPERATION_TYPE_VIRTUAL_TO_ACTUAL = 17
Public Const CRD_OPERATION_TYPE_SET_USER_VAR = 18
Public Const CRD_OPERATION_TYPE_SET_DO_BIT_PULSE = 19
Public Const CRD_OPERATION_TYPE_BUF_COMPAREPULSE = 20
Public Const CRD_OPERATION_TYPE_LASER_ON_EX = 21
Public Const CRD_OPERATION_TYPE_LASER_OFF_EX = 22
Public Const CRD_OPERATION_TYPE_LASER_CMD_EX = 23
Public Const CRD_OPERATION_TYPE_LASER_FOLLOW_RATIO_EX = 24
Public Const CRD_OPERATION_TYPE_LASER_FOLLOW_MODE = 25
Public Const CRD_OPERATION_TYPE_LASER_FOLLOW_OFF = 26
Public Const CRD_OPERATION_TYPE_LASER_FOLLOW_OFF_EX = 27
Public Const CRD_OPERATION_TYPE_LASER_FOLLOW_SPLINE = 28
Public Const CRD_OPERATION_TYPE_MOTION_DATA = 29

Public Const CRD_OPERATION_TYPE_BUF_TREND = 50

Public Const CRD_OPERATION_TYPE_BUF_EVENT_ON = 70
Public Const CRD_OPERATION_TYPE_BUF_EVENT_OFF = 71

Public Const INTERPOLATION_MOTION_TYPE_LINE = 0
Public Const INTERPOLATION_MOTION_TYPE_CIRCLE = 1
Public Const INTERPOLATION_MOTION_TYPE_HELIX = 2
Public Const INTERPOLATION_MOTION_TYPE_CIRCLE_3D = 3

Public Const INTERPOLATION_CIRCLE_PLAT_XY = 0
Public Const INTERPOLATION_CIRCLE_PLAT_YZ = 1
Public Const INTERPOLATION_CIRCLE_PLAT_ZX = 2

Public Const INTERPOLATION_HELIX_CIRCLE_XY_LINE_Z = 0
Public Const INTERPOLATION_HELIX_CIRCLE_YZ_LINE_X = 1
Public Const INTERPOLATION_HELIX_CIRCLE_ZX_LINE_Y = 2

Public Const INTERPOLATION_CIRCLE_DIR_CW = 0
Public Const INTERPOLATION_CIRCLE_DIR_CCW = 1
Public Const COMPARE_PORT_HSIO As Integer = 0
Public Const COMPARE_PORT_GPO As Integer = 1

Public Const COMPARE2D_MODE_2D As Integer = 1
Public Const COMPARE2D_MODE_1D As Integer = 0

Public Const INTERFACEBOARD20 As Integer = 2
Public Const INTERFACEBOARD30 As Integer = 3

Public Const AXIS_LASER As Integer = 7
Public Const AXIS_LASER_EX As Integer = 8

Public Const LASER_CTRL_MODE_PWM1 As Integer = 0
Public Const LASER_CTRL_FREQUENCY As Integer = 1
Public Const LASER_CTRL_VOLTAGE As Integer = 2
Public Const LASER_CTRL_MODE_PWM2 As Integer = 3

Public Const CRD_BUFFER_MODE_DYNAMIC_DEFAULT = 0
Public Const CRD_BUFFER_MODE_DYNAMIC_KEEP = 1
Public Const CRD_BUFFER_MODE_STATIC_INPUT = 11
Public Const CRD_BUFFER_MODE_STATIC_READY = 12
Public Const CRD_BUFFER_MODE_STATIC_START = 13

Public Const CRD_SMOOTH_MODE_NONE = 0
Public Const CRD_SMOOTH_MODE_PERCENT = 1
Public Const CRD_SMOOTH_MODE_JERK = 2

Public Type TTrapPrm
    acc As Double
    dec As Double
    velStart As Double
    smoothTime As Integer
End Type

Public Type TJogPrm
    acc As Double
    dec As Double
    smooth As Double
End Type

Public Type TPid
    kp As Double
    ki As Double
    kd As Double
    kvff As Double
    kaff As Double

    integralLimit As Long
    derivativeLimit As Long
    limit As Integer
End Type

Public Type TThreadSts
    run As Integer
    errorValue As Integer
    dumb1 As Integer
    result As Double
    line As Integer
End Type

Public Type TVarInfo
    id As Integer
    dataType As Integer
    dumb1 As Integer
    dumb2 As Integer
    name0 As Double
    name1 As Double
    name2 As Double
    name3 As Double
End Type

Public Type TCompileInfo
    pFileName As String
    pLineNo1 As Integer
    pLineNo2 As Integer
    pMessage As String
End Type

Public Type TCrdPrm
    dimension As Integer
    profile1 As Integer
    profile2 As Integer
    profile3 As Integer
    profile4 As Integer
    profile5 As Integer
    profile6 As Integer
    profile7 As Integer
    profile8 As Integer
    dumb1 As Integer
    dumb2 As Integer
    dumb3 As Integer
    synVelMax As Double
    synAccMax As Double
    evenTime As Integer
    setOriginFlag As Integer
    originPos1 As Long
    originPos2 As Long
    originPos3 As Long
    originPos4 As Long
    originPos5 As Long
    originPos6 As Long
    originPos7 As Long
    originPos8 As Long
End Type

Public Type TCrdBufOperation
    flag As Integer
    delay As Integer
    doType As Integer
    doMask As Integer  '请用16进制表示，如&HFFF
    doValue As Integer  '请用16进制表示，如&HFFF
    dataExt1 As Integer
    dataExt2 As Integer
    dumb3 As Integer
End Type

Public Type TCrdData
    motionType As Integer
    circlePlat As Integer
    posX As Long
    posY As Long
    posZ As Long
    posA As Long
    radius As Double
    circleDir As Integer
    dumb0 As Integer
    dumb1 As Integer
    dumb2 As Integer
    lCenterX As Double
    lCenterY As Double
    lCenterZ As Double
    vel As Double
    acc As Double
    velEndZero As Integer
    dumb3 As Integer
    dumb4 As Integer
    dumb5 As Integer
    operation As TCrdBufOperation

    CosX As Double
    CosY As Double
    CosZ As Double
    CosA As Double
    velEnd As Double
    velEndAdjust As Double
    r As Double
End Type

Public Type TTrigger
    encoder As Integer
    probeType As Integer
    probeIndex As Integer
    offset As Integer
    windowOnly As Integer
    firstPosition As Long
    lastPosition As Long
End Type

Public Type TTriggerStatus
    execute As Integer
    done As Integer
    position As Long
End Type

Public Type TTriggerStatusEx
    execute As Integer
    done As Integer
    position As Long
    clock As Long
    loopCount As Long
End Type

Public Type T2DCompareData
    px As Integer
    py As Integer
End Type

Public Type T2DComparePrm
    encx As Integer
    ency As Integer
    source As Integer
    outputType As Integer
    startLevel As Integer
    time As Integer
    maxerr As Integer
    threshold As Integer
End Type

Public Type TCrdTime
		time As Double
		segmentUsed As Long
		segmentHead As Long
		segmentTail As Long
End Type

Public Type TCrdSmoothInfo
		enable As Integer
		smoothMode As Integer
		percent As Integer
		accStartPercent As Integer
		decEndPercent As Integer
		jerkMax As Double
End Type

Public Type TCrdSmooth
		percent As Integer
		accStartPercent As Integer
		decEndPercent As Integer
		reserve As Double
End Type

Public Declare Function GT_GetDllVersion Lib "gts.dll" (ByVal cardNum As Integer,ByRef pDllVersion As String) As Integer
Public Declare Function GT_SetCardNo Lib "gts.dll" (ByVal cardNum As Integer,ByVal index As Integer) As Integer
Public Declare Function GT_GetCardNo Lib "gts.dll" (ByVal cardNum As Integer,ByRef pIndex As Integer) As Integer

Public Declare Function GT_GetVersion Lib "gts.dll" (ByVal cardNum As Integer,ByRef pVersion As String) As Integer
Public Declare Function GT_GetInterfaceBoardSts Lib "gts.dll" (ByVal cardNum As Integer,ByRef pStatus As Integer) As Integer
Public Declare Function GT_SetInterfaceBoardSts Lib "gts.dll" (ByVal cardNum As Integer,ByVal interfaceType As Integer) As Integer

Public Declare Function GT_Open Lib "gts.dll" (ByVal cardNum As Integer,Optional ByVal channel As Integer = 0, Optional ByVal param As Integer = 1) As Integer
Public Declare Function GT_Close Lib "gts.dll" (ByVal cardNum As Integer) As Integer

Public Declare Function GT_LoadConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFile As String) As Integer

Public Declare Function GT_AlarmOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer) As Integer
Public Declare Function GT_AlarmOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer) As Integer
Public Declare Function GT_LmtsOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, Optional ByVal limitType As Integer = -1) As Integer
Public Declare Function GT_LmtsOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, Optional ByVal limitType As Integer = -1) As Integer
Public Declare Function GT_ProfileScale Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal alpha As Integer, ByVal beta As Integer) As Integer
Public Declare Function GT_EncScale Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal alpha As Integer, ByVal beta As Integer) As Integer
Public Declare Function GT_StepDir Lib "gts.dll" (ByVal cardNum As Integer,ByVal step As Integer) As Integer
Public Declare Function GT_StepPulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal step As Integer) As Integer
Public Declare Function GT_SetMtrBias Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer, ByVal bias As Integer) As Integer
Public Declare Function GT_GetMtrBias Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer, ByRef pBias As Integer) As Integer
Public Declare Function GT_SetMtrLmt Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer, ByVal limit As Integer) As Integer
Public Declare Function GT_GetMtrLmt Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer, ByRef pLimit As Integer) As Integer
Public Declare Function GT_EncSns Lib "gts.dll" (ByVal cardNum As Integer,ByVal sense As Integer) As Integer
Public Declare Function GT_EncOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer) As Integer
Public Declare Function GT_EncOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer) As Integer
Public Declare Function GT_SetPosErr Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal iError As Long) As Integer
Public Declare Function GT_GetPosErr Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByRef pError As Long) As Integer
Public Declare Function GT_SetStopDec Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal decSmoothStop As Double, ByVal decAbruptStop As Double) As Integer
Public Declare Function GT_GetStopDec Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pDecSmoothStop As Double, ByRef pDecAbruptStop As Double) As Integer
Public Declare Function GT_LmtSns Lib "gts.dll" (ByVal cardNum As Integer,ByVal sense As Integer) As Integer
Public Declare Function GT_CtrlMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal mode As Integer) As Integer
Public Declare Function GT_SetStopIo Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal stopType As Integer, ByVal inputType As Integer, ByVal inputIndex As Integer) As Integer
Public Declare Function GT_GpiSns Lib "gts.dll" (ByVal cardNum As Integer,ByVal sense As Integer) As Integer
Public Declare Function GT_SetAdcFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal filterTime As Integer) As Integer
Public Declare Function GT_SetAxisPrfVelFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal filterNumExp As Integer) As Integer
Public Declare Function GT_GetAxisPrfVelFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pFilterNumExp As Integer) As Integer
Public Declare Function GT_SetAxisEncVelFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal filterNumExp As Integer) As Integer
Public Declare Function GT_GetAxisEncVelFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pFilterNumExp As Integer) As Integer
Public Declare Function GT_SetAxisInputShaping Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal enable As Integer, ByVal count As Integer, ByVal k As Double) As Integer

Public Declare Function GT_SetDo Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer, ByVal value As Long) As Integer
Public Declare Function GT_SetDoBit Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer, ByVal doIndex As Integer, ByVal value As Integer) As Integer
Public Declare Function GT_GetDo Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer, ByRef pValue As Long) As Integer
Public Declare Function GT_SetDoBitReverse Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer, ByVal doIndex As Integer, ByVal value As Integer, ByVal reverseTime As Integer) As Integer
Public Declare Function GT_SetDoMask Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer, ByVal doMask As Integer, ByVal value As Long) As Integer
Public Declare Function GT_EnableDoBitPulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer, ByVal doIndex As Integer, ByVal highLevelTime As Integer, ByVal lowLevelTime As Integer, ByVal pulseNum As Long, ByVal firstLevel As Integer) As Integer
Public Declare Function GT_DisableDoBitPulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer, ByVal doIndex As Integer) As Integer

Public Declare Function GT_GetDi Lib "gts.dll" (ByVal cardNum As Integer,ByVal diType As Integer, ByRef pValue As Long) As Integer
Public Declare Function GT_GetDiReverseCount Lib "gts.dll" (ByVal cardNum As Integer,ByVal diType As Integer, ByVal diIndex As Integer, ByRef pReverseCount As Long, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_SetDiReverseCount Lib "gts.dll" (ByVal cardNum As Integer,ByVal diType As Integer, ByVal diIndex As Integer, ByRef pReverseCount As Long, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_GetDiRaw Lib "gts.dll" (ByVal cardNum As Integer,ByVal diType As Integer, ByRef pValue As Long) As Integer

Public Declare Function GT_SetDac Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer, ByRef pValue As Integer, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_GetDac Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer, ByRef pValue As Integer, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer

Public Declare Function GT_GetAdc Lib "gts.dll" (ByVal cardNum As Integer,ByVal adc As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetAdcValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal adc As Integer, ByRef pValue As Integer, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer

Public Declare Function GT_SetEncPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByVal encPos As Long) As Integer
Public Declare Function GT_GetEncPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetEncPosPre Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetEncVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer

Public Declare Function GT_SetCaptureMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByVal mode As Integer) As Integer
Public Declare Function GT_GetCaptureMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pMode As Integer, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_GetCaptureStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pStatus As Integer, ByRef pValue As Long, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_SetCaptureSense Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByVal mode As Integer, ByVal sense As Integer) As Integer
Public Declare Function GT_ClearCaptureStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer) As Integer
Public Declare Function GT_SetCaptureRepeat Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByVal count As Integer) As Integer
Public Declare Function GT_GetCaptureRepeatStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pCount As Integer) As Integer
Public Declare Function GT_GetCaptureRepeatPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pValue As Long, ByVal startNum As Integer, ByVal count As Integer) As Integer

Public Declare Function GT_SetCaptureEncoder Lib "gts.dll" (ByVal cardNum As Integer,ByVal trigger As Integer, ByVal encoder As Integer) As Integer
Public Declare Function GT_GetCaptureWidth Lib "gts.dll" (ByVal cardNum As Integer,ByVal trigger As Integer, ByRef pWidth As Integer, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_GetCaptureHomeGpi Lib "gts.dll" (ByVal cardNum As Integer,ByVal trigger As Integer, ByRef pHomeSts As Integer, ByRef pHomePos As Integer, ByRef pGpiSts As Integer, ByRef pGpiPos As Integer, Optional ByVal count As Integer = 1) As Integer

Public Declare Function GT_Reset Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_GetClock Lib "gts.dll" (ByVal cardNum As Integer,ByRef pClock As Long, Optional ByRef pLoop As Long = 0) As Integer
Public Declare Function GT_GetClockHighPrecision Lib "gts.dll" (ByVal cardNum As Integer,ByRef pClock As Long) As Integer

Public Declare Function GT_GetSts Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pSts As Long, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_ClrSts Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_AxisOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer) As Integer
Public Declare Function GT_AxisOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer) As Integer
Public Declare Function GT_Stop Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long, ByVal stopOption As Long) As Integer
Public Declare Function GT_SetPrfPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal prfPos As Long) As Integer
Public Declare Function GT_SynchAxisPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long) As Integer
Public Declare Function GT_ZeroPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, Optional ByVal count As Integer = 1) As Integer

Public Declare Function GT_SetSoftLimit Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal positive As Long, ByVal negative As Long) As Integer
Public Declare Function GT_GetSoftLimit Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pPositive As Long, ByRef pNegative As Long) As Integer
Public Declare Function GT_SetAxisBand Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal band As Long, ByVal time As Long) As Integer
Public Declare Function GT_GetAxisBand Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pBand As Long, ByRef pTime As Long) As Integer
Public Declare Function GT_SetBacklash Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal compValue As Long, ByVal compChangeValue As Double, ByVal compDir As Long) As Integer
Public Declare Function GT_GetBacklash Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pCompValue As Long, ByRef pCompChangeValue As Double, ByRef pCompDir As Long) As Integer
Public Declare Function GT_SetLeadScrewComp Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal n As Integer, ByVal startPos As Long, ByVal lenPos As Long, ByRef pCompPos As Long, ByRef pCompNeg As Long) As Integer
Public Declare Function GT_EnableLeadScrewComp Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal mode As Integer) As Integer
Public Declare Function GT_GetCompensate Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pPitchError As Double, ByRef pCrossError As Double, ByRef pBacklashError As Double, ByRef pEncPos As Double, ByRef pPrfPos As Double) As Integer

Public Declare Function GT_EnableGantry Lib "gts.dll" (ByVal cardNum As Integer,ByVal gantryMaster As Integer, ByVal gantrySlave As Integer, ByVal masterKp As Double, ByVal slaveKp As Double) As Integer
Public Declare Function GT_DisableGantry Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_SetGantryErrLmt Lib "gts.dll" (ByVal cardNum As Integer,ByVal gantryErrLmt As Long) As Integer
Public Declare Function GT_GetGantryErrLmt Lib "gts.dll" (ByVal cardNum As Integer,ByRef pGantryErrLmt As Long) As Integer
Public Declare Function GT_ZeroGantryPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal gantryMaster As Integer, ByVal gantrySlave As Integer) As Integer

Public Declare Function GT_GetPrfPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetPrfVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetPrfAcc Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetPrfMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pValue As Long, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer

Public Declare Function GT_GetAxisPrfPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetAxisPrfVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetAxisPrfAcc Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetAxisEncPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetAxisEncVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetAxisEncAcc Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer
Public Declare Function GT_GetAxisError Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double, Optional ByVal count As Integer = 1, Optional ByRef pClock As Long = 0) As Integer

Public Declare Function GT_SetLongVar Lib "gts.dll" (ByVal cardNum As Integer,ByVal index As Integer, ByVal value As Long) As Integer
Public Declare Function GT_GetLongVar Lib "gts.dll" (ByVal cardNum As Integer,ByVal index As Integer, ByRef pValue As Long) As Integer
Public Declare Function GT_SetDoubleVar Lib "gts.dll" (ByVal cardNum As Integer,ByVal index As Integer, ByVal value As Double) As Integer
Public Declare Function GT_GetDoubleVar Lib "gts.dll" (ByVal cardNum As Integer,ByVal index As Integer, ByRef pValue As Double) As Integer

Public Declare Function GT_SetControlFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal index As Integer) As Integer
Public Declare Function GT_GetControlFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByRef pIndex As Integer) As Integer

Public Declare Function GT_SetPid Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal index As Integer, ByRef pPid As TPid) As Integer
Public Declare Function GT_GetPid Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal index As Integer, ByRef pPid As TPid) As Integer

Public Declare Function GT_SetKvffFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal index As Integer, ByVal kvffFilterExp As Integer, ByVal accMax As Double) As Integer
Public Declare Function GT_GetKvffFilter Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal index As Integer, ByRef pKvffFilterExp As Integer, ByRef pAccMax As Double) As Integer

Public Declare Function GT_Update Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long) As Integer
Public Declare Function GT_SetPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal pos As Long) As Integer
Public Declare Function GT_GetPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pPos As Long) As Integer
Public Declare Function GT_SetVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal vel As Double) As Integer
Public Declare Function GT_GetVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pVel As Double) As Integer

Public Declare Function GT_PrfTrap Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer) As Integer
Public Declare Function GT_SetTrapPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pPrm As TTrapPrm) As Integer
Public Declare Function GT_GetTrapPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pPrm As TTrapPrm) As Integer

Public Declare Function GT_PrfJog Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer) As Integer
Public Declare Function GT_SetJogPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pPrm As TJogPrm) As Integer
Public Declare Function GT_GetJogPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pPrm As TJogPrm) As Integer

Public Declare Function GT_PrfPt Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, Optional ByVal mode As Integer = PT_MODE_STATIC) As Integer
Public Declare Function GT_SetPtLoop Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal ptLoop As Long) As Integer
Public Declare Function GT_GetPtLoop Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pLoop As Long) As Integer
Public Declare Function GT_PtSpace Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pSpace As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_PtData Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal pos As Double, ByVal time As Long, Optional ByVal ptType As Integer = PT_SEGMENT_NORMAL, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_PtDataWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal pos As Double, ByVal time As Long, Optional ByVal ptType As Integer = PT_SEGMENT_NORMAL, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_PtClear Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_PtStart Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long, Optional ByVal fifoOption As Long = 0) As Integer
Public Declare Function GT_SetPtMemory Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal memory As Integer) As Integer
Public Declare Function GT_GetPtMemory Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pMemory As Integer) As Integer
Public Declare Function GT_PtGetSegNum Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pSegNum As Long) As Integer
Public Declare Function GT_SetPtPrecisionMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal precisionMode As Integer) As Integer
Public Declare Function GT_GetPtPrecisionMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pPrecisionMode As Integer) As Integer
Public Declare Function GT_SetPtVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal velLast As Double, ByVal fifo As Integer) As Integer
Public Declare Function GT_SetPtLink Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal fifo As Integer, ByVal list As Integer) As Integer
Public Declare Function GT_GetPtLink Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef fifo As Integer, ByRef pList As Integer) As Integer
Public Declare Function GT_PtDoBit Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal doType As Integer, ByVal index As Integer, ByVal value As Integer, ByVal fifo As Integer) As Integer
Public Declare Function GT_PtAo Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal aoType As Integer, ByVal index As Integer, ByVal value As Double, ByVal fifo As Integer) As Integer

Public Declare Function GT_PrfGear Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, Optional ByVal dir As Integer = 0) As Integer
Public Declare Function GT_SetGearMaster Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal masterIndex As Integer, Optional ByVal masterType As Integer = GEAR_MASTER_PROFILE, Optional ByVal masterItem As Integer = 0) As Integer
Public Declare Function GT_GetGearMaster Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pMasterIndex As Integer, Optional ByRef pMasterType As Integer = 0, Optional ByRef pMasterItem As Integer = 0) As Integer
Public Declare Function GT_SetGearRatio Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal masterEven As Long, ByVal slaveEven As Long, Optional ByVal masterSlope As Long = 0) As Integer
Public Declare Function GT_GetGearRatio Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pMasterEven As Long, ByRef pSlaveEven As Long, Optional ByRef pMasterSlope As Long = 0) As Integer
Public Declare Function GT_GearStart Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long) As Integer
Public Declare Function GT_SetGearEvent Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal gearEvent As Integer, ByVal startPara0 As Long, ByVal startPara1 As Long) As Integer
Public Declare Function GT_GetGearEvent Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pGearEvent As Integer, ByRef startPara0 As Long, ByRef startPara1 As Long) As Integer

Public Declare Function GT_PrfFollow Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, Optional ByVal dir As Integer = 0) As Integer
Public Declare Function GT_SetFollowMaster Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal masterIndex As Integer, Optional ByVal masterType As Integer = FOLLOW_MASTER_PROFILE, Optional ByVal masterItem As Integer = 0) As Integer
Public Declare Function GT_GetFollowMaster Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pMasterIndex As Integer, Optional ByRef pMasterType As Integer = 0, Optional ByRef pMasterItem As Integer = 0) As Integer
Public Declare Function GT_SetFollowLoop Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal followLoop As Long) As Integer
Public Declare Function GT_GetFollowLoop Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pLoop As Long) As Integer
Public Declare Function GT_SetFollowEvent Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal followEvent As Integer, ByVal masterDir As Integer, Optional ByVal pos As Long = 0) As Integer
Public Declare Function GT_GetFollowEvent Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pEvent As Integer, ByRef pMasterDir As Integer, Optional ByRef pPos As Long = 0) As Integer
Public Declare Function GT_FollowSpace Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pSpace As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_FollowData Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal masterSegment As Long, ByVal slaveSegment As Double, Optional ByVal followType As Integer = FOLLOW_SEGMENT_NORMAL, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_FollowClear Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_FollowStart Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long, ByVal fifoOption As Long) As Integer
Public Declare Function GT_FollowSwitch Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long) As Integer
Public Declare Function GT_SetFollowMemory Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal memory As Integer) As Integer
Public Declare Function GT_GetFollowMemory Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pMemory As Integer) As Integer
Public Declare Function GT_GetFollowStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pFifoNum As Integer, ByRef pSwitchStatus As Integer) As Integer
Public Declare Function GT_SetFollowPhasing Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal profilePhasing As Integer) As Integer
Public Declare Function GT_GetFollowPhasing Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pProfilePhasing As Integer) As Integer

Public Declare Function GT_Compile Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFileName As String, ByRef pWrongInfo As TCompileInfo) As Integer
Public Declare Function GT_Download Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFileName As String) As Integer

Public Declare Function GT_GetFunId Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFunName As String, ByRef pFunId As Integer) As Integer
Public Declare Function GT_Bind Lib "gts.dll" (ByVal cardNum As Integer,ByVal thread As Integer, ByVal funId As Integer, ByVal page As Integer) As Integer

Public Declare Function GT_RunThread Lib "gts.dll" (ByVal cardNum As Integer,ByVal thread As Integer) As Integer
Public Declare Function GT_StopThread Lib "gts.dll" (ByVal cardNum As Integer,ByVal thread As Integer) As Integer
Public Declare Function GT_PauseThread Lib "gts.dll" (ByVal cardNum As Integer,ByVal thread As Integer) As Integer

Public Declare Function GT_GetThreadSts Lib "gts.dll" (ByVal cardNum As Integer,ByVal thread As Integer, ByRef pThreadSts As TThreadSts) As Integer

Public Declare Function GT_GetVarId Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFunName As String, ByVal pVarName As String, ByRef pVarInfo As TVarInfo) As Integer
Public Declare Function GT_SetVarValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal page As Integer, ByRef pVarInfo As TVarInfo, ByRef pValue As Double, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_GetVarValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal page As Integer, ByRef pVarInfo As TVarInfo, ByRef pValue As Double, Optional ByVal count As Integer = 1) As Integer

Public Declare Function GT_SetCrdMapBase Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal base As Integer) As Integer
Public Declare Function GT_GetCrdMapBase Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pBase As Integer) As Integer
Public Declare Function GT_SetCrdSmooth Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pCrdSmooth As TCrdSmooth) As Integer
Public Declare Function GT_GetCrdSmooth Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pCrdSmooth As TCrdSmooth) As Integer
Public Declare Function GT_SetCrdJerk Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal jerkMax As Double) As Integer
Public Declare Function GT_GetCrdJerk Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pJerkMax As Double) As Integer
Public Declare Function GT_SetCrdPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pCrdPrm As TCrdPrm) As Integer
Public Declare Function GT_GetCrdPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pCrdPrm As TCrdPrm) As Integer
Public Declare Function GT_SetArcAllowError Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal error As Double) As Integer
Public Declare Function GT_CrdSpace Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pSpace As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_CrdData Lib "gts.dll" (ByVal cardNum As Integer, ByVal crd As Integer, ByVal pCrdData As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_CrdDataCircle Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pCrdData As TCrdData, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXY Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZ Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZA Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYG0 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZG0 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZAG0 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYR Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYC Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcYZR Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcYZC Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcZXR Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcZXC Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYZ Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal interX As Double, ByVal interY As Double, ByVal interZ As Double, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer

Public Declare Function GT_LnXYOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZAOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYG0Override2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZG0Override2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZAG0Override2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYROverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYCOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcYZROverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0)
Public Declare Function GT_ArcYZCOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcZXROverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0)
Public Declare Function GT_ArcZXCOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYRZ Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYCZ Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixYZRX Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0)
Public Declare Function GT_HelixYZCX Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXRY Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXCY Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYRZOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYCZOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixYZRXOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixYZCXOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXRYOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXCYOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZAWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYG0WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZG0WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZAG0WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYRWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYCWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcYZRWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcYZCWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcZXRWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcZXCWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYZWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal interX As Double, ByVal interY As Double, ByVal interZ As Double, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZAOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYG0Override2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZG0Override2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_LnXYZAG0Override2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal a As Long, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYROverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcXYCOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcYZROverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcYZCOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcZXROverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_ArcZXCOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Long, ByVal x As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYRZWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYCZWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixYZRXWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixYZCXWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXRYWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXCYWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYRZOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixXYCZOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal xCenter As Double, ByVal yCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixYZRXOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixYZCXOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal yCenter As Double, ByVal zCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXRYOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal radius As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_HelixZXCYOverride2WN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Long, ByVal y As Long, ByVal z As Long, ByVal zCenter As Double, ByVal xCenter As Double, ByVal radius As Integer, ByVal synVel As Double, ByVal synAcc As Double, Optional ByVal velEnd As Double = 0, Optional ByVal segNum As Long = 0, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufTrend Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal trendSegNum As Long, ByVal trendDistance As Double, ByVal trendVelEnd As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufIO Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal doType As Integer, ByVal doMask As Integer, ByVal doValue As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufEnableDoBitPulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal doType As Integer, ByVal doIndex As Integer, ByVal highLevelTime As Integer, ByVal lowLevelTime As Integer, ByVal pulseNum As Long, ByVal firstLevel As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufDisableDoBitPulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal doType As Integer, ByVal doIndex As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufDelay Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal delayTime As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufDA Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal chn As Integer, ByVal daValue As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufLmtsOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal axis As Integer, ByVal limitType As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufLmtsOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal axis As Integer, ByVal limitType As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufSetStopIo Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal axis As Integer, ByVal stopType As Integer, ByVal inputType As Integer, ByVal inputIndex As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufMove Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal moveAxis As Integer, ByVal pos As Long, ByVal vel As Double, ByVal acc As Double, ByVal modal As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufGear Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal gearAxis As Integer, ByVal pos As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufGearPercent Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal gearAxis As Integer, ByVal pos As Long, ByVal accPercent As Integer, ByVal decPercent As Integer, Optional ByVal fifo As Integer = 0)
Public Declare Function GT_BufStopMotion Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0)
Public Declare Function GT_BufSetVarValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pageId As Integer, ByRef pVarInfo As TVarInfo, ByVal value As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufJumpNextSeg Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal axis As Integer, ByVal limitType As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufSynchPrfPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal encoder As Integer, ByVal profile As Integer, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufVirtualToActual Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0)
Public Declare Function GT_BufSetLongVar Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal index As Integer, ByVal value As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_BufSetDoubleVar Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal index As Integer, ByVal value As Double, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_CrdStart Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Integer, ByVal optionV As Integer) As Integer
Public Declare Function GT_CrdStartStep Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Integer, ByVal stepOption As Integer) As Integer
Public Declare Function GT_CrdStepMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Integer, ByVal modeOption As Integer) As Integer
Public Declare Function GT_SetOverride Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal synVelRatio As Double) As Integer
Public Declare Function GT_SetOverride2 Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal synVelRatio As Double) As Integer
Public Declare Function GT_InitLookAhead Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal fifo As Integer, ByVal T As Double, ByVal accMax As Double, ByVal n As Integer, ByRef pLookAheadBuf As TCrdData) As Integer
Public Declare Function GT_GetLookAheadSpace Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pSpace As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_GetLookAheadSegCount Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pSegCount As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_CrdClear Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal fifo As Integer) As Integer
Public Declare Function GT_CrdStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pRun As Integer, ByRef pSegment As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_SetUserSegNum Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal segNum As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_GetUserSegNum Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pSegment As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_GetUserSegNumWN Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pSegment As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_GetRemainderSegNum Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pSegment As Long, Optional ByVal fifo As Integer = 0) As Integer
Public Declare Function GT_SetCrdStopDec Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal decSmoothStop As Double, ByVal decAbruptStop As Double) As Integer
Public Declare Function GT_GetCrdStopDec Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pDecSmoothStop As Double, ByRef pDecAbruptStop As Double) As Integer
Public Declare Function GT_SetCrdLmtStopMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal lmtStopMode As Integer) As Integer
Public Declare Function GT_GetCrdLmtStopMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pLmtStopMode As Integer) As Integer
Public Declare Function GT_GetUserTargetVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pTargetVel As Double) As Integer
Public Declare Function GT_GetSegTargetPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pTargetPos As Long) As Integer
Public Declare Function GT_GetCrdPos Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pPos As Double) As Integer
Public Declare Function GT_GetCrdVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pSynVel As Double) As Integer
Public Declare Function GT_SetCrdSingleMaxVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pMaxVel As Double) As Integer
Public Declare Function GT_GetCrdSingleMaxVel Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pMaxVel As Double) As Integer
Public Declare Function GT_GetCmdCount Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pLmtStopMode As Integer, ByVal fifo As Integer) As Integer
Public Declare Function GT_BufLaserOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_BufLaserOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_BufLaserPrfCmd Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal laserPower As Double, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_BufLaserFollowRatio Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal ratio As Double, ByVal minPower As Double, ByVal maxPower As Double, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_BufLaserFollowMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal source As Integer = 0, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0, Optional ByVal startPower As Double = 0) As Integer
Public Declare Function GT_BufLaserFollowOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_BufLaserFollowSpline Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal tableId As Integer, ByVal minPower As Double, ByVal maxPower As Double, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer

Public Declare Function GT_PrfPvt Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer) As Integer
Public Declare Function GT_SetPvtLoop Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal loopValue As Long) As Integer
Public Declare Function GT_GetPvtLoop Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pLoopCount As Long, ByRef pLoop As Long) As Integer
Public Declare Function GT_PvtStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByRef pTableId As Integer, ByRef pTime As Double, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_PvtStart Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long) As Integer
Public Declare Function GT_PvtTableSelect Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer, ByVal tableId As Integer) As Integer

Public Declare Function GT_PvtTable Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal count As Long, ByRef pTime As Double, ByRef pPos As Double, ByRef pVel As Double) As Integer
Public Declare Function GT_PvtTableEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal count As Long, ByRef pTime As Double, ByRef pPos As Double, ByRef pVelBegin As Double, ByRef pVelEnd As Double) As Integer
Public Declare Function GT_PvtTableComplete Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal count As Long, ByRef pTime As Double, ByRef pPos As Double, ByRef pA As Double, ByRef pB As Double, ByRef pC As Double, Optional ByVal velBegin As Double = 0, Optional ByVal velEnd As Double = 0) As Integer
Public Declare Function GT_PvtTablePercent Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal count As Long, ByRef pTime As Double, ByRef pPos As Double, ByRef pPercent As Double, Optional ByVal velBegin As Double = 0) As Integer
Public Declare Function GT_PvtPercentCalculate Lib "gts.dll" (ByVal cardNum As Integer,ByVal n As Long, ByRef pTime As Double, ByRef pPos As Double, ByRef pPercent As Double, ByVal velBegin As Double, ByRef pVel As Double) As Integer
Public Declare Function GT_PvtTableContinuous Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal count As Long, ByRef pPos As Double, ByRef pVel As Double, ByRef pPercent As Double, ByRef pVelMax As Double, ByRef pAcc As Double, ByRef pDec As Double, ByVal timeBegin As Double) As Integer
Public Declare Function GT_PvtContinuousCalculate Lib "gts.dll" (ByVal cardNum As Integer,ByVal n As Long, ByRef pPos As Double, ByRef pVel As Double, ByRef pPercent As Double, ByRef pVelMax As Double, ByRef pAcc As Double, ByRef pDec As Double, ByRef pTime As Double) As Integer
Public Declare Function GT_PvtTableMovePercent Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal distance As Long, ByVal vm As Double, ByVal acc As Double, ByVal pa1 As Double, ByVal pa2 As Double, ByVal dec As Double, ByVal pd1 As Double, ByVal pd2 As Double, ByRef pVel As Double, ByRef pAcc As Double, ByRef pDec As Double, ByRef pTime As Double) As Integer
Public Declare Function GT_PvtTableMovePercentEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal distance As Long, ByVal vm As Double, ByVal acc As Double, ByVal pa1 As Double, ByVal pa2 As Double, ByVal ma As Double, ByVal dec As Double, ByVal pd1 As Double, ByVal pd2 As Double, ByVal md As Double, ByRef pVel As Double, ByRef pAcc As Double, ByRef pDec As Double, ByRef pTime As Double) As Integer

Public Declare Function GT_HomeInit Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_Home Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal pos As Long, ByVal vel As Double, ByVal acc As Double, ByVal offset As Long) As Integer
Public Declare Function GT_Index Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal pos As Long, ByVal offset As Long) As Integer
Public Declare Function GT_HomeStop Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal pos As Long, ByVal vel As Double, ByVal acc As Double) As Integer
Public Declare Function GT_HomeSts Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pStatus As Integer) As Integer

Public Declare Function GT_HandwheelInit Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_SetHandwheelStopDec Lib "gts.dll" (ByVal cardNum As Integer,ByVal slave As Integer, ByVal decSmoothStop As Double, ByVal decAbruptStop As Double) As Integer
Public Declare Function GT_StartHandwheel Lib "gts.dll" (ByVal cardNum As Integer,ByVal slave As Integer, ByVal master As Integer, ByVal masterEven As Integer, ByVal slaveEven As Integer, ByVal intervalTime As Integer, ByVal acc As Double, ByVal dec As Double, ByVal vel As Double, ByVal stopWaitTime As Integer) As Integer
Public Declare Function GT_EndHandwheel Lib "gts.dll" (ByVal cardNum As Integer,ByVal slave As Integer) As Integer

Public Declare Function GT_SetTrigger Lib "gts.dll" (ByVal cardNum As Integer,ByVal i As Integer, ByRef pTrigger As TTrigger) As Integer
Public Declare Function GT_GetTrigger Lib "gts.dll" (ByVal cardNum As Integer,ByVal i As Integer, ByRef pTrigger As TTrigger) As Integer
Public Declare Function GT_GetTriggerStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal i As Integer, ByRef pTriggerStatus As TTriggerStatus, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_GetTriggerStatusEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal i As Integer, ByRef pTriggerStatusEx As TTriggerStatusEx, Optional ByVal count As Integer = 1) As Integer
Public Declare Function GT_ClearTriggerStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal i As Integer) As Integer

Public Declare Function GT_SetComparePort Lib "gts.dll" (ByVal cardNum As Integer,ByVal channel As Integer, ByVal hsio0 As Integer, ByVal hsio1 As Integer) As Integer

Public Declare Function GT_ComparePulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal level As Integer, ByVal outputType As Integer, ByVal time As Integer) As Integer
Public Declare Function GT_CompareStop Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_CompareStatus Lib "gts.dll" (ByVal cardNum As Integer,ByRef pStatus As Integer, ByRef pCount As Long) As Integer
Public Declare Function GT_CompareData Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByVal source As Integer, ByVal pulseType As Integer, ByVal startLevel As Integer, ByVal time As Integer, ByRef pBuf1() As Long, ByVal count1 As Integer, ByRef pBuf2() As Long, ByVal count2 As Integer) As Integer
Public Declare Function GT_CompareLinear Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByVal channel As Integer, ByVal startPos As Long, ByVal repeatTimes As Long, ByVal interval As Long, ByVal time As Integer, ByVal source As Integer) As Integer
Public Declare Function GT_CompareContinuePulseMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer, ByVal count As Integer, ByVal standTime As Integer) As Integer

Public Declare Function GT_SetEncResponseCheck Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal dacThreshold As Integer, ByVal minEncVel As Double, ByVal time As Long) As Integer
Public Declare Function GT_GetEncResponseCheck Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByRef pDacThreshold As Integer, ByRef pMinEncVel As Double, ByRef pTime As Long) As Integer
Public Declare Function GT_EnableEncResponseCheck Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer) As Integer
Public Declare Function GT_DisableEncResponseCheck Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer) As Integer

Public Declare Function GT_2DCompareMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer, ByVal mode As Integer) As Integer
Public Declare Function GT_2DComparePulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer, ByVal level As Integer, ByVal outputType As Integer, ByVal time As Integer) As Integer
Public Declare Function GT_2DCompareStop Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer)
Public Declare Function GT_2DCompareClear Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer)
Public Declare Function GT_2DCompareStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer, ByRef pStatus As Integer, ByRef pCount As Long, ByRef pFifo As Integer, ByRef pFifoCount As Integer, Optional ByRef pBufCount As Integer = 0) As Integer
Public Declare Function GT_2DCompareSetPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer, ByRef pPrm As T2DComparePrm) As Integer
Public Declare Function GT_2DCompareData Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer, ByVal count As Integer, ByRef pBuf As T2DCompareData, ByVal fifo As Integer) As Integer
Public Declare Function GT_2DCompareStart Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer) As Integer
Public Declare Function GT_2DCompareClearData Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer) As Integer
Public Declare Function GT_2DCompareSetPreOutTime Lib "gts.dll" (ByVal cardNum As Integer,ByVal chn As Integer, ByVal preOutputTime As Double) As Integer

Public Declare Function GT_SetAxisMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal mode As Integer) As Integer
Public Declare Function GT_GetAxisMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal pMode As Integer) As Integer
Public Declare Function GT_SetHSIOOpt Lib "gts.dll" (ByVal cardNum As Integer,ByVal value As Integer, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_GetHSIOOpt Lib "gts.dll" (ByVal cardNum As Integer,ByRef pValue As Integer, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_LaserPowerMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal laserPowerMode As Integer, ByVal maxValue As Double, ByVal minValue As Double, Optional ByVal channel As Integer = 0, Optional ByVal delaymode As Integer = 0) As Integer
Public Declare Function GT_LaserPrfCmd Lib "gts.dll" (ByVal cardNum As Integer,ByVal outputCmd As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_LaserOutFrq Lib "gts.dll" (ByVal cardNum As Integer,ByVal outFrq As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetPulseWidth Lib "gts.dll" (ByVal cardNum As Integer,ByVal width As Long, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetWaitPulse Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer, ByVal waitPulseFrq As Double, ByVal waitPulseDuty As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetPreVltg Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer, ByVal voltageValue As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetLevelDelay Lib "gts.dll" (ByVal cardNum As Integer,ByVal offDelay As Integer, ByVal onDelay As Integer, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_EnaFPK Lib "gts.dll" (ByVal cardNum As Integer,ByVal time1 As Integer, ByVal time2 As Integer, ByVal laserOffDelay As Integer, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_DisFPK Lib "gts.dll" (ByVal cardNum As Integer,Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetLaserDisMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer, ByVal source As Integer, ByRef pPos As Long, ByRef pScale As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetLaserDisRatio Lib "gts.dll" (ByVal cardNum As Integer,ByRef pRatio As Double, ByVal minPower As Double, ByVal maxPower As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetWaitPulseEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer, ByVal waitPulseFrq As Double, ByVal waitPulseDuty As Double) As Integer
Public Declare Function GT_SetLaserMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer) As Integer
Public Declare Function GT_SetLaserFollowSpline Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal n As Long, ByRef pX As Double, ByRef pY As Double, ByVal beginValue As Double, ByVal endValue As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_GetLaserFollowSpline Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableId As Integer, ByVal n As Long, ByRef pX As Double, ByRef pY As Double, ByRef pA As Double, ByRef pB As Double, ByRef pC As Double, ByRef pCount As Long, Optional ByVal channel As Integer = 0) As Integer

'ExtMul
Public Declare Function GT_OpenExtMdl Lib "gts.dll" (ByVal cardNum As Integer,Optional ByRef pDllName As String) As Integer
Public Declare Function GT_CloseExtMdl Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_SwitchtoCardNoExtMdl Lib "gts.dll" (ByVal cardNum As Integer,ByVal card As Integer) As Integer
Public Declare Function GT_ResetExtMdl Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_LoadExtConfig Lib "gts.dll" (ByVal cardNum As Integer,ByRef pFileName As String) As Integer
Public Declare Function GT_SetExtIoValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal value As Integer) As Integer
Public Declare Function GT_GetExtIoValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByRef pValue As Integer) As Integer
Public Declare Function GT_SetExtIoBit Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal index As Integer, ByVal value As Integer) As Integer
Public Declare Function GT_GetExtIoBit Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal index As Integer, ByRef pValue As Integer) As Integer
Public Declare Function GT_GetExtAdValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal chn As Integer, ByRef pValue As Integer) As Integer
Public Declare Function GT_GetExtAdVoltage Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal chn As Integer, ByRef pValue As Double) As Integer
Public Declare Function GT_SetExtDaValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal chn As Integer, ByVal value As Integer) As Integer
Public Declare Function GT_SetExtDaVoltage Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal chn As Integer, ByVal value As Double) As Integer
Public Declare Function GT_GetStsExtMdl Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByVal chn As Integer, ByRef pStatus As Integer) As Integer
Public Declare Function GT_GetExtDoValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal mdl As Integer, ByRef pValue As Integer) As Integer
Public Declare Function GT_GetExtMdlMode Lib "gts.dll" (ByVal cardNum As Integer,ByRef pMode As Integer) As Integer
Public Declare Function GT_SetExtMdlMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer) As Integer
Public Declare Function GT_UploadConfig Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function GT_DownloadConfig Lib "gts.dll" (ByVal cardNum As Integer) As Integer

Public Declare Function GT_GetUuid Lib "gts.dll" (ByVal cardNum As Integer,ByRef pCode As String, ByVal count As Integer) As Integer
Public Declare Function GT_SetUuid Lib "gts.dll" (ByVal cardNum As Integer,ByRef pCode As String, ByVal count As Integer) As Integer

'2D Compensate
Public Type TCompensate2DTable
     count1 As Integer
     count2 As Integer
     posBegin1 As Long
     posBegin2 As Long
     step1 As Long
     step2 As Long
End Type
Public Type TCompensate2D
     enable As Integer
     tableIndex As Integer
     axisType1 As Integer
     axisType2 As Integer
     axisIndex1 As Integer
     axisIndex2 As Integer
End Type
Public Declare Function GT_SetCompensate2DTable Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableIndex As Integer, ByRef pTable As TCompensate2DTable, ByRef pData As Long, Optional ByVal externComp As Integer = 0) As Integer
Public Declare Function GT_GetCompensate2DTable Lib "gts.dll" (ByVal cardNum As Integer,ByVal tableIndex As Integer, ByRef pTable As TCompensate2DTable, Optional ByRef pExternComp As Integer) As Integer
Public Declare Function GT_SetCompensate2D Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pComp2d As TCompensate2D) As Integer
Public Declare Function GT_GetCompensate2D Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pComp2d As TCompensate2D) As Integer
Public Declare Function GT_GetCompensate2DValue Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pValue As Double) As Integer

'Smart Home
Public Const HOME_STAGE_IDLE As Integer = 0
Public Const HOME_STAGE_START As Integer = 1
Public Const HOME_STAGE_ON_HOME_LIMIT_ESCAPE As Integer = 2
Public Const HOME_STAGE_SEARCH_LIMIT As Integer = 10
Public Const HOME_STAGE_SEARCH_LIMIT_STOP As Integer = 11
Public Const HOME_STAGE_SEARCH_LIMIT_ESCAPE As Integer = 13
Public Const HOME_STAGE_SEARCH_LIMIT_RETURN As Integer = 15
Public Const HOME_STAGE_SEARCH_LIMIT_RETURN_STOP As Integer = 16
Public Const HOME_STAGE_SEARCH_HOME As Integer = 20
Public Const HOME_STAGE_SEARCH_HOME_STOP As Integer = 22
Public Const HOME_STAGE_SEARCH_HOME_RETURN As Integer = 25
Public Const HOME_STAGE_SEARCH_INDEX As Integer = 30
Public Const HOME_STAGE_SEARCH_GPI As Integer = 40
Public Const HOME_STAGE_SEARCH_GPI_RETURN As Integer = 45
Public Const HOME_STAGE_GO_HOME As Integer = 80
Public Const HOME_STAGE_END As Integer = 100
Public Const HOME_ERROR_NONE As Integer = 0
Public Const HOME_ERROR_NOT_TRAP_MODE As Integer = 1
Public Const HOME_ERROR_DISABLE As Integer = 2
Public Const HOME_ERROR_ALARM As Integer = 3
Public Const HOME_ERROR_STOP As Integer = 4
Public Const HOME_ERROR_STAGE As Integer = 5
Public Const HOME_ERROR_HOME_MODE As Integer = 6
Public Const HOME_ERROR_SET_CAPTURE_HOME As Integer = 7
Public Const HOME_ERROR_NO_HOME As Integer = 8
Public Const HOME_ERROR_SET_CAPTURE_INDEX As Integer = 9
Public Const HOME_ERROR_NO_INDEX As Integer = 10
Public Const HOME_MODE_LIMIT As Integer = 10
Public Const HOME_MODE_LIMIT_HOME As Integer = 11
Public Const HOME_MODE_LIMIT_INDEX As Integer = 12
Public Const HOME_MODE_LIMIT_HOME_INDEX As Integer = 13
Public Const HOME_MODE_HOME As Integer = 20
Public Const HOME_MODE_HOME_INDEX As Integer = 22
Public Const HOME_MODE_INDEX As Integer = 30
Public Const HOME_MODE_FORCED_HOME As Integer = 40
Public Const HOME_MODE_FORCED_HOME_INDEX As Integer = 41
Public Type THomePrm
     mode As Integer
     moveDir As Integer
     indexDir As Integer
     edge As Integer
     triggerIndex As Integer
     pad1_1 As Integer
     pad1_2 As Integer
     pad1_3 As Integer
     velHigh As Double
     velLow As Double
     acc As Double
     dec As Double
     smoothTime As Integer
     pad2_1 As Integer
     pad2_2 As Integer
     pad2_3 As Integer
     homeOffset As Long
     searchHomeDistance As Long
     searchIndexDistance As Long
     escapeStep As Long
     pad3_1 As Long
     pad3_2 As Long
     pad3_3 As Long
End Type
Public Type THomeStatus
     run As Integer
     stage As Integer
     iError As Integer
     pad1 As Integer
     capturePos As Long
     targetPos As Long
End Type
Public Declare Function GT_GoHome Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pHomePrm As THomePrm) As Integer
Public Declare Function GT_GetHomePrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pHomePrm As THomePrm) As Integer
Public Declare Function GT_GetHomeStatus Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pHomeStatus As THomeStatus) As Integer

'Extern Control
Public Type TControlConfigEx
     refType As Integer
     refIndex As Integer
     feedbackType As Integer
     feedbackIndex As Integer
     errorLimit As Long
     feedbackSmooth As Integer
     controlSmooth As Integer
End Type
Public Declare Function GT_SetControlConfigEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByRef pControl As TControlConfigEx) As Integer
Public Declare Function GT_GetControlConfigEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByRef pControl As TControlConfigEx) As Integer

'Adc filter
Public Type TAdcConfig
     active As Integer
     reverse As Integer
     a As Double
     b As Double
     filterMode As Integer
End Type
Public Declare Function GT_SetAdcConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal adc As Integer, ByRef pAdc As TAdcConfig) As Integer
Public Declare Function GT_GetAdcConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal adc As Integer, ByRef pAdc As TAdcConfig) As Integer
Public Declare Function GT_SetAdcFilterPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal adc As Integer, ByVal k As Double) As Integer
Public Declare Function GT_GetAdcFilterPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal adc As Integer, ByRef pk As Double) As Integer

'Superimposed
Public Declare Function GT_SetControlSuperimposed Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByVal superimposedType As Integer, ByVal superimposedIndex As Integer) As Integer
Public Declare Function GT_GetControlSuperimposed Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer, ByRef pSuperimposedType As Integer, ByRef pSuperimposedIndex As Integer) As Integer

''
Public Declare Function GT_ZeroLaserOnTime Lib "gts.dll" (ByVal cardNum As Integer,ByVal channel As Integer) As Integer
Public Declare Function GT_GetLaserOnTime Lib "gts.dll" (ByVal cardNum As Integer,ByVal channel As Integer, ByRef pTime As Long) As Integer

Public Declare Function GT_SetProfileScale Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal alpha As Long, ByVal beta As Long) As Integer
Public Declare Function GT_GetProfileScale Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pAlpha As Long, ByRef pBeta As Long) As Integer
Public Declare Function GT_SetEncoderScale Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByVal alpha As Long, ByVal beta As Long) As Integer
Public Declare Function GT_GetEncoderScale Lib "gts.dll" (ByVal cardNum As Integer,ByVal encoder As Integer, ByRef pAlpha As Long, ByRef pBeta As Long) As Integer

Public Declare Function GT_MultiAxisOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long) As Integer
Public Declare Function GT_MultiAxisOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal mask As Long) As Integer
Public Declare Function GT_SetAxisOnDelayTime Lib "gts.dll" (ByVal cardNum As Integer,ByVal ms As Integer) As Integer
Public Declare Function GT_GetAxisOnDelayTime Lib "gts.dll" (ByVal cardNum As Integer,ByRef pMs As Integer) As Integer

Public Declare Function GT_SetLaserDisTable1D Lib "gts.dll" (ByVal cardNum As Integer,ByVal count As Integer, ByRef pRatio As Double, ByRef pPos As Double, ByVal minPower As Double, ByVal maxPower As Double,ByRef pLimitPower As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetLaserDisTable2D Lib "gts.dll" (ByVal cardNum As Integer,ByRef axisIndex As Integer, ByRef count As Integer, ByRef pRatio As Double, ByRef pXPos As Integer, ByRef pYPos As Integer,ByVal minPower As Double, ByVal maxPower As Double, ByRef pLimitPower As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetLaserDisTable2DEx Lib "gts.dll" (ByVal cardNum As Integer,ByRef axisIndex As Integer, ByRef count As Integer, ByRef pRatio As Double, ByRef posBegin As Integer, ByRef posStep As Integer,ByVal minPower As Double, ByVal maxPower As Double, ByRef pLimitPower As Double, Optional ByVal channel As Integer = 0) As Integer
Public Declare Function GT_SetLaserCrdMap Lib "gts.dll" (ByVal cardNum As Integer,ByVal channel As Integer, ByVal map As Integer) As Integer
Public Declare Function GT_GetLaserCrdMap Lib "gts.dll" (ByVal cardNum As Integer,ByVal channel As Integer, ByRef pMap As Integer) As Integer

'AutoFocus
Public Declare Function GT_AutoFocus Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer, ByVal kp As Double, ByVal reverse As Integer, ByVal chanel As Integer) As Integer
Public Declare Function GT_SetAutoFocusRefVol Lib "gts.dll" (ByVal cardNum As Integer,ByVal refVol As Double, ByVal maxVol As Double, ByVal minVol As Double, ByVal chanel As Integer) As Integer
Public Declare Function GT_GetAutoFocusStatus Lib "gts.dll" (ByVal cardNum As Integer,ByRef pStatus As Integer, ByVal count As Integer) As Integer
Public Declare Function GT_ConfigAutoFocus Lib "gts.dll" (ByVal cardNum As Integer,ByVal chnAdc As Integer, ByVal chanel As Integer) As Integer
Public Declare Function GT_SetAutoFocusAuxPrm Lib "gts.dll" (ByVal cardNum As Integer,ByVal kf As Double, ByVal kd As Double, ByVal limitKd As Double, ByVal chanel As Integer) As Integer

Public Declare Function GT_Delay Lib "gts.dll" (ByVal cardNum As Integer,ByVal time As Integer) As Integer
Public Declare Function GT_DelayHighPrecision Lib "gts.dll" (ByVal cardNum As Integer,ByVal time As Integer) As Integer

Public Declare Function GT_SetCrdBufferMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal bufferMode As Integer, ByVal fifo As Integer) As Integer
Public Declare Function GT_GetCrdBufferMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pBufferMode As Integer, ByVal fifo As Integer) As Integer
Public Declare Function GT_GetCrdSegmentTime Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal segmentIndex As Long, ByRef pSegmentTime As Double, ByVal pSegmentNumber As Long, ByVal fifo As Integer) As Integer
Public Declare Function GT_GetCrdTime Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pTime As TCrdTime, ByVal fifo As Integer) As Integer

Public Declare Function GT_SetLeadScrewLink Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByVal link As Integer) As Integer
Public Declare Function GT_GetLeadScrewLink Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer, ByRef pLink As Integer) As Integer