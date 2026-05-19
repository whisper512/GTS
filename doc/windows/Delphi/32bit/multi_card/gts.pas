unit gts;

interface

const  GTDll = 'gts.dll';

Const DLL_VERSION_0 = 2;
Const DLL_VERSION_1 = 1;
Const DLL_VERSION_2 = 0;
Const DLL_VERSION_3 = 1;
Const DLL_VERSION_4 = 5;
Const DLL_VERSION_5 = 0;
Const DLL_VERSION_6 = 6;
Const DLL_VERSION_7 = 0;
Const DLL_VERSION_8 = 7;

Const MC_NONE  = -1;

Const MC_LIMIT_POSITIVE = 0;
Const MC_LIMIT_NEGATIVE = 1 ;
Const MC_ALARM = 2;
Const MC_HOME = 3;
Const MC_GPI = 4;
Const MC_ARRIVE = 5;
Const MC_MPG = 6;

Const MC_ENABLE = 10;
Const MC_CLEAR = 11;
Const MC_GPO = 12;

Const MC_DAC = 20;
Const MC_STEP = 21;
Const MC_PULSE = 22;
Const MC_ENCODER = 23;
Const MC_ADC = 24;

Const MC_AXIS = 30;
Const MC_PROFILE = 31;
Const MC_CONTROL = 32;

Const CAPTURE_HOME = 1;
Const CAPTURE_INDEX = 2;
Const CAPTURE_PROBE = 3;
Const CAPTURE_HSIO0 = 6;
Const CAPTURE_HSIO1 = 7;
Const CAPTURE_HOME_GPI = 8;

Const PT_MODE_STATIC = 0;
Const PT_MODE_DYNAMIC = 1;

Const PT_SEGMENT_NORMAL = 0;
Const PT_SEGMENT_EVEN = 1;
Const PT_SEGMENT_STOP = 2;

Const GEAR_MASTER_ENCODER = 1;
Const GEAR_MASTER_PROFILE = 2;
Const GEAR_MASTER_AXIS = 3;

Const FOLLOW_MASTER_ENCODER = 1;
Const FOLLOW_MASTER_PROFILE = 2;
Const FOLLOW_MASTER_AXIS = 3;

Const FOLLOW_EVENT_START = 1;
Const FOLLOW_EVENT_PASS = 2;

Const GEAR_EVENT_START = 1;
Const GEAR_EVENT_PASS = 2;
Const GEAR_EVENT_AREA = 5;

Const FOLLOW_SEGMENT_NORMAL = 0;
Const FOLLOW_SEGMENT_EVEN = 1;
Const FOLLOW_SEGMENT_STOP = 2;
Const FOLLOW_SEGMENT_CONTINUE = 3;

Const INTERPOLATION_AXIS_MAX = 4;
Const CRD_FIFO_MAX = 4096;
Const FIFO_MAX = 2;
Const CRD_MAX = 2;
Const CRD_OPERATION_DATA_EXT_MAX = 2;

Const CRD_OPERATION_TYPE_NONE = 0;
Const CRD_OPERATION_TYPE_BUF_IO_DELAY = 1;
Const CRD_OPERATION_TYPE_LASER_ON = 2;
Const CRD_OPERATION_TYPE_LASER_OFF = 3;
Const CRD_OPERATION_TYPE_BUF_DA = 4;
Const CRD_OPERATION_TYPE_LASER_CMD = 5;
Const CRD_OPERATION_TYPE_LASER_FOLLOW = 6;
Const CRD_OPERATION_TYPE_LMTS_ON = 7;
Const CRD_OPERATION_TYPE_LMTS_OFF = 8;
Const CRD_OPERATION_TYPE_SET_STOP_IO = 9;
Const CRD_OPERATION_TYPE_BUF_MOVE = 10;
Const CRD_OPERATION_TYPE_BUF_GEAR = 11;
Const CRD_OPERATION_TYPE_SET_SEG_NUM = 12;
Const CRD_OPERATION_TYPE_STOP_MOTION = 13;
Const CRD_OPERATION_TYPE_SET_VAR_VALUE = 14;
Const CRD_OPERATION_TYPE_JUMP_NEXT_SEG = 15;
Const CRD_OPERATION_TYPE_SYNCH_PRF_POS = 16;
Const CRD_OPERATION_TYPE_VIRTUAL_TO_ACTUAL = 17;
Const CRD_OPERATION_TYPE_SET_USER_VAR = 18;
Const CRD_OPERATION_TYPE_SET_DO_BIT_PULSE = 19;
Const CRD_OPERATION_TYPE_BUF_COMPAREPULSE = 20;
Const CRD_OPERATION_TYPE_LASER_ON_EX = 21;
Const CRD_OPERATION_TYPE_LASER_OFF_EX = 22;
Const CRD_OPERATION_TYPE_LASER_CMD_EX = 23;
Const CRD_OPERATION_TYPE_LASER_FOLLOW_RATIO_EX = 24;
Const CRD_OPERATION_TYPE_LASER_FOLLOW_MODE = 25;
Const CRD_OPERATION_TYPE_LASER_FOLLOW_OFF = 26;
Const CRD_OPERATION_TYPE_LASER_FOLLOW_OFF_EX = 27;
Const CRD_OPERATION_TYPE_LASER_FOLLOW_SPLINE = 28;
Const CRD_OPERATION_TYPE_MOTION_DATA = 29;

Const CRD_OPERATION_TYPE_BUF_TREND = 50;

Const CRD_OPERATION_TYPE_BUF_EVENT_ON = 70;
Const CRD_OPERATION_TYPE_BUF_EVENT_OFF = 71;

Const INTERPOLATION_MOTION_TYPE_LINE = 0;
Const INTERPOLATION_MOTION_TYPE_CIRCLE = 1;
Const INTERPOLATION_MOTION_TYPE_HELIX = 2;
Const INTERPOLATION_MOTION_TYPE_CIRCLE_3D = 3;

Const INTERPOLATION_CIRCLE_PLAT_XY = 0;
Const INTERPOLATION_CIRCLE_PLAT_YZ = 1;
Const INTERPOLATION_CIRCLE_PLAT_ZX = 2;

Const INTERPOLATION_HELIX_CIRCLE_XY_LINE_Z = 0;
Const INTERPOLATION_HELIX_CIRCLE_YZ_LINE_X = 1;
Const INTERPOLATION_HELIX_CIRCLE_ZX_LINE_Y = 2;

Const INTERPOLATION_CIRCLE_DIR_CW = 0;
Const INTERPOLATION_CIRCLE_DIR_CCW = 1;
Const COMPARE_PORT_HSIO  = 0;
Const COMPARE_PORT_GPO  = 1;

Const  COMPARE2D_MODE_2D = 1;
Const  COMPARE2D_MODE_1D = 0;

Const  INTERFACEBOARD20 = 2;
Const  INTERFACEBOARD30 = 3;


Const AXIS_LASER = 7;
Const AXIS_LASER_EX = 8;

Const LASER_CTRL_MODE_PWM1 = 0;
Const LASER_CTRL_FREQUENCY = 1;
Const LASER_CTRL_VOLTAGE = 2;
Const LASER_CTRL_MODE_PWM2 = 3;

Const CRD_BUFFER_MODE_DYNAMIC_DEFAULT = 0;
Const CRD_BUFFER_MODE_DYNAMIC_KEEP = 1;
Const CRD_BUFFER_MODE_STATIC_INPUT = 11;
Const CRD_BUFFER_MODE_STATIC_READY = 12;
Const CRD_BUFFER_MODE_STATIC_START = 13;

Const CRD_SMOOTH_MODE_NONE = 0;
Const CRD_SMOOTH_MODE_PERCENT = 1;
Const CRD_SMOOTH_MODE_JERK = 2;

type TTrapPrm =record
    acc :Double;
    dec :Double;
    velStart :Double;
    smoothTime :SmallInt;
end;

type TJogPrm  =record
    acc :Double;
    dec :Double;
    smooth :Double;
end;

type TPid =record
    kp :Double;
    ki :Double;
    kd :Double;
    kvff :Double;
    kaff :Double;

    integralLimit:LongInt;
    derivativeLimit:LongInt;
    limit :SmallInt;
end;

type TThreadSts =record
    run : SmallInt;
    errorValue : SmallInt;
    result : Double;
    line : SmallInt;
end;

type TVarInfo = record
    id : SmallInt;
    dataType : SmallInt;
    name :array[0..31] of Byte;
end;

type TCompileInfo = record
	pFileName:String;
	pLineNo:^SmallInt;
	pMessage:String;
end;

type TCrdPrm = record
    dimension: SmallInt;
    profile:array[0..7] of SmallInt;
    synVelMax:Double;
    synAccMax:Double;
    evenTime: SmallInt;
    setOriginFlag:SmallInt;
    originPos:array[0..7] of LongInt;
end;

type TCrdBufOperation = record
    flag: SmallInt;
    delay:Word;
    doType: SmallInt;
    doMask:Word;
    doValue:Word;
    dataExt:array[0..1] of Word;
end;

type TCrdData = record
    motionType:SmallInt;
    circlePlat:SmallInt;
    pos:array[0..3] of LongInt;
    radius:Double;
    circleDir:SmallInt;
    center:array[0..2] of Double;
    vel:Double;
    acc:Double;
    velEndZero:SmallInt;
    operation:TCrdBufOperation;

    cos:array[0..3] of Double;
    velEnd:Double;
    velEndAdjust:Double;
    r:Double;
end;

type TTrigger = record
    encoder: SmallInt;
    probeType:SmallInt;
    probeIndex: SmallInt;
    offset:SmallInt;
    windowOnly:SmallInt;
    firstPosition:LongInt;
    lastPosition:LongInt;
end;

type TTriggerStatus = record
    execute:SmallInt;
    done:SmallInt;
    position:LongInt;
end;

type TriggerStatusEx = record
    execute:SmallInt;
    done:SmallInt;
    position:LongInt;
    clock:LongInt;
    loopCount:LongInt;
end;

type T2DCompareData = record
	px:LongInt;
	py:LongInt;
end;

type T2DComparePrm = record
	encx:SmallInt;
	ency:SmallInt;
	source:SmallInt;
	outputType:SmallInt;
	startLevel:SmallInt;
	time:SmallInt;
	maxerr:SmallInt;
	threshold:SmallInt;
end;

type TCrdTime = record
	time:Double;
	segmentUsed:LongInt
	segmentHead:LongInt
	segmentTail:LongInt
end;

type TCrdSmoothInfo = record
	enable:SmallInt
	smoothMode:SmallInt
	percent:SmallInt
	accStartPercent:SmallInt
	decEndPercent:SmallInt
	jerkMax:Double
end;

type TCrdSmooth = record
	percent:SmallInt
	accStartPercent:SmallInt
	decEndPercent:SmallInt
	reserve:Double
end;

function GT_GetDllVersion(cardNum:SmallInt ;out pDllVersion:String):SmallInt; stdcall; External GTDLL;
function GT_SetCardNo(cardNum:SmallInt ;index:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCardNo(cardNum:SmallInt ;out pIndex:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetVersion(cardNum:SmallInt ;out pVersion:String): SmallInt; stdcall; External GTDLL;
function GT_GetInterfaceBoardSts(cardNum:SmallInt ;out pStatus:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetInterfaceBoardSts(cardNum:SmallInt ;interfaceType:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_Open(cardNum:SmallInt ;channel:SmallInt=0;param:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_Close(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_LoadConfig(cardNum:SmallInt ;pFile:String): SmallInt; stdcall; External GTDLL;

function GT_AlarmOff(cardNum:SmallInt ;axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_AlarmOn(cardNum:SmallInt ;axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_LmtsOn(cardNum:SmallInt ;axis:SmallInt;limitType:SmallInt =-1): SmallInt; stdcall; External GTDLL;
function GT_LmtsOff(cardNum:SmallInt ;axis:SmallInt;limitType:SmallInt=-1): SmallInt; stdcall; External GTDLL;
function GT_ProfileScale(cardNum:SmallInt ;axis:SmallInt ;alpha:SmallInt ;beta:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_EncScale(cardNum:SmallInt ;axis:SmallInt ;alpha:SmallInt ;beta:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_StepDir(cardNum:SmallInt ;step:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_StepPulse(cardNum:SmallInt ;step:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_SetMtrBias(cardNum:SmallInt ;dac:SmallInt ;bias:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_GetMtrBias(cardNum:SmallInt ;dac:SmallInt ;out pBias:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_SetMtrLmt(cardNum:SmallInt ;dac:SmallInt ;limit:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_GetMtrLmt(cardNum:SmallInt ;dac:SmallInt ;out pLimit:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_EncSns(cardNum:SmallInt ;sense:Word ): SmallInt; stdcall; External GTDLL;
function GT_EncOn(cardNum:SmallInt ;encoder:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_EncOff(cardNum:SmallInt ;encoder:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_SetPosErr(cardNum:SmallInt ;control:SmallInt ;error:LongInt ): SmallInt; stdcall; External GTDLL;
function GT_GetPosErr(cardNum:SmallInt ;control:SmallInt ;out pError:LongInt ): SmallInt; stdcall; External GTDLL;
function GT_SetStopDec(cardNum:SmallInt ;profile:SmallInt ;decSmoothStop:Double ;decAbruptStop:Double ): SmallInt; stdcall; External GTDLL;
function GT_GetStopDec(cardNum:SmallInt ;profile:SmallInt ; out pDecSmoothStop:Double;out pDecAbruptStop:Double ): SmallInt; stdcall; External GTDLL;
function GT_LmtSns(cardNum:SmallInt ;sense:Word): SmallInt; stdcall; External GTDLL;
function GT_CtrlMode(cardNum:SmallInt ;axis:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetStopIo(cardNum:SmallInt ;axis:SmallInt;stopType:SmallInt;inputType:SmallInt;inputIndex:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GpiSns(cardNum:SmallInt ;sense:Word): SmallInt; stdcall; External GTDLL;
function GT_SetAdcFilter(cardNum:SmallInt ;adc:SmallInt;filterTime:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisPrfVelFilter(cardNum:SmallInt ;axis:SmallInt;filterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisPrfVelFilter(cardNum:SmallInt ;axis:SmallInt;out pFilterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisEncVelFilter(cardNum:SmallInt ;axis:SmallInt;filterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncVelFilter(cardNum:SmallInt ;axis:SmallInt;out pFilterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisInputShaping(cardNum:SmallInt ;axis:SmallInt;enable:SmallInt;count:SmallInt;k:Double): SmallInt; stdcall; External GTDLL;

function GT_SetDo(cardNum:SmallInt ;doType:SmallInt;value:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoBit(cardNum:SmallInt ;doType:SmallInt;doIndex:SmallInt;value:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetDo(cardNum:SmallInt ;doType : SmallInt; out pValue:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoBitReverse(cardNum:SmallInt ;doType : SmallInt; doIndex:SmallInt;value:SmallInt;reverseTime:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoMask(cardNum:SmallInt ;doType:SmallInt;doMask:Word;value:LongInt): SmallInt; stdcall; External GTDLL;
function GT_EnableDoBitPulse(cardNum:SmallInt ;doType:SmallInt;doIndex:SmallInt;highLevelTime:Word;lowLevelTime:Word;pulseNum:LongInt;firstLevel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_DisableDoBitPulse(cardNum:SmallInt ;doType:SmallInt;doIndex:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetDi(cardNum:SmallInt ;diType : SmallInt; out pValue:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetDiReverseCount(cardNum:SmallInt ;diType : SmallInt; diIndex : SmallInt; out pReverseCount : LongWord; count : SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_SetDiReverseCount(cardNum:SmallInt ;diType : SmallInt; diIndex : SmallInt; var pReverseCount : LongWord; count : SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetDiRaw(cardNum:SmallInt ;diType : SmallInt; out pValue:LongInt): SmallInt; stdcall; External GTDLL;

function GT_SetDac(cardNum:SmallInt ;dac : SmallInt;var pValue:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetDac(cardNum:SmallInt ;dac : SmallInt;out pValue:SmallInt;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_GetAdc(cardNum:SmallInt ;adc : SmallInt;out pValue:Double;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAdcValue(cardNum:SmallInt ;adc : SmallInt;out pValue:SmallInt;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetEncPos(cardNum:SmallInt ;encoder : SmallInt;encPos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetEncPos(cardNum:SmallInt ;encoder : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetEncPosPre(cardNum:SmallInt ;encoder:SmallInt;out pValue:Double;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetEncVel(cardNum:SmallInt ;encoder : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetCaptureMode(cardNum:SmallInt ;encoder : SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureMode(cardNum:SmallInt ;encoder : SmallInt; out pMode : SmallInt; count:SmallInt=1	): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureStatus(cardNum:SmallInt ;encoder : SmallInt; out pStatus : SmallInt; out pValue:LongInt;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_SetCaptureSense(cardNum:SmallInt ;encoder : SmallInt;mode:SmallInt;sense:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_ClearCaptureStatus(cardNum:SmallInt ;encoder : SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetCaptureRepeat(cardNum:SmallInt ;encoder:SmallInt;count:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureRepeatStatus(cardNum:SmallInt ;encoder:SmallInt;out pCount:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureRepeatPos(cardNum:SmallInt ;encoder:SmallInt;out pValue:LongInt;startNum:SmallInt;count:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetCaptureEncoder(cardNum:SmallInt ;trigger:SmallInt;encoder:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureWidth(cardNum:SmallInt ;trigger:SmallInt;out pWidth:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureHomeGpi(cardNum:SmallInt ;trigger:SmallInt;out pHomeSts:SmallInt;out pHomePos:SmallInt;out pGpiSts:SmallInt;out pGpiPos:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;

function GT_Reset(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetClock(cardNum:SmallInt ;Out pClock:LongWord;out pLoop:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetClockHighPrecision(cardNum:SmallInt ;Out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_GetSts(cardNum:SmallInt ;axis : SmallInt; out pSts:LongInt; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_ClrSts(cardNum:SmallInt ;axis:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_AxisOn(cardNum:SmallInt ;axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_AxisOff(cardNum:SmallInt ;axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_Stop(cardNum:SmallInt ;mask:LongInt;stopOption:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetPrfPos(cardNum:SmallInt ;profile : SmallInt;prfPos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SynchAxisPos(cardNum:SmallInt ;mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_ZeroPos(cardNum:SmallInt ;axis : SmallInt;count : SmallInt=1): SmallInt; stdcall; External GTDLL;

function GT_SetSoftLimit(cardNum:SmallInt ;axis : SmallInt;positive:LongInt;negative:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetSoftLimit(cardNum:SmallInt ;axis : SmallInt;out pPositive:LongInt;out pNegative:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisBand(cardNum:SmallInt ;axis : SmallInt;band:LongInt;time:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisBand(cardNum:SmallInt ;axis : SmallInt; out pBand:LongInt;out pTime:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetBacklash(cardNum:SmallInt ;axis : SmallInt;compValue:LongInt;compChangeValue:Double;compDir:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetBacklash(cardNum:SmallInt ;axis : SmallInt; out pCompValue:LongInt;out pCompChangeValue:Double;out pCompDir:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetLeadScrewComp(cardNum:SmallInt ;axis:SmallInt;n:SmallInt;startPos:LongInt;lenPos:LongInt;out pCompPos:LongInt;out pCompNeg:LongInt): SmallInt; stdcall; External GTDLL;
function GT_EnableLeadScrewComp(cardNum:SmallInt ;axis:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate(cardNum:SmallInt ;axis:SmallInt;out pPitchError:Double;out pCrossError:Double;out pBacklashError:Double;out pEncPos:Double;out pPrfPos:Double): SmallInt; stdcall; External GTDLL;

function GT_EnableGantry(cardNum:SmallInt ;gantryMaster:SmallInt;gantrySlave:SmallInt;masterKp:Double;slaveKp:Double): SmallInt; stdcall; External GTDLL;
function GT_DisableGantry(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetGantryErrLmt(cardNum:SmallInt ;gantryErrLmt:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetGantryErrLmt(cardNum:SmallInt ;out pGantryErrLmt:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetPrfMode(cardNum:SmallInt ;profile : SmallInt; out pValue:LongInt;count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_GetPrfPos(cardNum:SmallInt ;profile : SmallInt; out pValue:Double; count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetPrfVel(cardNum:SmallInt ;profile : SmallInt; out pValue:Double; count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetPrfAcc(cardNum:SmallInt ;profile : SmallInt; out pValue:Double; count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetPrfMode(cardNum:SmallInt ;profile : SmallInt; out pValue:LongInt;count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_GetAxisPrfPos(cardNum:SmallInt ;axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisPrfVel(cardNum:SmallInt ;axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisPrfAcc(cardNum:SmallInt ;axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncPos(cardNum:SmallInt ;axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncVel(cardNum:SmallInt ;axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncAcc(cardNum:SmallInt ;axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisError(cardNum:SmallInt ;axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetLongVar(cardNum:SmallInt ;index:SmallInt;value:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetLongVar(cardNum:SmallInt ;index:SmallInt;out pValue:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoubleVar(cardNum:SmallInt ;index:SmallInt;pValue:Double): SmallInt; stdcall; External GTDLL;
function GT_GetDoubleVar(cardNum:SmallInt ;index:SmallInt;out pValue:Double): SmallInt; stdcall; External GTDLL;

function GT_SetControlFilter(cardNum:SmallInt ;control : SmallInt;index:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetControlFilter(cardNum:SmallInt ;control : SmallInt;out pIndex:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetPid(cardNum:SmallInt ;control : SmallInt;index : SmallInt; var pPid:TPid): SmallInt; stdcall; External GTDLL;
function GT_GetPid(cardNum:SmallInt ;control : SmallInt;index : SmallInt; out pPid:TPid): SmallInt; stdcall; External GTDLL;

function GT_SetKvffFilter(cardNum:SmallInt ;control:SmallInt;index:SmallInt;kvffFilterExp:SmallInt;accMax:Double): SmallInt; stdcall; External GTDLL;
function GT_GetKvffFilter(cardNum:SmallInt ;control:SmallInt;index:SmallInt;out pKvffFilterExp:SmallInt;out pAccMax:Double): SmallInt; stdcall; External GTDLL;

function GT_Update(cardNum:SmallInt ;mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetPos(cardNum:SmallInt ;profile : SmallInt;pos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetPos(cardNum:SmallInt ;profile : SmallInt; out pPos:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_SetVel(cardNum:SmallInt ;profile : SmallInt;vel:Double): SmallInt; stdcall; External GTDLL;
function GT_GetVel(cardNum:SmallInt ;profile : SmallInt; out pVel:Double): SmallInt; stdcall; External GTDLL;

function GT_PrfTrap(cardNum:SmallInt ;profile:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetTrapPrm(cardNum:SmallInt ;profile : SmallInt; var pPrm:TTrapPrm): SmallInt; stdcall; External GTDLL;
function GT_GetTrapPrm(cardNum:SmallInt ;profile : SmallInt; out pPrm:TTrapPrm): SmallInt; stdcall; External GTDLL;

function GT_PrfJog(cardNum:SmallInt ;profile:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetJogPrm(cardNum:SmallInt ;profile : SmallInt; var pPrm:TJogPrm): SmallInt; stdcall; External GTDLL;
function GT_GetJogPrm(cardNum:SmallInt ;profile : SmallInt; out pPrm:TJogPrm): SmallInt; stdcall; External GTDLL;

function GT_PrfPt(cardNum:SmallInt ;profile : SmallInt; mode:SmallInt = PT_MODE_STATIC): SmallInt; stdcall; External GTDLL;
function GT_SetPtLoop(cardNum:SmallInt ;profile : SmallInt;ptLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_GetPtLoop(cardNum:SmallInt ;profile : SmallInt; out pLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_PtSpace(cardNum:SmallInt ;profile : SmallInt; out pSpace:SmallInt; fifo:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_PtData(cardNum:SmallInt ;profile : SmallInt;pos:Double;time:LongInt; mytype:SmallInt = PT_SEGMENT_NORMAL;fifo:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_PtDataWN(cardNum:SmallInt ;profile:SmallInt;pos:Double;time:LongInt;ptDataType:SmallInt=PT_SEGMENT_NORMAL;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_PtClear(cardNum:SmallInt ;profile : SmallInt; fifo:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_PtStart(cardNum:SmallInt ;mask:LongInt;fifoOption:LongInt = 0): SmallInt; stdcall; External GTDLL;
function GT_SetPtMemory(cardNum:SmallInt ;profile : SmallInt; memory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetPtMemory(cardNum:SmallInt ;profile : SmallInt; out pMemory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PtGetSegNum(cardNum:SmallInt ;profile:SmallInt;out pSegNum:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetPtPrecisionMode(cardNum:SmallInt ;profile:SmallInt;precisionMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetPtPrecisionMode(cardNum:SmallInt ;profile:SmallInt;out pPrecisionMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetPtVel(cardNum:SmallInt ;profile:SmallInt;velLast:Double;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetPtLink(cardNum:SmallInt ;profile:SmallInt;fifo:SmallInt;list:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetPtLink(cardNum:SmallInt ;profile:SmallInt;fifo:SmallInt;out pList:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PtDoBit(cardNum:SmallInt ;profile:SmallInt;doType:SmallInt;index:SmallInt;value:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PtAo(cardNum:SmallInt ;profile:SmallInt;aoType:SmallInt;index:SmallInt;value:Double;fifo:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_PrfGear(cardNum:SmallInt ;profile : SmallInt; dir:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_SetGearMaster(cardNum:SmallInt ;profile : SmallInt;masterIndex : SmallInt;masterType : SmallInt=GEAR_MASTER_PROFILE; masterItem:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetGearMaster(cardNum:SmallInt ;profile : SmallInt;out pMasterIndex : SmallInt; out pMasterType : SmallInt; out pMasterItem:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetGearRatio(cardNum:SmallInt ;profile : SmallInt;masterEven:LongInt;slaveEven:LongInt; masterSlope:LongInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetGearRatio(cardNum:SmallInt ;profile : SmallInt; out pMasterEven:LongInt;out pSlaveEven:LongInt; out pMasterSlope:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GearStart(cardNum:SmallInt ;mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetGearEvent(cardNum:SmallInt ;profile:SmallInt;event:SmallInt;startPara0:LongInt;startPara1:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetGearEvent(cardNum:SmallInt ;profile:SmallInt;out pEvent:SmallInt;out pStartPara0:LongInt;out pStartPara1:LongInt): SmallInt; stdcall; External GTDLL;

function GT_PrfFollow(cardNum:SmallInt ;profile : SmallInt; dir:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_SetFollowMaster(cardNum:SmallInt ;profile : SmallInt;masterIndex : SmallInt;masterType : SmallInt=FOLLOW_MASTER_PROFILE; masterItem:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetFollowMaster(cardNum:SmallInt ;profile : SmallInt;out pMasterIndex : SmallInt;out pMasterType : SmallInt; out pMasterItem:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetFollowLoop(cardNum:SmallInt ;profile : SmallInt;followLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_GetFollowLoop(cardNum:SmallInt ;profile : SmallInt; out pLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_SetFollowEvent(cardNum:SmallInt ;profile : SmallInt;followEvent : SmallInt;masterDir : SmallInt; pos:LongInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetFollowEvent(cardNum:SmallInt ;profile : SmallInt; out pEvent : SmallInt; out pMasterDir : SmallInt;  out pPos:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_FollowSpace(cardNum:SmallInt ;profile : SmallInt; out pSpace:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowData(cardNum:SmallInt ;profile : SmallInt;masterSegment:LongInt;slaveSegment:Double; mytype:SmallInt = FOLLOW_SEGMENT_NORMAL;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowClear(cardNum:SmallInt ;profile:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowStart(cardNum:SmallInt ;mask:LongInt;fifoOption:LongInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowSwitch(cardNum:SmallInt ;mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetFollowMemory(cardNum:SmallInt ;profile:SmallInt;memory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetFollowMemory(cardNum:SmallInt ;profile:SmallInt;out pMemory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetFollowStatus(cardNum:SmallInt ;profile:SmallInt;out pFifoNum:SmallInt;out pSwitchStatus:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetFollowPhasing(cardNum:SmallInt ;profile:SmallInt;profilePhasing:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetFollowPhasing(cardNum:SmallInt ;profile:SmallInt;out pProfilePhasing:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_Compile(cardNum:SmallInt ;pFileName:String;out pWrongInfo:TCompileInfo): SmallInt; stdcall; External GTDLL;
function GT_Download(cardNum:SmallInt ;pFileName:String): SmallInt; stdcall; External GTDLL;

function GT_GetFunId(cardNum:SmallInt ;pFunName : String;out funId : SmallInt): SmallInt; stdcall; External GTDLL;
function GT_Bind(cardNum:SmallInt ;thread : SmallInt;funId : SmallInt;page:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_RunThread(cardNum:SmallInt ;thread:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_StopThread(cardNum:SmallInt ;thread:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PauseThread(cardNum:SmallInt ;thread:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetThreadSts(cardNum:SmallInt ;thread : SmallInt; out pThreadSts:TThreadSts): SmallInt; stdcall; External GTDLL;

function GT_GetVarId(cardNum:SmallInt ;pFunName : String;pVarName:String;out pVarInfo : TVarInfo): SmallInt; stdcall; External GTDLL;
function GT_SetVarValue(cardNum:SmallInt ;page:SmallInt;var pVarInfo:TVarInfo;var pValue:Double;count:SmallInt=1):SmallInt;stdcall;External GTDLL;
function GT_GetVarValue(cardNum:SmallInt ;page:SmallInt;var pVarInfo:TVarInfo;out pValue:Double;count:SmallInt=1):SmallInt;stdcall;External GTDLL;

function GT_SetCrdMapBase(cardNum:SmallInt ;crd:SmallInt;base:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_GetCrdMapBase(cardNum:SmallInt ;crd:SmallInt;out pBase:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_SetCrdSmooth(cardNum:SmallInt ;crd:SmallInt;var pCrdSmooth:TCrdSmooth):SmallInt;stdcall;External GTDLL;
function GT_GetCrdSmooth(cardNum:SmallInt ;crd:SmallInt;out pCrdSmooth:TCrdSmooth):SmallInt;stdcall;External GTDLL;
function GT_SetCrdJerk(cardNum:SmallInt ;crd:SmallInt;jerkMax:Double):SmallInt;stdcall;External GTDLL;
function GT_GetCrdJerk(cardNum:SmallInt ;crd:SmallInt;out pJerkMax:Double):SmallInt;stdcall;External GTDLL;
function GT_SetCrdPrm(cardNum:SmallInt ;crd:SmallInt;var pCrdPrm:TCrdPrm):SmallInt;stdcall;External GTDLL;
function GT_GetCrdPrm(cardNum:SmallInt ;crd:SmallInt;out pCrdPrm:TCrdPrm):SmallInt;stdcall;External GTDLL;
function GT_SetArcAllowError(cardNum:SmallInt ;crd:SmallInt;error:Double):SmallInt;stdcall;External GTDLL;
function GT_CrdSpace(cardNum:SmallInt ;crd:SmallInt;out pSpace:LongInt; fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_CrdData(cardNum:SmallInt ;crd:SmallInt;var pCrdData:TCrdData; fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_CrdDataCircle(cardNum:SmallInt ;crd:SmallInt;var pCrdData:TCrdData ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXY(cardNum:SmallInt ;crd:SmallInt ;x:LongInt ;y:LongInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZ(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZA(cardNum:SmallInt ;crd:SmallInt ;x:LongInt; y:LongInt;z:LongInt;a:LongInt;synVel:Double ;synAcc:Double;velEnd:Double =0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;synVel:Double ;synAcc:Double ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0(cardNum:SmallInt ;crd:SmallInt ;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYR(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYC(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double ;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZR(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZC(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double ;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXR(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXC(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double ;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYZ(ccardNum:SmallInt ;rd:SmallInt;x:LongInt;y:LongInt;z:LongInt;interX:Double;interY:Double;interZ:Double;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0Override2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0Override2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0Override2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYROverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYCOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZROverride2(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZCOverride2(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXROverride2(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXCOverride2(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZ(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZ(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRX(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCX(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRY(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCY(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRXOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCXOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRYOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCYOverride2(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYRWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYCWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZRWN(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZCWN(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXRWN(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXCWN(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYZWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;interX:Double;interY:Double;interZ:Double;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0Override2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0Override2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0Override2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYROverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYCOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZROverride2WN(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZCOverride2WN(cardNum:SmallInt ;crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXROverride2WN(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXCOverride2WN(cardNum:SmallInt ;crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRXWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCXWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRYWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCYWN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRXOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCXOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRYOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCYOverride2WN(cardNum:SmallInt ;crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufTrend(cardNum:SmallInt ;crd:SmallInt;trendSegNum:LongInt ;trendDistance:Double ;trendVelEnd:Double ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_BufIO(cardNum:SmallInt ;crd:SmallInt;doType:Word ;doMask:Word ;doValue:Word ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_BufEnableDoBitPulse(cardNum:SmallInt ;crd:SmallInt;doType:SmallInt;doIndex:SmallInt;highLevelTime:Word;lowLevelTime:Word;pulseNum:LongInt;firstLevel:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufDisableDoBitPulse(cardNum:SmallInt ;crd:SmallInt;doType:SmallInt;doIndex:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufDelay(cardNum:SmallInt ;crd:SmallInt;delayTime:Word;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufComparePulse(cardNum:SmallInt ;crd:SmallInt;level:SmallInt;outputType:SmallInt;time:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufDA(cardNum:SmallInt ;crd:SmallInt;chn:SmallInt;daValue:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLmtsOn(cardNum:SmallInt ;crd:SmallInt;axis:SmallInt;limitType:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLmtsOff(cardNum:SmallInt ;crd:SmallInt;axis:SmallInt;limitType:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetStopIo(cardNum:SmallInt ;crd:SmallInt;axis:SmallInt;stopType:SmallInt;inputType:SmallInt;inputIndex:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufMove(cardNum:SmallInt ;crd:SmallInt;moveAxis:SmallInt;pos:LongInt;vel:Double;acc:Double;modal:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufGear(cardNum:SmallInt ;crd:SmallInt;gearAxis:SmallInt;pos:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufGearPercent(cardNum:SmallInt ;crd:SmallInt;gearAxis:SmallInt;pos:LongInt;accPercent:SmallInt;decPercent:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufStopMotion(cardNum:SmallInt ;crd:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetVarValue(cardNum:SmallInt ;crd:SmallInt;pageId:SmallInt;out pVarInfo:TVarInfo;value:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufJumpNextSeg(cardNum:SmallInt ;crd:SmallInt;axis:SmallInt;limitType:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSynchPrfPos(cardNum:SmallInt ;crd:SmallInt;encoder:SmallInt;profile:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufVirtualToActual(cardNum:SmallInt ;crd:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetLongVar(cardNum:SmallInt ;crd:SmallInt;index:SmallInt;value:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetDoubleVar(cardNum:SmallInt ;crd:SmallInt;index:SmallInt;value:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_CrdStart(cardNum:SmallInt ;mask:SmallInt;optionV:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_CrdStartStep(cardNum:SmallInt ;mask:SmallInt;option:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CrdStepMode(cardNum:SmallInt ;mask:SmallInt;option:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetOverride(cardNum:SmallInt ;crd:SmallInt;synVelRatio:Double):SmallInt;stdcall;External GTDLL;
function GT_SetOverride2(cardNum:SmallInt ;crd:SmallInt;synVelRatio:Double): SmallInt; stdcall; External GTDLL;
function GT_InitLookAhead(cardNum:SmallInt ;crd:SmallInt;fifo:SmallInt;T:Double;accMax:Double;n:SmallInt;var pLookAheadBuf:TCrdData):SmallInt;stdcall;External GTDLL;
function GT_GetLookAheadSpace(cardNum:SmallInt ;crd:SmallInt;out pSpace:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetLookAheadSegCount(cardNum:SmallInt ;crd:SmallInt;out pSegCount:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_CrdClear(cardNum:SmallInt ;crd:SmallInt;fifo:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_CrdStatus(cardNum:SmallInt ;crd:SmallInt;out pRun:SmallInt;out pSegment:LongInt; fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_SetUserSegNum(cardNum:SmallInt ;crd:SmallInt;segNum:LongInt;fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_GetUserSegNum(cardNum:SmallInt ;crd:SmallInt;out pSegNum:LongInt;fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_GetUserSegNumWN(cardNum:SmallInt ;crd:SmallInt;out pSegment:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetRemainderSegNum(cardNum:SmallInt ;crd:SmallInt;out pSegNum:LongInt;fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_SetCrdStopDec(cardNum:SmallInt ;crd:SmallInt;decSmoothStop:Double;decAbruptStop:Double):SmallInt;stdcall;External GTDLL;
function GT_GetCrdStopDec(cardNum:SmallInt ;crd:SmallInt;out pDecSmoothStop:Double;out pDecAbruptStop:Double):SmallInt;stdcall;External GTDLL;
function GT_SetCrdLmtStopMode(cardNum:SmallInt ;crd:SmallInt;lmtStopMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdLmtStopMode(cardNum:SmallInt ;crd:SmallInt;out pLmtStopMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetUserTargetVel(cardNum:SmallInt ;crd:SmallInt;out pTargetVel:Double): SmallInt; stdcall; External GTDLL;
function GT_GetSegTargetPos(cardNum:SmallInt ;crd:SmallInt;out pTargetPos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdPos(cardNum:SmallInt ;crd:SmallInt;out pPos:Double):SmallInt;stdcall;External GTDLL;
function GT_GetCrdVel(cardNum:SmallInt ;crd:SmallInt;out pSynVel:Double):SmallInt;stdcall;External GTDLL;
function GT_SetCrdSingleMaxVel(cardNum:SmallInt ;crd:SmallInt;out pMaxVell:Double): SmallInt; stdcall; External GTDLL;
function GT_GetCrdSingleMaxVel(cardNum:SmallInt ;crd:SmallInt;out pMaxVell:Double): SmallInt; stdcall; External GTDLL;
function GT_GetCmdCount(cardNum:SmallInt ;crd:SmallInt;out pResult:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_BufLaserOn(cardNum:SmallInt ;crd:SmallInt;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserOff(cardNum:SmallInt ;crd:SmallInt;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserPrfCmd(cardNum:SmallInt ;crd:SmallInt;laserPower:Double;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowRatio(cardNum:SmallInt ;crd:SmallInt;ratio:Double;minPower:Double;maxPower:Double;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowMode(cardNum:SmallInt ;crd:SmallInt;source:SmallInt =0;fifo:SmallInt=0;channel:SmallInt=0;startPower:Double =0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowOff(cardNum:SmallInt ;crd:SmallInt;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowSpline(cardNum:SmallInt ;crd:SmallInt;tableId:SmallInt;minPower:Double;maxPower:Double;fifo:SmallInt=0,channel:SmallInt=0): SmallInt; stdcall; External GTDLL;

function GT_PrfPvt(cardNum:SmallInt ;profile:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_SetPvtLoop(cardNum:SmallInt ;profile:SmallInt;loop:LongInt):SmallInt;stdcall;External GTDLL;
function GT_GetPvtLoop(cardNum:SmallInt ;profile:SmallInt;out pLoopCount:LongInt;out pLoop:LongInt):SmallInt;stdcall;External GTDLL;
function GT_PvtStatus(cardNum:SmallInt ;profile:SmallInt;out pTableId:SmallInt;out pTime:Double;count:SmallInt=1):SmallInt;stdcall;External GTDLL;
function GT_PvtStart(cardNum:SmallInt ;mask:LongInt):SmallInt;stdcall;External GTDLL;
function GT_PvtTableSelect(cardNum:SmallInt ;profile:SmallInt;tableId:SmallInt):SmallInt;stdcall;External GTDLL;

function GT_PvtTable(cardNum:SmallInt ;tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pVel:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableEx(cardNum:SmallInt ;tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pVelBegin:Double;var pVelEnd:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableComplete(cardNum:SmallInt ;tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pA:Double;var pB:Double;var pC:Double;velBegin:Double=0;velEnd:Double=0):SmallInt;stdcall;External GTDLL;
function GT_PvtTablePercent(cardNum:SmallInt ;tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pPercent:Double;velBegin:Double=0):SmallInt;stdcall;External GTDLL;
function GT_PvtPercentCalculate(cardNum:SmallInt ;n:LongInt;var pTime:Double;var pPos:Double;var pPercent:Double;velBegin:Double;var pVel:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableContinuous(cardNum:SmallInt ;tableId:SmallInt;count:LongInt;var pPos:Double;var pVel:Double;var pPercent:Double;var pVelMax:Double;var pAcc:Double;var pDec:Double;timeBegin:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtContinuousCalculate(cardNum:SmallInt ;n:LongInt;var pPos:Double;var pVel:Double;var pPercent:Double;var pVelMax:Double;var pAcc:Double;var pDec:Double;var pTime:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableMovePercent(cardNum:SmallInt ;tableId:SmallInt;distance:LongInt;vm:Double;acc:Double;pa1:Double;pa2:Double;dec:Double;pd1:Double;pd2:Double;var pVel:Double;var pAcc:Double;var pDec:Double;var pTime:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableMovePercentEx(cardNum:SmallInt ;tableId:SmallInt;distance:LongInt;vm:Double;acc:Double;pa1:Double;pa2:Double;ma:Double;dec:Double;pd1:Double;pd2:Double;md:Double;var pVel:Double;var pAcc:Double;var pDec:Double;var pTime:Double):SmallInt;stdcall;External GTDLL;

function GT_HomeInit(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_Home(cardNum:SmallInt ;axis:SmallInt;pos:LongInt;vel:Double;acc:Double;offset:LongInt): SmallInt; stdcall; External GTDLL;
function GT_Index(cardNum:SmallInt ;axis:SmallInt;pos:LongInt;offset:LongInt): SmallInt; stdcall; External GTDLL;
function GT_HomeStop(cardNum:SmallInt ;axis:SmallInt;pos:LongInt;vel:Double;acc:Double): SmallInt; stdcall; External GTDLL;
function GT_HomeSts(cardNum:SmallInt ;axis:SmallInt;out pStatus:Word): SmallInt; stdcall; External GTDLL;

function GT_HandwheelInit(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetHandwheelStopDec(cardNum:SmallInt ;slave:SmallInt;decSmoothStop:Double;decAbruptStop:Double): SmallInt; stdcall; External GTDLL;
function GT_StartHandwheel(cardNum:SmallInt ;slave:SmallInt;master:SmallInt;masterEven:SmallInt;slaveEven:SmallInt;intervalTime:SmallInt;acc:Double;dec:Double;vel:Double;stopWaitTime:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_EndHandwheel(cardNum:SmallInt ;slave:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetTrigger(cardNum:SmallInt ;i:SmallInt;out pTrigger:TTrigger): SmallInt; stdcall; External GTDLL;
function GT_GetTrigger(cardNum:SmallInt ;i:SmallInt;out pTrigger:TTrigger): SmallInt; stdcall; External GTDLL;
function GT_GetTriggerStatus(cardNum:SmallInt ;i:SmallInt;out pTriggerStatus:TTriggerStatus;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetTriggerStatusEx(cardNum:SmallInt ;i:SmallInt;out pTriggerStatusEx:TTriggerStatusEx;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_ClearTriggerStatus(cardNum:SmallInt ;i:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetComparePort(cardNum:SmallInt ;channel:SmallInt;hsio0:SmallInt;hsio1:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_ComparePulse(cardNum:SmallInt ;level:SmallInt;outputType:SmallInt;time:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CompareStop(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CompareStatus(cardNum:SmallInt ;out pStatus:SmallInt;out pCount:LongInt): SmallInt; stdcall; External GTDLL;
function GT_CompareData(cardNum:SmallInt ;encoder:SmallInt;source:SmallInt;pulseType:SmallInt;startLevel:SmallInt;time:SmallInt;var pBuf1:LongInt;count1:SmallInt;var pBuf2:LongInt;count2:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CompareLinear(cardNum:SmallInt ;encoder:SmallInt;channel:SmallInt;startPos:LongInt;repeatTimes:LongInt;interval:LongInt;time:SmallInt;source:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CompareContinuePulseMode(cardNum:SmallInt ;mode:SmallInt;count:SmallInt;standTime:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetEncResponseCheck(cardNum:SmallInt ;control:SmallInt;dacThreshold:SmallInt;minEncVel:Double;time:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetEncResponseCheck(cardNum:SmallInt ;control:SmallInt;out pDacThreshold:SmallInt;out pMinEncVel:Double;out pTime:LongInt): SmallInt; stdcall; External GTDLL;
function GT_EnableEncResponseCheck(cardNum:SmallInt ;control:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_DisableEncResponseCheck(cardNum:SmallInt ;control:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_2DCompareMode(cardNum:SmallInt ;chn:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DComparePulse(cardNum:SmallInt ;chn:SmallInt;level:SmallInt;outputType:SmallInt;time:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareStop(cardNum:SmallInt ;chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareClear(cardNum:SmallInt ;chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareStatus(cardNum:SmallInt ;chn:SmallInt;out pStatus:SmallInt;out pCount:LongInt;out pFifo:SmallInt;out pFifoCount:SmallInt;out pBufCount:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareSetPrm(cardNum:SmallInt ;chn:SmallInt;out pPrm:T2DComparePrm): SmallInt; stdcall; External GTDLL;
function GT_2DCompareData(cardNum:SmallInt ;chn:SmallInt;count:SmallInt;out pBuf:T2DCompareData;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareStart(cardNum:SmallInt ;chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareClearData(cardNum:SmallInt ;chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareSetPreOutTime(cardNum:SmallInt ;chn:SmallInt;preOutputTime:Double): SmallInt; stdcall; External GTDLL;

function GT_SetAxisMode(cardNum:SmallInt ;axis:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisMode(cardNum:SmallInt ;axis:SmallInt;out ppMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetHSIOOpt(cardNum:SmallInt ;value:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetHSIOOpt(cardNum:SmallInt ;out pValue:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LaserPowerMode(cardNum:SmallInt ;laserPowerMode:SmallInt;maxValue:Double;minValue:Double;channel:SmallInt=0;delaymode:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LaserPrfCmd(cardNum:SmallInt ;outputCmd:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LaserOutFrq(cardNum:SmallInt ;outFrq:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetPulseWidth(cardNum:SmallInt ;width:LongWord;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetWaitPulse(cardNum:SmallInt ;mode:Word;waitPulseFrq:Double;waitPulseDuty:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetPreVltg(cardNum:SmallInt ;mode:Word;voltageValue:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLevelDelay(cardNum:SmallInt ;offDelay:Word;onDelay:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_EnaFPK(cardNum:SmallInt ;time1:Word;time2:Word;laserOffDelay:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_DisFPK(cardNum:SmallInt ;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisMode(cardNum:SmallInt ;mode:SmallInt;source:SmallInt;out pPos:LongInt;out pScale:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisRatio(cardNum:SmallInt ;out pRatio:Double;minPower:Double;maxPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetWaitPulseEx(cardNum:SmallInt ;mode:Word;waitPulseFrq:Double;waitPulseDuty:Double): SmallInt; stdcall; External GTDLL;
function GT_SetLaserMode(cardNum:SmallInt ;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetLaserFollowSpline(cardNum:SmallInt ;tableId:SmallInt;n:LongInt;var pX:Double;var pY:Double;beginValue:Double;endValue:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetLaserFollowSpline(cardNum:SmallInt ;tableId:SmallInt;n:LongInt;out pX:Double;out pY:Double;out pA:Double;out pB:Double;out pC:Double;out pCount:LongInt;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;

//ExtMdl
function GT_OpenExtMdl(cardNum:SmallInt ;out pDllName:String): SmallInt; stdcall; External GTDLL;
function GT_CloseExtMdl(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SwitchtoCardNoExtMdl(cardNum:SmallInt ;card:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_ResetExtMdl(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_LoadExtConfig(cardNum:SmallInt ;var pFileName:String): SmallInt; stdcall; External GTDLL;
function GT_SetExtIoValue(cardNum:SmallInt ;mdl:SmallInt;value:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtIoValue(cardNum:SmallInt ;mdl:SmallInt;out pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_SetExtIoBit(cardNum:SmallInt ;mdl:SmallInt;index:SmallInt;value:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtIoBit(cardNum:SmallInt ;mdl:SmallInt;index:SmallInt;out pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtAdValue(cardNum:SmallInt ;mdl:SmallInt;chn:SmallInt;out pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtAdVoltage(cardNum:SmallInt ;mdl:SmallInt;chn:SmallInt;out pValue:Double): SmallInt; stdcall; External GTDLL;
function GT_SetExtDaValue(cardNum:SmallInt ;mdl:SmallInt;chn:SmallInt;value:Word): SmallInt; stdcall; External GTDLL;
function GT_SetExtDaVoltage(cardNum:SmallInt ;mdl:SmallInt;chn:SmallInt;value:Double): SmallInt; stdcall; External GTDLL;
function GT_GetStsExtMdl(cardNum:SmallInt ;mdl:SmallInt;chn:SmallInt;var pStatus:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtDoValue(cardNum:SmallInt ;mdl:SmallInt;var pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtMdlMode(cardNum:SmallInt ;var pMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetExtMdlMode(cardNum:SmallInt ;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_UploadConfig(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_DownloadConfig(cardNum:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetUuid(cardNum:SmallInt ;out pCode:String;count:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetUuid(cardNum:SmallInt ;var pCode:String;count:SmallInt): SmallInt; stdcall; External GTDLL;

//////////////////////////////////////////////////////////////////////////////////////
//2D Compensate

type TCompensate2DTable = record  
	count:array[0..1] of SmallInt;
    posBegin:array[0..1] of LongInt;                       
	step:array[0..1] of LongInt;                                                      
end;

type TCompensate2D = record   
    enable:SmallInt;                               
	tableIndex:SmallInt;                            
	axisType:array[0..1] of SmallInt;	                         
	axisIndex:array[0..1] of SmallInt;	                         
end;

function GT_SetCompensate2DTable(cardNum:SmallInt ;tableIndex : SmallInt;var pTable:TCompensate2DTable ;var pData:LongInt;externComp:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate2DTable(cardNum:SmallInt ;tableIndex : SmallInt;out pTable:TCompensate2DTable ;out pExternComp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetCompensate2D(cardNum:SmallInt ;axis : SmallInt;var pComp2d:TCompensate2D): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate2D(cardNum:SmallInt ;axis : SmallInt;out pComp2d:TCompensate2D): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate2DValue(cardNum:SmallInt ;axis : SmallInt;out pValue:Double): SmallInt; stdcall; External GTDLL;

//Smart Home
Const HOME_STAGE_IDLE = 0;
Const HOME_STAGE_START = 1;
Const HOME_STAGE_ON_HOME_LIMIT_ESCAPE = 2;
Const HOME_STAGE_SEARCH_LIMIT = 10;
Const HOME_STAGE_SEARCH_LIMIT_STOP = 11;
Const HOME_STAGE_SEARCH_LIMIT_ESCAPE = 13;
Const HOME_STAGE_SEARCH_LIMIT_RETURN = 15;
Const HOME_STAGE_SEARCH_LIMIT_RETURN_STOP = 16;
Const HOME_STAGE_SEARCH_HOME = 20;
Const HOME_STAGE_SEARCH_HOME_STOP = 22;
Const HOME_STAGE_SEARCH_HOME_RETURN = 25;
Const HOME_STAGE_SEARCH_INDEX = 30;
Const HOME_STAGE_SEARCH_GPI = 40;
Const HOME_STAGE_SEARCH_GPI_RETURN = 45;
Const HOME_STAGE_GO_HOME = 80;
Const HOME_STAGE_END = 100;
Const HOME_ERROR_NONE = 0;
Const HOME_ERROR_NOT_TRAP_MODE = 1;
Const HOME_ERROR_DISABLE = 2;
Const HOME_ERROR_ALARM = 3;
Const HOME_ERROR_STOP = 4;
Const HOME_ERROR_STAGE = 5;
Const HOME_ERROR_HOME_MODE = 6;
Const HOME_ERROR_SET_CAPTURE_HOME = 7;
Const HOME_ERROR_NO_HOME = 8;
Const HOME_ERROR_SET_CAPTURE_INDEX = 9;
Const HOME_ERROR_NO_INDEX = 10;
Const HOME_MODE_LIMIT = 10;
Const HOME_MODE_LIMIT_HOME = 11;
Const HOME_MODE_LIMIT_INDEX = 12;
Const HOME_MODE_LIMIT_HOME_INDEX = 13;
Const HOME_MODE_HOME = 20;
Const HOME_MODE_HOME_INDEX = 22;
Const HOME_MODE_INDEX = 30;
Const HOME_MODE_FORCED_HOME = 40;
Const HOME_MODE_FORCED_HOME_INDEX = 41;

type THomePrm = record
	mode:SmallInt;					
	moveDir:SmallInt;				
	indexDir:SmallInt;				
	edge:SmallInt;					
	triggerIndex:SmallInt;	
	pad1:array[0..2] of SmallInt;					
	velHigh:Double;				
	velLow:Double;				
	acc:Double;					
	dec:Double;	
	smoothTime:SmallInt;
	pad2:array[0..2] of SmallInt;				
	homeOffset:LongInt;				
	searchHomeDistance:LongInt;		
	searchIndexDistance:LongInt;		
	escapeStep:LongInt;	
	pad3:array[0..1] of LongInt;							
end;

type THomeStatus = record
	run:SmallInt;
	stage:SmallInt;
	error:SmallInt;
	pad1:SmallInt;
	capturePos:LongInt;
	targetPos:LongInt;
end;
function GT_GoHome(cardNum:SmallInt ;axis : SmallInt;var pHomePrm:THomePrm ): SmallInt; stdcall; External GTDLL;
function GT_GetHomePrm(cardNum:SmallInt ;axis : SmallInt;out pHomePrm:THomePrm): SmallInt; stdcall; External GTDLL;
function GT_GetHomeStatus(cardNum:SmallInt ;axis : SmallInt;out pHomeStatus:THomeStatus ): SmallInt; stdcall; External GTDLL;

//Extern Control
type TControlConfigEx = record
	refType:SmallInt;			
	refIndex:SmallInt;			
	feedbackType:SmallInt;		
	feedbackIndex:SmallInt;		
	errorLimit:LongInt;		
	feedbackSmooth:SmallInt;	
	controlSmooth:SmallInt;	
end;
function GT_SetControlConfigEx(cardNum:SmallInt ;control:SmallInt;var pControl:TControlConfigEx ): SmallInt; stdcall; External GTDLL;
function GT_GetControlConfigEx(cardNum:SmallInt ;control:SmallInt;out pControl:TControlConfigEx ): SmallInt; stdcall; External GTDLL;

//Adc filter
type TAdcConfig = record
	active:SmallInt;	
	reverse:SmallInt;	
	a:Double;			
	b:Double;				
	filterMode:SmallInt;	
end;

function GT_SetAdcConfig(cardNum:SmallInt ;adc:SmallInt;var pAdc:TAdcConfig): SmallInt; stdcall; External GTDLL;
function GT_GetAdcConfig(cardNum:SmallInt ;adc:SmallInt;out pAdc:TAdcConfig): SmallInt; stdcall; External GTDLL;
function GT_SetAdcFilterPrm(cardNum:SmallInt ;adc:SmallInt;k:Double): SmallInt; stdcall; External GTDLL;
function GT_GetAdcFilterPrm(cardNum:SmallInt ;adc:SmallInt;out pk:double): SmallInt; stdcall; External GTDLL;

//Superimposed
function GT_SetControlSuperimposed(cardNum:SmallInt ;control:SmallInt;superimposedType:SmallInt;superimposedIndex:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetControlSuperimposed(cardNum:SmallInt ;control:SmallInt;out pSuperimposedType:SmallInt;out pSuperimposedIndex:SmallInt): SmallInt; stdcall; External GTDLL;

//
function GT_ZeroLaserOnTime(cardNum:SmallInt ;channel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetLaserOnTime(cardNum:SmallInt ;channel:SmallInt;out pTime:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetProfileScale(cardNum:SmallInt ;axis:SmallInt;alpha:LongInt;beta:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetProfileScale(cardNum:SmallInt ;axis:SmallInt;out pAlpha:LongInt;out pBeta:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetEncoderScale(cardNum:SmallInt ;axis:SmallInt;alpha:LongInt;beta:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetEncoderScale(cardNum:SmallInt ;axis:SmallInt;out pAlpha:LongInt;out pBeta:LongInt): SmallInt; stdcall; External GTDLL;

function GT_MultiAxisOn(cardNum:SmallInt ;mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_MultiAxisOff(cardNum:SmallInt ;mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisOnDelayTime(cardNum:SmallInt ;ms:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisOnDelayTime(cardNum:SmallInt ;out pMs:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetLaserDisTable1D(cardNum:SmallInt ;count:SmallInt;var pRatio:Double;var pPos:LongInt;minPower:Double;maxPower:Double;var pLimitPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisTable2D(cardNum:SmallInt ;var axisIndex:SmallInt;var count:SmarllInt;var pRatio:Double;var pXPos:Double;var pYPos:Double;
																minPower:Double;maxPower:Double;var pLimitPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisTable2DEx(cardNum:SmallInt ;var axisIndex:SmallInt;var count:SmallInt;pRatio:Double;var posBegin:LongInt;var posStep:LongInt;
																	minPower:Double;maxPower:Double;var pLimitPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserCrdMap(cardNum:SmallInt ;channel:SmallInt;map:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetLaserCrdMap(cardNum:SmallInt ;channel:SmallInt;out pMap:SmallInt): SmallInt; stdcall; External GTDLL;

//AutoFocus
function GT_AutoFocus(cardNum:SmallInt ;mode:Word;kp:Double;reverse:SmallInt;chanel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAutoFocusRefVol(cardNum:SmallInt ;refVol:Double;maxVol:Double;minVol:Double;chanel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAutoFocusStatus(cardNum:SmallInt ;out pStatus:Word;count:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_ConfigAutoFocus(cardNum:SmallInt ;chnAdc:SmallInt;chanel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAutoFocusAuxPrm(cardNum:SmallInt ;kf:Double;kd:Double;limitKd:Double;chanel:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_Delay(cardNum:SmallInt ;time:Word): SmallInt; stdcall; External GTDLL;
function GT_DelayHighPrecision(cardNum:SmallInt ;time:Word): SmallInt; stdcall; External GTDLL;

function GT_SetCrdBufferMode(cardNum:SmallInt ;crd:SmallInt;bufferMode:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdBufferMode(cardNum:SmallInt ;crd:SmallInt;out pBufferMode:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdSegmentTime(cardNum:SmallInt ;crd:SmallInt;segmentIndex:LongInt;out pSegmentTime:Double;out pSegmentNumber:LongInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdTime(cardNum:SmallInt ;crd:SmallInt;out pTime:TCrdTime;fifo:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetLeadScrewLink(cardNum:SmallInt ;axis:SmallInt;link:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetLeadScrewLink(cardNum:SmallInt ;axis:SmallInt;out pLink:SmallInt): SmallInt; stdcall; External GTDLL;

implementation

end.
