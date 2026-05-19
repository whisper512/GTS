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

function GT_GetDllVersion(out pDllVersion:String):SmallInt; stdcall; External GTDLL;
function GT_SetCardNo(index:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCardNo(out pIndex:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetVersion(out pVersion:String): SmallInt; stdcall; External GTDLL;
function GT_GetInterfaceBoardSts(out pStatus:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetInterfaceBoardSts(interfaceType:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_Open(channel:SmallInt=0;param:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_Close: SmallInt; stdcall; External GTDLL;

function GT_LoadConfig(pFile:String): SmallInt; stdcall; External GTDLL;

function GT_AlarmOff(axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_AlarmOn(axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_LmtsOn(axis:SmallInt;limitType:SmallInt =-1): SmallInt; stdcall; External GTDLL;
function GT_LmtsOff(axis:SmallInt;limitType:SmallInt=-1): SmallInt; stdcall; External GTDLL;
function GT_ProfileScale(axis:SmallInt ;alpha:SmallInt ;beta:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_EncScale(axis:SmallInt ;alpha:SmallInt ;beta:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_StepDir(step:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_StepPulse(step:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_SetMtrBias(dac:SmallInt ;bias:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_GetMtrBias(dac:SmallInt ;out pBias:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_SetMtrLmt(dac:SmallInt ;limit:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_GetMtrLmt(dac:SmallInt ;out pLimit:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_EncSns(sense:Word ): SmallInt; stdcall; External GTDLL;
function GT_EncOn(encoder:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_EncOff(encoder:SmallInt ): SmallInt; stdcall; External GTDLL;
function GT_SetPosErr(control:SmallInt ;error:LongInt ): SmallInt; stdcall; External GTDLL;
function GT_GetPosErr(control:SmallInt ;out pError:LongInt ): SmallInt; stdcall; External GTDLL;
function GT_SetStopDec(profile:SmallInt ;decSmoothStop:Double ;decAbruptStop:Double ): SmallInt; stdcall; External GTDLL;
function GT_GetStopDec(profile:SmallInt ; out pDecSmoothStop:Double;out pDecAbruptStop:Double ): SmallInt; stdcall; External GTDLL;
function GT_LmtSns(sense:Word): SmallInt; stdcall; External GTDLL;
function GT_CtrlMode(axis:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetStopIo(axis:SmallInt;stopType:SmallInt;inputType:SmallInt;inputIndex:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GpiSns(sense:Word): SmallInt; stdcall; External GTDLL;
function GT_SetAdcFilter(adc:SmallInt;filterTime:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisPrfVelFilter(axis:SmallInt;filterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisPrfVelFilter(axis:SmallInt;out pFilterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisEncVelFilter(axis:SmallInt;filterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncVelFilter(axis:SmallInt;out pFilterNumExp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisInputShaping(axis:SmallInt;enable:SmallInt;count:SmallInt;k:Double): SmallInt; stdcall; External GTDLL;

function GT_SetDo(doType:SmallInt;value:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoBit(doType:SmallInt;doIndex:SmallInt;value:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetDo(doType : SmallInt; out pValue:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoBitReverse(doType : SmallInt; doIndex:SmallInt;value:SmallInt;reverseTime:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoMask(doType:SmallInt;doMask:Word;value:LongInt): SmallInt; stdcall; External GTDLL;
function GT_EnableDoBitPulse(doType:SmallInt;doIndex:SmallInt;highLevelTime:Word;lowLevelTime:Word;pulseNum:LongInt;firstLevel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_DisableDoBitPulse(doType:SmallInt;doIndex:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetDi(diType : SmallInt; out pValue:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetDiReverseCount(diType : SmallInt; diIndex : SmallInt; out pReverseCount : LongWord; count : SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_SetDiReverseCount(diType : SmallInt; diIndex : SmallInt; var pReverseCount : LongWord; count : SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetDiRaw(diType : SmallInt; out pValue:LongInt): SmallInt; stdcall; External GTDLL;

function GT_SetDac(dac : SmallInt;var pValue:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetDac(dac : SmallInt;out pValue:SmallInt;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_GetAdc(adc : SmallInt;out pValue:Double;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAdcValue(adc : SmallInt;out pValue:SmallInt;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetEncPos(encoder : SmallInt;encPos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetEncPos(encoder : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetEncPosPre(encoder:SmallInt;out pValue:Double;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetEncVel(encoder : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetCaptureMode(encoder : SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureMode(encoder : SmallInt; out pMode : SmallInt; count:SmallInt=1	): SmallInt; stdcall; External GTDLL;
function GT_StopCapture(encoder : SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureStatus(encoder : SmallInt; out pStatus : SmallInt; out pValue:LongInt;count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_SetCaptureSense(encoder : SmallInt;mode:SmallInt;sense:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_ClearCaptureStatus(encoder : SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetCaptureRepeat(encoder:SmallInt;count:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureRepeatStatus(encoder:SmallInt;out pCount:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureRepeatPos(encoder:SmallInt;out pValue:LongInt;startNum:SmallInt;count:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetCaptureEncoder(trigger:SmallInt;encoder:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureWidth(trigger:SmallInt;out pWidth:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetCaptureHomeGpi(trigger:SmallInt;out pHomeSts:SmallInt;out pHomePos:SmallInt;out pGpiSts:SmallInt;out pGpiPos:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;

function GT_Reset: SmallInt; stdcall; External GTDLL;
function GT_GetClock(Out pClock:LongWord;out pLoop:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetClockHighPrecision(Out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_GetSts(axis : SmallInt; out pSts:LongInt; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_ClrSts(axis:SmallInt;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_AxisOn(axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_AxisOff(axis:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_Stop(mask:LongInt;stopOption:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetPrfPos(profile : SmallInt;prfPos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SynchAxisPos(mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_ZeroPos(axis : SmallInt;count : SmallInt=1): SmallInt; stdcall; External GTDLL;

function GT_SetSoftLimit(axis : SmallInt;positive:LongInt;negative:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetSoftLimit(axis : SmallInt;out pPositive:LongInt;out pNegative:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisBand(axis : SmallInt;band:LongInt;time:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisBand(axis : SmallInt; out pBand:LongInt;out pTime:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetBacklash(axis : SmallInt;compValue:LongInt;compChangeValue:Double;compDir:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetBacklash(axis : SmallInt; out pCompValue:LongInt;out pCompChangeValue:Double;out pCompDir:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetLeadScrewComp(axis:SmallInt;n:SmallInt;startPos:LongInt;lenPos:LongInt;out pCompPos:LongInt;out pCompNeg:LongInt): SmallInt; stdcall; External GTDLL;
function GT_EnableLeadScrewComp(axis:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate(axis:SmallInt;out pPitchError:Double;out pCrossError:Double;out pBacklashError:Double;out pEncPos:Double;out pPrfPos:Double): SmallInt; stdcall; External GTDLL;

function GT_EnableGantry(gantryMaster:SmallInt;gantrySlave:SmallInt;masterKp:Double;slaveKp:Double): SmallInt; stdcall; External GTDLL;
function GT_DisableGantry(): SmallInt; stdcall; External GTDLL;
function GT_SetGantryErrLmt(gantryErrLmt:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetGantryErrLmt(out pGantryErrLmt:LongInt): SmallInt; stdcall; External GTDLL;
function GT_ZeroGantryPos(gantryMaster:SmallInt;gantrySlave:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetPrfPos(profile : SmallInt; out pValue:Double; count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetPrfVel(profile : SmallInt; out pValue:Double; count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetPrfAcc(profile : SmallInt; out pValue:Double; count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetPrfMode(profile : SmallInt; out pValue:LongInt;count:SmallInt; out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_GetAxisPrfPos(axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisPrfVel(axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisPrfAcc(axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncPos(axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncVel(axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisEncAcc(axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;
function GT_GetAxisError(axis : SmallInt; out pValue:Double; count:SmallInt;out pClock:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetLongVar(index:SmallInt;value:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetLongVar(index:SmallInt;out pValue:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetDoubleVar(index:SmallInt;pValue:Double): SmallInt; stdcall; External GTDLL;
function GT_GetDoubleVar(index:SmallInt;out pValue:Double): SmallInt; stdcall; External GTDLL;

function GT_SetControlFilter(control : SmallInt;index:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetControlFilter(control : SmallInt;out pIndex:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetPid(control : SmallInt;index : SmallInt; var pPid:TPid): SmallInt; stdcall; External GTDLL;
function GT_GetPid(control : SmallInt;index : SmallInt; out pPid:TPid): SmallInt; stdcall; External GTDLL;

function GT_SetKvffFilter(control:SmallInt;index:SmallInt;kvffFilterExp:SmallInt;accMax:Double): SmallInt; stdcall; External GTDLL;
function GT_GetKvffFilter(control:SmallInt;index:SmallInt;out pKvffFilterExp:SmallInt;out pAccMax:Double): SmallInt; stdcall; External GTDLL;

function GT_Update(mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetPos(profile : SmallInt;pos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetPos(profile : SmallInt; out pPos:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_SetVel(profile : SmallInt;vel:Double): SmallInt; stdcall; External GTDLL;
function GT_GetVel(profile : SmallInt; out pVel:Double): SmallInt; stdcall; External GTDLL;

function GT_PrfTrap(profile:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetTrapPrm(profile : SmallInt; var pPrm:TTrapPrm): SmallInt; stdcall; External GTDLL;
function GT_GetTrapPrm(profile : SmallInt; out pPrm:TTrapPrm): SmallInt; stdcall; External GTDLL;

function GT_PrfJog(profile:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetJogPrm(profile : SmallInt; var pPrm:TJogPrm): SmallInt; stdcall; External GTDLL;
function GT_GetJogPrm(profile : SmallInt; out pPrm:TJogPrm): SmallInt; stdcall; External GTDLL;

function GT_PrfPt(profile : SmallInt; mode:SmallInt = PT_MODE_STATIC): SmallInt; stdcall; External GTDLL;
function GT_SetPtLoop(profile : SmallInt;ptLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_GetPtLoop(profile : SmallInt; out pLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_PtSpace(profile : SmallInt; out pSpace:SmallInt; fifo:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_PtData(profile : SmallInt;pos:Double;time:LongInt; mytype:SmallInt = PT_SEGMENT_NORMAL;fifo:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_PtDataWN(profile:SmallInt;pos:Double;time:LongInt;ptDataType:SmallInt=PT_SEGMENT_NORMAL;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_PtClear(profile : SmallInt; fifo:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_PtStart(mask:LongInt;fifoOption:LongInt = 0): SmallInt; stdcall; External GTDLL;
function GT_SetPtMemory(profile : SmallInt; memory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetPtMemory(profile : SmallInt; out pMemory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PtGetSegNum(profile:SmallInt;out pSegNum:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetPtPrecisionMode(profile:SmallInt;precisionMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetPtPrecisionMode(profile:SmallInt;out pPrecisionMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetPtVel(profile:SmallInt;velLast:Double;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetPtLink(profile:SmallInt;fifo:SmallInt;list:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetPtLink(profile:SmallInt;fifo:SmallInt;out pList:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PtDoBit(profile:SmallInt;doType:SmallInt;index:SmallInt;value:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PtAo(profile:SmallInt;aoType:SmallInt;index:SmallInt;value:Double;fifo:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_PrfGear(profile : SmallInt; dir:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_SetGearMaster(profile : SmallInt;masterIndex : SmallInt;masterType : SmallInt=GEAR_MASTER_PROFILE; masterItem:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetGearMaster(profile : SmallInt;out pMasterIndex : SmallInt; out pMasterType : SmallInt; out pMasterItem:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetGearRatio(profile : SmallInt;masterEven:LongInt;slaveEven:LongInt; masterSlope:LongInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetGearRatio(profile : SmallInt; out pMasterEven:LongInt;out pSlaveEven:LongInt; out pMasterSlope:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GearStart(mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetGearEvent(profile:SmallInt;event:SmallInt;startPara0:LongInt;startPara1:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetGearEvent(profile:SmallInt;out pEvent:SmallInt;out pStartPara0:LongInt;out pStartPara1:LongInt): SmallInt; stdcall; External GTDLL;

function GT_PrfFollow(profile : SmallInt; dir:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_SetFollowMaster(profile : SmallInt;masterIndex : SmallInt;masterType : SmallInt=FOLLOW_MASTER_PROFILE; masterItem:SmallInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetFollowMaster(profile : SmallInt;out pMasterIndex : SmallInt;out pMasterType : SmallInt; out pMasterItem:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetFollowLoop(profile : SmallInt;followLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_GetFollowLoop(profile : SmallInt; out pLoop:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_SetFollowEvent(profile : SmallInt;followEvent : SmallInt;masterDir : SmallInt; pos:LongInt = 0): SmallInt; stdcall; External GTDLL;
function GT_GetFollowEvent(profile : SmallInt; out pEvent : SmallInt; out pMasterDir : SmallInt;  out pPos:LongInt	): SmallInt; stdcall; External GTDLL;
function GT_FollowSpace(profile : SmallInt; out pSpace:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowData(profile : SmallInt;masterSegment:LongInt;slaveSegment:Double; mytype:SmallInt = FOLLOW_SEGMENT_NORMAL;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowClear(profile:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowStart(mask:LongInt;fifoOption:LongInt=0): SmallInt; stdcall; External GTDLL;
function GT_FollowSwitch(mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetFollowMemory(profile:SmallInt;memory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetFollowMemory(profile:SmallInt;out pMemory:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetFollowStatus(profile:SmallInt;out pFifoNum:SmallInt;out pSwitchStatus:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetFollowPhasing(profile:SmallInt;profilePhasing:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetFollowPhasing(profile:SmallInt;out pProfilePhasing:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_Compile(pFileName:String;out pWrongInfo:TCompileInfo): SmallInt; stdcall; External GTDLL;
function GT_Download(pFileName:String): SmallInt; stdcall; External GTDLL;

function GT_GetFunId(pFunName : String;out funId : SmallInt): SmallInt; stdcall; External GTDLL;
function GT_Bind(thread : SmallInt;funId : SmallInt;page:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_RunThread(thread:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_StopThread(thread:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_PauseThread(thread:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_GetThreadSts(thread : SmallInt; out pThreadSts:TThreadSts): SmallInt; stdcall; External GTDLL;

function GT_GetVarId(pFunName : String;pVarName:String;out pVarInfo : TVarInfo): SmallInt; stdcall; External GTDLL;
function GT_SetVarValue(page:SmallInt;var pVarInfo:TVarInfo;var pValue:Double;count:SmallInt=1):SmallInt;stdcall;External GTDLL;
function GT_GetVarValue(page:SmallInt;var pVarInfo:TVarInfo;out pValue:Double;count:SmallInt=1):SmallInt;stdcall;External GTDLL;

function GT_SetCrdMapBase(crd:SmallInt;base:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_GetCrdMapBase(crd:SmallInt;out pBase:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_SetCrdSmooth(crd:SmallInt;var pCrdSmooth:TCrdSmooth):SmallInt;stdcall;External GTDLL;
function GT_GetCrdSmooth(crd:SmallInt;out pCrdSmooth:TCrdSmooth):SmallInt;stdcall;External GTDLL;
function GT_SetCrdJerk(crd:SmallInt;jerkMax:Double):SmallInt;stdcall;External GTDLL;
function GT_GetCrdJerk(crd:SmallInt;out pJerkMax:Double):SmallInt;stdcall;External GTDLL;
function GT_SetCrdPrm(crd:SmallInt;var pCrdPrm:TCrdPrm):SmallInt;stdcall;External GTDLL;
function GT_GetCrdPrm(crd:SmallInt;out pCrdPrm:TCrdPrm):SmallInt;stdcall;External GTDLL;
function GT_SetArcAllowError(crd:SmallInt;error:Double):SmallInt;stdcall;External GTDLL;
function GT_CrdSpace(crd:SmallInt;out pSpace:LongInt; fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_CrdData(crd:SmallInt;var pCrdData:TCrdData; fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_CrdDataCircle(crd:SmallInt;var pCrdData:TCrdData ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXY(crd:SmallInt ;x:LongInt ;y:LongInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZ(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZA(crd:SmallInt ;x:LongInt; y:LongInt;z:LongInt;a:LongInt;synVel:Double ;synAcc:Double;velEnd:Double =0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0(crd:SmallInt;x:LongInt;y:LongInt;synVel:Double ;synAcc:Double ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0(crd:SmallInt ;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYR(crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYC(crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double ;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZR(crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZC(crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double ;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXR(crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXC(crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double ;circleDir:SmallInt ;synVel:Double ;synAcc:Double ;velEnd:Double =0;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYZ(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;interX:Double;interY:Double;interZ:Double;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYOverride2(crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0Override2(crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0Override2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0Override2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYROverride2(crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYCOverride2(crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZROverride2(crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZCOverride2(crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXROverride2(crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXCOverride2(crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZ(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZ(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRX(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCX(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRY(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCY(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRXOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCXOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRYOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCYOverride2(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYWN(crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0WN(crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYRWN(crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYCWN(crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZRWN(crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZCWN(crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXRWN(crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXCWN(crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYZWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;interX:Double;interY:Double;interZ:Double;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYG0Override2WN(crd:SmallInt;x:LongInt;y:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZG0Override2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LnXYZAG0Override2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;a:LongInt;synVel:Double;synAcc:Double;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYROverride2WN(crd:SmallInt;x:LongInt;y:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcXYCOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZROverride2WN(crd:SmallInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcYZCOverride2WN(crd:SmallInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXROverride2WN(crd:SmallInt;z:LongInt;x:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_ArcZXCOverride2WN(crd:SmallInt;z:LongInt;x:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRXWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCXWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRYWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCYWN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYRZOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixXYCZOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;xCenter:Double;yCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZRXOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixYZCXOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;yCenter:Double;zCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXRYOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;radius:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_HelixZXCYOverride2WN(crd:SmallInt;x:LongInt;y:LongInt;z:LongInt;zCenter:Double;xCenter:Double;circleDir:SmallInt;synVel:Double;synAcc:Double;velEnd:Double=0;segNum:LongInt=0;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufTrend(crd:SmallInt;trendSegNum:LongInt ;trendDistance:Double ;trendVelEnd:Double ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_BufIO(crd:SmallInt;doType:Word ;doMask:Word ;doValue:Word ;fifo:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_BufEnableDoBitPulse(crd:SmallInt;doType:SmallInt;doIndex:SmallInt;highLevelTime:Word;lowLevelTime:Word;pulseNum:LongInt;firstLevel:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufDisableDoBitPulse(crd:SmallInt;doType:SmallInt;doIndex:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufDelay(crd:SmallInt;delayTime:Word;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufComparePulse(crd:SmallInt;level:SmallInt;outputType:SmallInt;time:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufDA(crd:SmallInt;chn:SmallInt;daValue:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLmtsOn(crd:SmallInt;axis:SmallInt;limitType:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLmtsOff(crd:SmallInt;axis:SmallInt;limitType:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetStopIo(crd:SmallInt;axis:SmallInt;stopType:SmallInt;inputType:SmallInt;inputIndex:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufMove(crd:SmallInt;moveAxis:SmallInt;pos:LongInt;vel:Double;acc:Double;modal:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufGear(crd:SmallInt;gearAxis:SmallInt;pos:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufGearPercent(crd:SmallInt;gearAxis:SmallInt;pos:LongInt;accPercent:SmallInt;decPercent:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufStopMotion(crd:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetVarValue(crd:SmallInt;pageId:SmallInt;out pVarInfo:TVarInfo;value:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufJumpNextSeg(crd:SmallInt;axis:SmallInt;limitType:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSynchPrfPos(crd:SmallInt;encoder:SmallInt;profile:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufVirtualToActual(crd:SmallInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetLongVar(crd:SmallInt;index:SmallInt;value:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufSetDoubleVar(crd:SmallInt;index:SmallInt;value:Double;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_CrdStart(mask:SmallInt;optionV:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_CrdStartStep(mask:SmallInt;option:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CrdStepMode(mask:SmallInt;option:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetOverride(crd:SmallInt;synVelRatio:Double):SmallInt;stdcall;External GTDLL;
function GT_SetOverride2(crd:SmallInt;synVelRatio:Double): SmallInt; stdcall; External GTDLL;
function GT_InitLookAhead(crd:SmallInt;fifo:SmallInt;T:Double;accMax:Double;n:SmallInt;var pLookAheadBuf:TCrdData):SmallInt;stdcall;External GTDLL;
function GT_GetLookAheadSpace(crd:SmallInt;out pSpace:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetLookAheadSegCount(crd:SmallInt;out pSegCount:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_CrdClear(crd:SmallInt;fifo:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_CrdStatus(crd:SmallInt;out pRun:SmallInt;out pSegment:LongInt; fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_SetUserSegNum(crd:SmallInt;segNum:LongInt;fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_GetUserSegNum(crd:SmallInt;out pSegNum:LongInt;fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_GetUserSegNumWN(crd:SmallInt;out pSegment:LongInt;fifo:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetRemainderSegNum(crd:SmallInt;out pSegNum:LongInt;fifo:SmallInt = 0):SmallInt;stdcall;External GTDLL;
function GT_SetCrdStopDec(crd:SmallInt;decSmoothStop:Double;decAbruptStop:Double):SmallInt;stdcall;External GTDLL;
function GT_GetCrdStopDec(crd:SmallInt;out pDecSmoothStop:Double;out pDecAbruptStop:Double):SmallInt;stdcall;External GTDLL;
function GT_SetCrdLmtStopMode(crd:SmallInt;lmtStopMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdLmtStopMode(crd:SmallInt;out pLmtStopMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetUserTargetVel(crd:SmallInt;out pTargetVel:Double): SmallInt; stdcall; External GTDLL;
function GT_GetSegTargetPos(crd:SmallInt;out pTargetPos:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdPos(crd:SmallInt;out pPos:Double):SmallInt;stdcall;External GTDLL;
function GT_GetCrdVel(crd:SmallInt;out pSynVel:Double):SmallInt;stdcall;External GTDLL;
function GT_SetCrdSingleMaxVel(crd:SmallInt;out pMaxVell:Double): SmallInt; stdcall; External GTDLL;
function GT_GetCrdSingleMaxVel(crd:SmallInt;out pMaxVell:Double): SmallInt; stdcall; External GTDLL;
function GT_GetCmdCount(crd:SmallInt;out pResult:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_BufLaserOn(crd:SmallInt;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserOff(crd:SmallInt;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserPrfCmd(crd:SmallInt;laserPower:Double;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowRatio(crd:SmallInt;ratio:Double;minPower:Double;maxPower:Double;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowMode(crd:SmallInt;source:SmallInt =0;fifo:SmallInt=0;channel:SmallInt=0;startPower:Double =0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowOff(crd:SmallInt;fifo:SmallInt=0;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_BufLaserFollowSpline(crd:SmallInt;tableId:SmallInt;minPower:Double;maxPower:Double;fifo:SmallInt=0,channel:SmallInt=0): SmallInt; stdcall; External GTDLL;

function GT_PrfPvt(profile:SmallInt):SmallInt;stdcall;External GTDLL;
function GT_SetPvtLoop(profile:SmallInt;loop:LongInt):SmallInt;stdcall;External GTDLL;
function GT_GetPvtLoop(profile:SmallInt;out pLoopCount:LongInt;out pLoop:LongInt):SmallInt;stdcall;External GTDLL;
function GT_PvtStatus(profile:SmallInt;out pTableId:SmallInt;out pTime:Double;count:SmallInt=1):SmallInt;stdcall;External GTDLL;
function GT_PvtStart(mask:LongInt):SmallInt;stdcall;External GTDLL;
function GT_PvtTableSelect(profile:SmallInt;tableId:SmallInt):SmallInt;stdcall;External GTDLL;

function GT_PvtTable(tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pVel:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableEx(tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pVelBegin:Double;var pVelEnd:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableComplete(tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pA:Double;var pB:Double;var pC:Double;velBegin:Double=0;velEnd:Double=0):SmallInt;stdcall;External GTDLL;
function GT_PvtTablePercent(tableId:SmallInt;count:LongInt;var pTime:Double;var pPos:Double;var pPercent:Double;velBegin:Double=0):SmallInt;stdcall;External GTDLL;
function GT_PvtPercentCalculate(n:LongInt;var pTime:Double;var pPos:Double;var pPercent:Double;velBegin:Double;var pVel:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableContinuous(tableId:SmallInt;count:LongInt;var pPos:Double;var pVel:Double;var pPercent:Double;var pVelMax:Double;var pAcc:Double;var pDec:Double;timeBegin:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtContinuousCalculate(n:LongInt;var pPos:Double;var pVel:Double;var pPercent:Double;var pVelMax:Double;var pAcc:Double;var pDec:Double;var pTime:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableMovePercent(tableId:SmallInt;distance:LongInt;vm:Double;acc:Double;pa1:Double;pa2:Double;dec:Double;pd1:Double;pd2:Double;var pVel:Double;var pAcc:Double;var pDec:Double;var pTime:Double):SmallInt;stdcall;External GTDLL;
function GT_PvtTableMovePercentEx(tableId:SmallInt;distance:LongInt;vm:Double;acc:Double;pa1:Double;pa2:Double;ma:Double;dec:Double;pd1:Double;pd2:Double;md:Double;var pVel:Double;var pAcc:Double;var pDec:Double;var pTime:Double):SmallInt;stdcall;External GTDLL;

function GT_HomeInit: SmallInt; stdcall; External GTDLL;
function GT_Home(axis:SmallInt;pos:LongInt;vel:Double;acc:Double;offset:LongInt): SmallInt; stdcall; External GTDLL;
function GT_Index(axis:SmallInt;pos:LongInt;offset:LongInt): SmallInt; stdcall; External GTDLL;
function GT_HomeStop(axis:SmallInt;pos:LongInt;vel:Double;acc:Double): SmallInt; stdcall; External GTDLL;
function GT_HomeSts(axis:SmallInt;out pStatus:Word): SmallInt; stdcall; External GTDLL;

function GT_HandwheelInit(): SmallInt; stdcall; External GTDLL;
function GT_SetHandwheelStopDec(slave:SmallInt;decSmoothStop:Double;decAbruptStop:Double): SmallInt; stdcall; External GTDLL;
function GT_StartHandwheel(slave:SmallInt;master:SmallInt;masterEven:SmallInt;slaveEven:SmallInt;intervalTime:SmallInt;acc:Double;dec:Double;vel:Double;stopWaitTime:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_EndHandwheel(slave:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetTrigger(i:SmallInt;out pTrigger:TTrigger): SmallInt; stdcall; External GTDLL;
function GT_GetTrigger(i:SmallInt;out pTrigger:TTrigger): SmallInt; stdcall; External GTDLL;
function GT_GetTriggerStatus(i:SmallInt;out pTriggerStatus:TTriggerStatus;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_GetTriggerStatusEx(i:SmallInt;out pTriggerStatusEx:TTriggerStatusEx;count:SmallInt=1): SmallInt; stdcall; External GTDLL;
function GT_ClearTriggerStatus(i:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetComparePort(channel:SmallInt;hsio0:SmallInt;hsio1:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_ComparePulse(level:SmallInt;outputType:SmallInt;time:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CompareStop: SmallInt; stdcall; External GTDLL;
function GT_CompareStatus(out pStatus:SmallInt;out pCount:LongInt): SmallInt; stdcall; External GTDLL;
function GT_CompareData(encoder:SmallInt;source:SmallInt;pulseType:SmallInt;startLevel:SmallInt;time:SmallInt;var pBuf1:LongInt;count1:SmallInt;var pBuf2:LongInt;count2:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CompareLinear(encoder:SmallInt;channel:SmallInt;startPos:LongInt;repeatTimes:LongInt;interval:LongInt;time:SmallInt;source:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_CompareContinuePulseMode(mode:SmallInt;count:SmallInt;standTime:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetEncResponseCheck(control:SmallInt;dacThreshold:SmallInt;minEncVel:Double;time:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetEncResponseCheck(control:SmallInt;out pDacThreshold:SmallInt;out pMinEncVel:Double;out pTime:LongInt): SmallInt; stdcall; External GTDLL;
function GT_EnableEncResponseCheck(control:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_DisableEncResponseCheck(control:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_2DCompareMode(chn:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DComparePulse(chn:SmallInt;level:SmallInt;outputType:SmallInt;time:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareStop(chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareClear(chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareStatus(chn:SmallInt;out pStatus:SmallInt;out pCount:LongInt;out pFifo:SmallInt;out pFifoCount:SmallInt;out pBufCount:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareSetPrm(chn:SmallInt;out pPrm:T2DComparePrm): SmallInt; stdcall; External GTDLL;
function GT_2DCompareData(chn:SmallInt;count:SmallInt;out pBuf:T2DCompareData;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareStart(chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareClearData(chn:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_2DCompareSetPreOutTime(chn:SmallInt;preOutputTime:Double): SmallInt; stdcall; External GTDLL;

function GT_SetAxisMode(axis:SmallInt;mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisMode(axis:SmallInt;out ppMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetHSIOOpt(value:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetHSIOOpt(out pValue:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LaserPowerMode(laserPowerMode:SmallInt;maxValue:Double;minValue:Double;channel:SmallInt=0;delaymode:SmallInt =0): SmallInt; stdcall; External GTDLL;
function GT_LaserPrfCmd(outputCmd:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_LaserOutFrq(outFrq:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetPulseWidth(width:LongWord;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetWaitPulse(mode:Word;waitPulseFrq:Double;waitPulseDuty:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetPreVltg(mode:Word;voltageValue:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLevelDelay(offDelay:Word;onDelay:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_EnaFPK(time1:Word;time2:Word;laserOffDelay:Word;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_DisFPK(channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisMode(mode:SmallInt;source:SmallInt;out pPos:LongInt;out pScale:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisRatio(out pRatio:Double;minPower:Double;maxPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetWaitPulseEx(mode:Word;waitPulseFrq:Double;waitPulseDuty:Double): SmallInt; stdcall; External GTDLL;
function GT_SetLaserMode(mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetLaserFollowSpline(tableId:SmallInt;n:LongInt;var pX:Double;var pY:Double;beginValue:Double;endValue:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetLaserFollowSpline(tableId:SmallInt;n:LongInt;out pX:Double;out pY:Double;out pA:Double;out pB:Double;out pC:Double;out pCount:LongInt;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;

//ExtMdl
function GT_OpenExtMdl(out pDllName:String): SmallInt; stdcall; External GTDLL;
function GT_CloseExtMdl(): SmallInt; stdcall; External GTDLL;
function GT_SwitchtoCardNoExtMdl(card:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_ResetExtMdl(): SmallInt; stdcall; External GTDLL;
function GT_LoadExtConfig(var pFileName:String): SmallInt; stdcall; External GTDLL;
function GT_SetExtIoValue(mdl:SmallInt;value:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtIoValue(mdl:SmallInt;out pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_SetExtIoBit(mdl:SmallInt;index:SmallInt;value:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtIoBit(mdl:SmallInt;index:SmallInt;out pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtAdValue(mdl:SmallInt;chn:SmallInt;out pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtAdVoltage(mdl:SmallInt;chn:SmallInt;out pValue:Double): SmallInt; stdcall; External GTDLL;
function GT_SetExtDaValue(mdl:SmallInt;chn:SmallInt;value:Word): SmallInt; stdcall; External GTDLL;
function GT_SetExtDaVoltage(mdl:SmallInt;chn:SmallInt;value:Double): SmallInt; stdcall; External GTDLL;
function GT_GetStsExtMdl(mdl:SmallInt;chn:SmallInt;var pStatus:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtDoValue(mdl:SmallInt;var pValue:Word): SmallInt; stdcall; External GTDLL;
function GT_GetExtMdlMode(var pMode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetExtMdlMode(mode:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_UploadConfig(): SmallInt; stdcall; External GTDLL;
function GT_DownloadConfig(): SmallInt; stdcall; External GTDLL;

function GT_GetUuid(out pCode:String;count:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetUuid(var pCode:String;count:SmallInt): SmallInt; stdcall; External GTDLL;

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

function GT_SetCompensate2DTable(tableIndex : SmallInt;var pTable:TCompensate2DTable ;var pData:LongInt;externComp:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate2DTable(tableIndex : SmallInt;out pTable:TCompensate2DTable ;out pExternComp:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetCompensate2D(axis : SmallInt;var pComp2d:TCompensate2D): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate2D(axis : SmallInt;out pComp2d:TCompensate2D): SmallInt; stdcall; External GTDLL;
function GT_GetCompensate2DValue(axis : SmallInt;out pValue:Double): SmallInt; stdcall; External GTDLL;

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
function GT_GoHome(axis : SmallInt;var pHomePrm:THomePrm ): SmallInt; stdcall; External GTDLL;
function GT_GetHomePrm(axis : SmallInt;out pHomePrm:THomePrm): SmallInt; stdcall; External GTDLL;
function GT_GetHomeStatus(axis : SmallInt;out pHomeStatus:THomeStatus ): SmallInt; stdcall; External GTDLL;

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
function GT_SetControlConfigEx(control:SmallInt;var pControl:TControlConfigEx ): SmallInt; stdcall; External GTDLL;
function GT_GetControlConfigEx(control:SmallInt;out pControl:TControlConfigEx ): SmallInt; stdcall; External GTDLL;

//Adc filter
type TAdcConfig = record
	active:SmallInt;	
	reverse:SmallInt;	
	a:Double;			
	b:Double;				
	filterMode:SmallInt;	
end;

function GT_SetAdcConfig(adc:SmallInt;var pAdc:TAdcConfig): SmallInt; stdcall; External GTDLL;
function GT_GetAdcConfig(adc:SmallInt;out pAdc:TAdcConfig): SmallInt; stdcall; External GTDLL;
function GT_SetAdcFilterPrm(adc:SmallInt;k:Double): SmallInt; stdcall; External GTDLL;
function GT_GetAdcFilterPrm(adc:SmallInt;out pk:double): SmallInt; stdcall; External GTDLL;

//Superimposed
function GT_SetControlSuperimposed(control:SmallInt;superimposedType:SmallInt;superimposedIndex:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetControlSuperimposed(control:SmallInt;out pSuperimposedType:SmallInt;out pSuperimposedIndex:SmallInt): SmallInt; stdcall; External GTDLL;

//
function GT_ZeroLaserOnTime(channel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetLaserOnTime(channel:SmallInt;out pTime:LongWord): SmallInt; stdcall; External GTDLL;

function GT_SetProfileScale(axis:SmallInt;alpha:LongInt;beta:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetProfileScale(axis:SmallInt;out pAlpha:LongInt;out pBeta:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetEncoderScale(axis:SmallInt;alpha:LongInt;beta:LongInt): SmallInt; stdcall; External GTDLL;
function GT_GetEncoderScale(axis:SmallInt;out pAlpha:LongInt;out pBeta:LongInt): SmallInt; stdcall; External GTDLL;

function GT_MultiAxisOn(mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_MultiAxisOff(mask:LongInt): SmallInt; stdcall; External GTDLL;
function GT_SetAxisOnDelayTime(ms:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAxisOnDelayTime(out pMs:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetLaserDisTable1D(count:SmallInt;var pRatio:Double;var pPos:LongInt;minPower:Double;maxPower:Double;var pLimitPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisTable2D(var axisIndex:SmallInt;var count:SmarllInt;var pRatio:Double;var pXPos:Double;var pYPos:Double;
																minPower:Double;maxPower:Double;var pLimitPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserDisTable2DEx(var axisIndex:SmallInt;var count:SmallInt;pRatio:Double;var posBegin:LongInt;var posStep:LongInt;
																	minPower:Double;maxPower:Double;var pLimitPower:Double;channel:SmallInt=0): SmallInt; stdcall; External GTDLL;
function GT_SetLaserCrdMap(channel:SmallInt;map:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetLaserCrdMap(channel:SmallInt;out pMap:SmallInt): SmallInt; stdcall; External GTDLL;

//AutoFocus
function GT_AutoFocus(mode:Word;kp:Double;reverse:SmallInt;chanel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAutoFocusRefVol(refVol:Double;maxVol:Double;minVol:Double;chanel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetAutoFocusStatus(out pStatus:Word;count:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_ConfigAutoFocus(chnAdc:SmallInt;chanel:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetAutoFocusAuxPrm(kf:Double;kd:Double;limitKd:Double;chanel:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_Delay(time:Word): SmallInt; stdcall; External GTDLL;
function GT_DelayHighPrecision(time:Word): SmallInt; stdcall; External GTDLL;

function GT_SetCrdBufferMode(crd:SmallInt;bufferMode:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdBufferMode(crd:SmallInt;out pBufferMode:SmallInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdSegmentTime(crd:SmallInt;segmentIndex:LongInt;out pSegmentTime:Double;out pSegmentNumber:LongInt;fifo:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_GetCrdTime(crd:SmallInt;out pTime:TCrdTime;fifo:SmallInt): SmallInt; stdcall; External GTDLL;

function GT_SetLeadScrewLink(axis:SmallInt;link:SmallInt): SmallInt; stdcall; External GTDLL;
function GT_SetLeadScrewLink(axis:SmallInt;out pLink:SmallInt): SmallInt; stdcall; External GTDLL;

implementation

end.
