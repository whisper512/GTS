uint gts_cfg;

interface

const GTDll = 'gts.dll';

Const RES_LIMIT = 8;
Const RES_ALARM = 8;
Const RES_HOME = 8;
Const RES_GPI = 16;
Const RES_ARRIVE = 8;
Const RES_MPG = 7;

Const RES_ENABLE = 8;
Const RES_CLEAR = 8;
Const RES_GPO = 16;

Const RES_DAC = 12;
Const RES_STEP = 8;
Const RES_PULSE = 8;
Const RES_ENCODER = 11;
Const RES_LASER = 2;

Const AXIS_MAX = 8;
Const PROFILE_MAX = 8;
Const CONTROL_MAX = 8;

Const PRF_MAP_MAX = 2;
Const ENC_MAP_MAX = 2;

Const STEP_DIR = 0;
Const STEP_PULSE = 1;

Const CRD_BUF_DATA_NULL = 0;

type TDiConfig = record
    active :SmallInt;
    reverse :SmallInt;
    filterTime :SmallInt;
end;

type TCountConfig = record
    active :SmallInt;
    reverse :SmallInt;
    filterType :SmallInt;
    captureSource :SmallInt;
    captureHomeSense :SmallInt;
    captureIndexSense :SmallInt;
end;

type TDoConfig = record
    active :SmallInt;
    axis :SmallInt;
    axisItem :SmallInt;
    reverse :SmallInt;
end;

type TStepConfig = record
    active :SmallInt;
    axis :SmallInt;
    mode :SmallInt;
    parameter :SmallInt;
    reverse :SmallInt;
end;

type TDacConfig = record
    active :SmallInt;
    control :SmallInt;
    reverse :SmallInt;
    bias :SmallInt;
    limit :SmallInt;
end;

type TControlConfig = record
    active :SmallInt;
    axis :SmallInt;
    encoder :array[0..1] of SmallInt;
    errorLimit :LongInt;
    filterType :array[0..2] of SmallInt;
    encoderSmooth :SmallInt;
    controlSmooth :SmallInt;
end;

type TProfileConfig = record
    active :SmallInt;
    decSmoothStop :Double;
    decAbruptStop :Double;
end;

type TAxisConfig = record
    active :SmallInt;
    alarmType :SmallInt;
    alarmIndex :SmallInt;
    limitPositiveType :SmallInt;
    limitPositiveIndex :SmallInt;
    limitNegativeType :SmallInt;
    limitNegativeIndex :SmallInt;
    smoothStopType :SmallInt;
    smoothStopIndex :SmallInt;
    abruptStopType :SmallInt;
    abruptStopIndex :SmallInt;
    prfMap :LongInt;
    encMap :LongInt;
    prfMapAlpha :array[0..1] of SmallInt;
    prfMapBeta :array[0..1] of SmallInt;
    encMapAlpha :array[0..1] of SmallInt;
    encMapBeta :array[0..1] of SmallInt; 
end;

type TMcConfig = record
    profile :array[0..7] of TProfileConfig;
    axis :array[0..7] of TAxisConfig;
    control :array[0..7] of TControlConfig;
    dac :array[0..11] of TDacConfig;
    step :array[0..7] of TStepConfig;
    encoder :array[0..9] of TCountConfig;
    pulse :array[0..7] of TCountConfig;
    enable :array[0..7] of TDoConfig;
    clear :array[0..7] of TDoConfig;
    gpo :array[0..15] of TDoConfig;
    limitPositive :array[0..7] of TDiConfig;
    limitNegative :array[0..7] of TDiConfig;
    alarm :array[0..7] of TDiConfig;
    home :array[0..7] of TDiConfig;
    gpi :array[0..15] of TDiConfig;
    arrive :array[0..7] of TDiConfig;
    mpg :array[0..6] of TDiConfig;
end;

function GT_SetDiConfig(diType:SmallInt;diIndex:SmallInt;var pDi:TDiConfig):SmallInt; stdcall; External GTDLL;
function GT_GetDiConfig(diType:SmallInt;diIndex:SmallInt;out pDi:TDiConfig):SmallInt; stdcall; External GTDLL;
function GT_SetDoConfig(doType:SmallInt;doIndex:SmallInt;var pDo:TDoConfig):SmallInt; stdcall; External GTDLL;
function GT_GetDoConfig(doType:SmallInt;doIndex:SmallInt;out pDo:TDoConfig):SmallInt; stdcall; External GTDLL;
function GT_SetStepConfig(step:SmallInt;var pStep:TStepConfig):SmallInt; stdcall; External GTDLL;
function GT_GetStepConfig(step:SmallInt;out pStep:TStepConfig):SmallInt; stdcall; External GTDLL;
function GT_SetDacConfig(dac:SmallInt;var pDac:TDacConfig):SmallInt; stdcall; External GTDLL;
function GT_GetDacConfig(dac:SmallInt;out pDac:TDacConfig):SmallInt; stdcall; External GTDLL;
function GT_SetCountConfig(countType:SmallInt;countIndex:SmallInt;var pCount:TCountConfig):SmallInt; stdcall; External GTDLL;
function GT_GetCountConfig(countType:SmallInt;countIndex:SmallInt;out pCount:TCountConfig):SmallInt; stdcall; External GTDLL;
function GT_SetControlConfig(control:SmallInt;var pControl:TControlConfig):SmallInt; stdcall; External GTDLL;
function GT_GetControlConfig(control:SmallInt;out pControl:TControlConfig):SmallInt; stdcall; External GTDLL;
function GT_SetProfileConfig(profile:SmallInt;var pProfile:TProfileConfig):SmallInt; stdcall; External GTDLL;
function GT_GetProfileConfig(profile:SmallInt;out pProfile:TProfileConfig):SmallInt; stdcall; External GTDLL;
function GT_SetAxisConfig(axis:SmallInt;var pAxis:TAxisConfig):SmallInt; stdcall; External GTDLL;
function GT_GetAxisConfig(axis:SmallInt;out pAxis:TAxisConfig):SmallInt; stdcall; External GTDLL;
function GT_GetConfigTable(type:SmallInt;out pCount:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetConfigTableAll():SmallInt; stdcall; External GTDLL;

function GT_SetMcConfig(var pMc:TMcConfig):SmallInt; stdcall; External GTDLL;
function GT_GetMcConfig(out pMc:TMcConfig):SmallInt; stdcall; External GTDLL;

function GT_SetMcConfigToFile(var pMc:TMcConfig;pFile:String):SmallInt; stdcall; External GTDLL;
function GT_GetMcConfigFromFile(out pMc:TMcConfig;pFile:String):SmallInt; stdcall; External GTDLL;

function GT_SaveConfig(pFile:String):SmallInt; stdcall; External GTDLL;

//New Watch
Const WATCH_MODE_STATIC = 0;
Const WATCH_MODE_LOOP = 1;
Const WATCH_MODE_DYNAMIC = 2;

Const WATCH_MODE_STATIC_BACKGROUND = 10;
Const WATCH_MODE_LOOP_BACKGROUND = 11;
Const WATCH_MODE_DYNAMIC_BACKGROUND = 12;

Const WATCH_EVENT_RUN = 1;
Const WATCH_EVENT_START = 10;
Const WATCH_EVENT_STOP = 20;
Const WATCH_EVENT_OFF = 30;

Const WATCH_CONDITION_EQ = 1;
Const WATCH_CONDITION_NE = 2;
Const WATCH_CONDITION_GE = 3;
Const WATCH_CONDITION_LE = 4;

Const WATCH_CONDITION_CHANGE_TO = 11;
Const WATCH_CONDITION_CHANGE = 12;
Const WATCH_CONDITION_UP = 13;
Const WATCH_CONDITION_DOWN = 14;

Const WATCH_CONDITION_REMAIN_AT = 21;
Const WATCH_CONDITION_REMAIN = 22;

Const WATCH_VAR_CLOCK = 1200;
Const WATCH_VAR_PRF_LOOP = 1201;

Const WATCH_VAR_COMMAND_CODE = 1220;
Const WATCH_VAR_COMMAND_DATA = 1221;
Const WATCH_VAR_COMMAND_COUNT = 1222;
Const WATCH_VAR_COMMAND_READ_FLAG = 1223;

Const WATCH_VAR_PRF_POS = 6000;
Const WATCH_VAR_PRF_VEL = 6001;
Const WATCH_VAR_PRF_ACC = 6002;

Const WATCH_VAR_PRF_RUN = 6200;

Const WATCH_VAR_CRD_PRF_POS = 8000;
Const WATCH_VAR_CRD_PRF_VEL = 8001;
Const WATCH_VAR_CRD_PRF_ACC = 8002;

Const WATCH_VAR_CRD_RUN = 8200;

Const WATCH_VAR_CRD_SEGMENT_NUMBER = 8202;
Const WATCH_VAR_CRD_SEGMENT_NUMBER_USER = 8203;
Const WATCH_VAR_CRD_COMMAND_RECEIVE = 8204;
Const WATCH_VAR_CRD_COMMAND_EXECUTE = 8205;

Const WATCH_VAR_CRD_FOLLOW_SLAVE_POS = 8600;
Const WATCH_VAR_CRD_FOLLOW_SLAVE_VEL = 8601;

Const WATCH_VAR_CRD_FOLLOW_STAGE = 8610;

Const WATCH_VAR_SCAN_PRF_POS = 18000;
Const WATCH_VAR_SCAN_PRF_VEL = 18001;
Const WATCH_VAR_SCAN_PRF_ACC = 18002;

Const WATCH_VAR_SCAN_PRF_POS_X = 18010;
Const WATCH_VAR_SCAN_PRF_POS_Y = 18020;

Const WATCH_VAR_SCAN_RUN = 18200;

Const WATCH_VAR_SCAN_SEGMENT_NUMBER = 18202;


Const WATCH_VAR_LASER_HSIO = 18600;
Const WATCH_VAR_LASER_POWER = 18601;

Const WATCH_VAR_AXIS_PRF_POS = 20000;
Const WATCH_VAR_AXIS_PRF_VEL = 20001;
Const WATCH_VAR_AXIS_PRF_ACC = 20002;
Const WATCH_VAR_AXIS_ENC_POS = 20003;

Const WATCH_VAR_AXIS_PRF_VEL_FILTER = 20011;

Const WATCH_VAR_ENC_POS = 30000;

Const WATCH_VAR_ENC_VEL = 30001;

Const WATCH_VAR_GPI = 31000;

Const WATCH_VAR_GPO = 32000;

Const WATCH_VAR_AI = 33000;

Const WATCH_VAR_AO = 34000;

Const WATCH_VAR_AUTO_FOCUS_OUT = 34006;

Const WATCH_VAR_TRIGGER_EXECUTE = 38000;
Const WATCH_VAR_TRIGGER_STATUS = 38001;
Const WATCH_VAR_TRIGGER_POSITION = 38002;
Const WATCH_VAR_TRIGGER_COUNT = 38010;

Const WATCH_VAR_POS_LOOP_ERROR = 40000;

Const WATCH_VAR_CONTROL_REF_VEL = 41000;

Const WATCH_VAR_WATCH_TIME = 52001;

Const WATCH_VAR_INT32 = 52020;
Const WATCH_VAR_INT64 = 52021;
Const WATCH_VAR_FLOAT = 52022;
Const WATCH_VAR_DOUBLE = 52023;
Const WATCH_VAR_BOOL = 52024;

type TWatchVar = record
    type :Word;
    index :Word;
    id :Word;
end;

type TWatchEvent = record
    type :Word;
    loop :Word;
    watchCount :Word;
    var :TWatchVar;
    condition :Word;
    value :Double;
end;

function GT_ClearWatch(mode:SmallInt=0):SmallInt; stdcall; External GTDLL;
function GT_AddWatchVar(var pVar:TWatchVar):SmallInt; stdcall; External GTDLL;
function GT_SaveConfig(var pEvent:TWatchEvent):SmallInt; stdcall; External GTDLL;
function GT_WatchOn(interval:SmallInt=0;mode:SmallInt=WATCH_MODE_STATIC;count:Word=0):SmallInt; stdcall; External GTDLL;
function GT_WatchOff():SmallInt; stdcall; External GTDLL;
function GT_PrintWatch(pFileName:String;start:LongInt=0;printCount:LongInt=0):SmallInt; stdcall; External GTDLL;
function GT_GetMcVar(out pVar:TWatchVar;out pValue:Double):SmallInt; stdcall; External GTDLL;

function GT_SetWatchGroup(group:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetWatchGroup(out pGroup:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_LoadWatchConfig(pFile:String):SmallInt; stdcall; External GTDLL;
function GT_SaveWatchConfig(group:SamllInt;pFile:String):SmallInt; stdcall; External GTDLL;
function GT_ReadWatch(varIndex:SmallInt;out pBuffer:Double;bufferSize:LongInt;pReadCount:LongInt):SmallInt; stdcall; External GTDLL;

type TWatchInfo = record
    enable :SmallInt;
    run :SmallInt;
    time :LongInt;
    head :LongInt;
    threshold :LongInt;
    interval :SmallInt;
    mode :SmallInt;
    countBeforeEvent :Word;
    countAfterEvent :Word;
    varCount :Word;
    eventCount :Word;
end;

type TWatchVarInfo = record
    pAddress :LongWord;
    length :Word;
    fraction :SmallInt;
    format :Word;
    hex :Word;
    sign :Word;
    bit :Word;
end;

type TWatchFormat = record
    width :SmallInt;
    precision :SmallInt;
    seperator :ShortInt;
    hex :SmallInt;
end;

function GT_GetWatchInfo(out pInfo:TWatchInfo):SmallInt; stdcall; External GTDLL;
function GT_GetWatchVar(index:SmallInt;out pVar:TWatchVar;out pVarInfo:TWatchVarInfo):SmallInt; stdcall; External GTDLL;
function GT_GetWatchEvent(index:SmallInt;out pEvent:TWatchEvent):SmallInt; stdcall; External GTDLL;
function GT_SetWatchFormat(var pFormat:TWatchFormat):SmallInt; stdcall; External GTDLL;
function GT_GetWatchFormat(out pFormat:TWatchFormat):SmallInt; stdcall; External GTDLL;

//Event and Task
Const TASK_SET_DO_BIT = 0x1101;
Const TASK_CRD_START = 0x4004;
Const TASK_CRD_STOP = 0x4005;
Const TASK_CRD_OVERRIDE = 0x4006;

type TTaskSetDoBit = record
    doType :SmallInt;
    doIndex :SmallInt;
    doValue :SmallInt;
    mode :SmallInt;
    parameter :array[0..7] of LongInt;
end;

type TTaskCrdStart = record
    mask :SmallInt;
    option :SmallInt;
end;

type TTaskCrdStop = record
    mask :SmallInt;
    option :SmallInt;
end;

type TTaskCrdOverride = record
    crd :SmallInt;
    synVelOverride :Double;
end;

type TEvent = record
    loop :LongWord;
    var :TWatchVar;
    condition :Word;
    value :Double;
end;

function GT_ClearEvent():SmallInt; stdcall; External GTDLL;
function GT_ClearTask():SmallInt; stdcall; External GTDLL;
function GT_ClearEventTaskLink():SmallInt; stdcall; External GTDLL;
function GT_AddEvent(var pEvent:TEvent;out pEventIndex:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetWatchFormat(taskType:SmallInt;out pTaskData:LongInt;out pTaskIndex:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_AddEventTaskLink(eventIndex:SmallInt;taskIndex:SmallInt;out pLinkIndex:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetEventCount(out pCount:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetEvent(eventIndex:SmallInt;out pEvent:TEvent):SmallInt; stdcall; External GTDLL;
function GT_GetEventLoop(eventIndex:SmallInt;out pCount:LongWord):SmallInt; stdcall; External GTDLL;
function GT_GetTaskCount(out pCount:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetTask(taskIndex:SmallInt;out pTaskType:SmallInt;out pTaskData:LongInt):SmallInt; stdcall; External GTDLL;
function GT_GetEventTaskLinkCount(out pCount:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetEventTaskLink(linkIndex:SamllInt;out pEventIndex:SmallInt;out pTaskIndex:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_EventOn(eventIndex:SmallInt;count:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_EventOff(eventIndex:SmallInt;count:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_BufEventOn(crd:SmallInt;eventIndex:SmallInt;count:SmallInt;fifo:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_BufEventOff(crd:SmallInt;eventIndex:SmallInt;count:SmallInt;fifo:SmallInt):SmallInt; stdcall; External GTDLL;

Const VAR_CALCULATE_NONE = 0;
Const VAR_CALCULATE_OR = 1;
Const VAR_CALCULATE_AND = 3;
Const VAR_CALCULATE_NOT = 5;

Const VAR_CALCULATE_ADD = 11;
Const VAR_CALCULATE_SUB = 12;
Const VAR_CALCULATE_MUL = 13;
Const VAR_CALCULATE_DIV = 14;

type TWatchCondition; = record
    var :TWatchVar;
    condition :Word;
    value :Double;
end;

type TVarCalculate = record
    operation :Word;
    varType :Word;
    result :Word;
    lhs :Word;
    rhs :Word;
end;

function GT_ClearVar():SmallInt; stdcall; External GTDLL;
function GT_SetVarBoolCondition(varIndex:SmallInt;var pWatchCondition:TWatchCondition):SmallInt; stdcall; External GTDLL;
function GT_GetVarBoolCondition(varIndex:SmallInt;out pWatchCondition:TWatchCondition):SmallInt; stdcall; External GTDLL;
function GT_AddVarCalculate(var pVarCalculate:TVarCalculate;var pIndex:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetVarCalculateCount(out pCount:SmallInt):SmallInt; stdcall; External GTDLL;
function GT_GetVarCalculate(index:SmallInt;out pVarCalculate:TVarCalculate):SmallInt; stdcall; External GTDLL;

implementation

end.