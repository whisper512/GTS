Attribute VB_Name = "gts_cfg"

Public Const RES_LIMIT As Integer = 8
Public Const RES_ALARM As Integer = 8
Public Const RES_HOME As Integer = 8
Public Const RES_GPI As Integer = 16
Public Const RES_ARRIVE As Integer = 8
Public Const RES_MPG As Integer = 7

Public Const RES_ENABLE As Integer = 8
Public Const RES_CLEAR As Integer = 8
Public Const RES_GPO = 16

Public Const RES_DAC As Integer = 12
Public Const RES_STEP As Integer = 8
Public Const RES_PULSE As Integer = 8
Public Const RES_ENCODER As Integer = 11
Public Const RES_LASER As Integer = 2  

Public Const AXIS_MAX As Integer = 8
Public Const PROFILE_MAX As Integer = 8
Public Const CONTROL_MAX As Integer = 8

Public Const PRF_MAP_MAX As Integer = 2
Public Const ENC_MAP_MAX As Integer = 2

Public Const STEP_DIR As Integer = 0
Public Const STEP_PULSE As Integer = 1

Public Const CRD_BUF_DATA_NULL As Integer = 0

Public Type TDiConfig
    active As Integer
    reverse As Integer
    filterTime As Integer
End Type

Public Type TCountConfig
    active As Integer
    reverse As Integer
    filterType As Integer

    captureSource As Integer
    captureHomeSense As Integer
    captureIndexSense As Integer
End Type

Public Type TDoConfig
    active As Integer
    axis As Integer
    axisItem As Integer
    reverse As Integer
End Type

Public Type TStepConfig
    active As Integer
    axis As Integer
    mode As Integer
    parameter As Integer
    reverse As Integer
End Type

Public Type TDacConfig
    active As Integer
    control As Integer
    reverse As Integer
    bias As Integer
    limit As Integer
End Type
Public Type TControlConfig
    active As Integer
    axis As Integer
    encoder1 As Integer
    encoder2 As Integer
    errorLimit As Long
    filterType1 As Integer
    filterType2 As Integer
    filterType3 As Integer
    encoderSmooth As Integer
    controlSmooth As Integer
End Type

Public Type TProfileConfig
    active As Integer
    decSmoothStop As Double
     decAbruptStop As Double
End Type

Public Type TAxisConfig
    active As Integer
    alarmType As Integer
    alarmIndex As Integer
    limitPositiveType As Integer
    limitPositiveIndex As Integer
    limitNegativeType As Integer
    limitNegativeIndex As Integer
    smoothStopType As Integer
    smoothStopIndex As Integer
    abruptStopType As Integer
    abruptStopIndex As Integer
     prfMap As Long
     encMap As Long
    prfMapAlpha1 As Integer
    prfMapAlpha2 As Integer
    prfMapBeta1 As Integer
    prfMapBeta2 As Integer
    encMapAlpha1 As Integer
    encMapAlpha2 As Integer
    encMapBeta1 As Integer
    encMapBeta2 As Integer
End Type

Public Type TMcConfig
    profile1 As TProfileConfig
    profile2 As TProfileConfig
    profile3 As TProfileConfig
    profile4 As TProfileConfig
    profile5 As TProfileConfig
    profile6 As TProfileConfig
    profile7 As TProfileConfig
    profile8 As TProfileConfig
    axis1 As TAxisConfig
    axis2 As TAxisConfig
    axis3 As TAxisConfig
    axis4 As TAxisConfig
    axis5 As TAxisConfig
    axis6 As TAxisConfig
    axis7 As TAxisConfig
    axis8 As TAxisConfig
    control1 As TControlConfig
    control2 As TControlConfig
    control3 As TControlConfig
    control4 As TControlConfig
    control5 As TControlConfig
    control6 As TControlConfig
    control7 As TControlConfig
    control8 As TControlConfig
    dac1 As TDacConfig
    dac2 As TDacConfig
    dac3 As TDacConfig
    dac4 As TDacConfig
    dac5 As TDacConfig
    dac6 As TDacConfig
    dac7 As TDacConfig
    dac8 As TDacConfig
    dac9 As TDacConfig
    dac10 As TDacConfig
    dac11 As TDacConfig
    dac12 As TDacConfig
    step1 As TStepConfig
    step2 As TStepConfig
    step3 As TStepConfig
    step4 As TStepConfig
    step5 As TStepConfig
    step6 As TStepConfig
    step7 As TStepConfig
    step8 As TStepConfig
    encoder1 As TCountConfig
    encoder2 As TCountConfig
    encoder3 As TCountConfig
    encoder4 As TCountConfig
    encoder5 As TCountConfig
    encoder6 As TCountConfig
    encoder7 As TCountConfig
    encoder8 As TCountConfig
    encoder9 As TCountConfig
    encoder10 As TCountConfig
    encoder11 As TCountConfig
    pulse1 As TCountConfig
    pulse2 As TCountConfig
    pulse3 As TCountConfig
    pulse4 As TCountConfig
    pulse5 As TCountConfig
    pulse6 As TCountConfig
    pulse7 As TCountConfig
    pulse8 As TCountConfig
    enable1 As TDoConfig
    enable2 As TDoConfig
    enable3 As TDoConfig
    enable4 As TDoConfig
    enable5 As TDoConfig
    enable6 As TDoConfig
    enable7 As TDoConfig
    enable8 As TDoConfig
    clear1 As TDoConfig
    clear2 As TDoConfig
    clear3 As TDoConfig
    clear4 As TDoConfig
    clear5 As TDoConfig
    clear6 As TDoConfig
    clear7 As TDoConfig
    clear8 As TDoConfig
    gpo1 As TDoConfig
    gpo2 As TDoConfig
    gpo3 As TDoConfig
    gpo4 As TDoConfig
    gpo5 As TDoConfig
    gpo6 As TDoConfig
    gpo7 As TDoConfig
    gpo8 As TDoConfig
    gpo9 As TDoConfig
    gpo10 As TDoConfig
    gpo11 As TDoConfig
    gpo12 As TDoConfig
    gpo13 As TDoConfig
    gpo14 As TDoConfig
    gpo15 As TDoConfig
    gpo16 As TDoConfig
    limitPositive1 As TDiConfig
    limitPositive2 As TDiConfig
    limitPositive3 As TDiConfig
    limitPositive4 As TDiConfig
    limitPositive5 As TDiConfig
    limitPositive6 As TDiConfig
    limitPositive7 As TDiConfig
    limitPositive8 As TDiConfig
    limitNegative1 As TDiConfig
    limitNegative2 As TDiConfig
    limitNegative3 As TDiConfig
    limitNegative4 As TDiConfig
    limitNegative5 As TDiConfig
    limitNegative6 As TDiConfig
    limitNegative7 As TDiConfig
    limitNegative8 As TDiConfig
    alarm1 As TDiConfig
    alarm2 As TDiConfig
    alarm3 As TDiConfig
    alarm4 As TDiConfig
    alarm5 As TDiConfig
    alarm6 As TDiConfig
    alarm7 As TDiConfig
    alarm8 As TDiConfig
    home1 As TDiConfig
    home2 As TDiConfig
    home3 As TDiConfig
    home4 As TDiConfig
    home5 As TDiConfig
    home6 As TDiConfig
    home7 As TDiConfig
    home8 As TDiConfig
    gpi1 As TDiConfig
    gpi2 As TDiConfig
    gpi3 As TDiConfig
    gpi4 As TDiConfig
    gpi5 As TDiConfig
    gpi6 As TDiConfig
    gpi7 As TDiConfig
    gpi8 As TDiConfig
    gpi9 As TDiConfig
    gpi10 As TDiConfig
    gpi11 As TDiConfig
    gpi12 As TDiConfig
    gpi13 As TDiConfig
    gpi14 As TDiConfig
    gpi15 As TDiConfig
    gpi16 As TDiConfig
    arrive1 As TDiConfig
    arrive2 As TDiConfig
    arrive3 As TDiConfig
    arrive4 As TDiConfig
    arrive5 As TDiConfig
    arrive6 As TDiConfig
    arrive7 As TDiConfig
    arrive8 As TDiConfig
		mpg1 As TDiConfig
		mpg2 As TDiConfig
		mpg3 As TDiConfig
		mpg4 As TDiConfig
		mpg5 As TDiConfig
		mpg6 As TDiConfig
		mpg7 As TDiConfig
End Type



Public Declare Function  GT_SetDiConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal diType As Integer,ByVal diIndex As Integer,ByRef pDi As TDiConfig) As Integer
Public Declare Function  GT_GetDiConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal diType As Integer,ByVal diIndex As Integer,ByRef pDi As TDiConfig) As Integer
Public Declare Function  GT_SetDoConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer,ByVal doIndex As Integer,ByRef pDo As TDoConfig) As Integer
Public Declare Function  GT_GetDoConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal doType As Integer,ByVal doIndex As Integer,ByRef pDo As TDoConfig) As Integer
Public Declare Function  GT_SetStepConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal mcStep As Integer,ByRef pStep As TStepConfig) As Integer
Public Declare Function  GT_GetStepConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal mcStep As Integer,ByRef pStep As TStepConfig) As Integer
Public Declare Function  GT_SetDacConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer,ByRef pDac As TDacConfig) As Integer
Public Declare Function  GT_GetDacConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal dac As Integer,ByRef pDac As TDacConfig) As Integer
Public Declare Function  GT_SetCountConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal countType As Integer,ByVal countIndex As Integer,ByRef pCount As TCountConfig) As Integer
Public Declare Function  GT_GetCountConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal countType As Integer,ByVal countIndex As Integer,ByRef pCount As TCountConfig) As Integer
Public Declare Function  GT_SetControlConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer,ByRef pControl As TControlConfig) As Integer
Public Declare Function  GT_GetControlConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal control As Integer,ByRef pControl As TControlConfig) As Integer
Public Declare Function  GT_SetProfileConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer,ByRef pProfile As TProfileConfig) As Integer
Public Declare Function  GT_GetProfileConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal profile As Integer,ByRef pProfile As TProfileConfig) As Integer
Public Declare Function  GT_SetAxisConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer,ByRef pAxis As TAxisConfig) As Integer
Public Declare Function  GT_GetAxisConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal axis As Integer,ByRef pAxis As TAxisConfig) As Integer
Public Declare Function  GT_GetConfigTable Lib "gts.dll" (ByVal cardNum As Integer,ByVal type1 As Integer,ByRef pCount As Integer) As Integer
Public Declare Function  GT_GetConfigTableAll Lib "gts.dll" (ByVal cardNum As Integer)As Integer

Public Declare Function  GT_SetMcConfig Lib "gts.dll" (ByVal cardNum As Integer,ByRef pMc As TMcConfig) As Integer
Public Declare Function  GT_GetMcConfig Lib "gts.dll" (ByVal cardNum As Integer,ByRef pMc As TMcConfig) As Integer

Public Declare Function  GT_SetMcConfigToFile Lib "gts.dll" (ByVal cardNum As Integer,ByRef pMc As TMcConfig,ByVal pFile As String) As Integer
Public Declare Function  GT_GetMcConfigFromFile Lib "gts.dll" (ByVal cardNum As Integer,ByRef pMc As TMcConfig,ByVal pFile As String) As Integer

Public Declare Function  GT_SaveConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFile As String)As Integer

Public Declare Function  GT_GetInterruptTime Lib "gts.dll" (ByVal cardNum As Integer,ByRef pServoRunTime As Double,ByRef pProfileRunTime As Double)As Integer
Public Declare Function  GT_GetInterruptTimeMax Lib "gts.dll" (ByVal cardNum As Integer,ByRef pServoRunTimeMax As Double,ByRef pProfileRunTimeMax As Double) As Integer

'New Watch
Public Const WATCH_MODE_STATIC As Integer = 0
Public Const WATCH_MODE_LOOP As Integer = 1
Public Const WATCH_MODE_DYNAMIC As Integer = 2

Public Const WATCH_MODE_STATIC_BACKGROUND As Integer = 10
Public Const WATCH_MODE_LOOP_BACKGROUND As Integer = 11
Public Const WATCH_MODE_DYNAMIC_BACKGROUND As Integer = 12

Public Const WATCH_EVENT_RUN As Integer = 1
Public Const WATCH_EVENT_START As Integer = 10
Public Const WATCH_EVENT_STOP As Integer = 20
Public Const WATCH_EVENT_OFF As Integer = 30

Public Const WATCH_CONDITION_EQ As Integer = 1
Public Const WATCH_CONDITION_NE As Integer = 2
Public Const WATCH_CONDITION_GE As Integer = 3
Public Const WATCH_CONDITION_LE As Integer = 4

Public Const WATCH_CONDITION_CHANGE_TO As Integer = 11
Public Const WATCH_CONDITION_CHANGE As Integer = 12
Public Const WATCH_CONDITION_UP As Integer = 13
Public Const WATCH_CONDITION_DOWN As Integer = 14

Public Const WATCH_CONDITION_REMAIN_AT As Integer = 21
Public Const WATCH_CONDITION_REMAIN As Integer = 22

Public Const WATCH_VAR_CLOCK As Long = 1200
Public Const WATCH_VAR_PRF_LOOP	 As Long = 1201

Public Const WATCH_VAR_COMMAND_CODE As Long = 1220
Public Const WATCH_VAR_COMMAND_DATA	As Long = 1221
Public Const WATCH_VAR_COMMAND_COUNT As Long = 1222
Public Const WATCH_VAR_COMMAND_READ_FLAG As Long = 1223

Public Const WATCH_VAR_PRF_POS As Long = 6000
Public Const WATCH_VAR_PRF_VEL As Long = 6001
Public Const WATCH_VAR_PRF_ACC As Long = 6002

Public Const WATCH_VAR_PRF_RUN As Long = 6200

Public Const WATCH_VAR_CRD_PRF_POS As Long = 8000
Public Const WATCH_VAR_CRD_PRF_VEL As Long = 8001
Public Const WATCH_VAR_CRD_PRF_ACC As Long = 8002

Public Const WATCH_VAR_CRD_RUN As Long = 8200

Public Const WATCH_VAR_CRD_SEGMENT_NUMBER As Long = 8202
Public Const WATCH_VAR_CRD_SEGMENT_NUMBER_USER As Long = 8203
Public Const WATCH_VAR_CRD_COMMAND_RECEIVE As Long = 8204
Public Const WATCH_VAR_CRD_COMMAND_EXECUTE As Long = 8205

Public Const WATCH_VAR_CRD_FOLLOW_SLAVE_POS As Long = 8600
Public Const WATCH_VAR_CRD_FOLLOW_SLAVE_VEL As Long = 8601

Public Const WATCH_VAR_CRD_FOLLOW_STAGE As Long = 8610

Public Const WATCH_VAR_SCAN_PRF_POS As Long = 18000
Public Const WATCH_VAR_SCAN_PRF_VEL As Long = 18001
Public Const WATCH_VAR_SCAN_PRF_ACC As Long = 18002

Public Const WATCH_VAR_SCAN_PRF_POS_X As Long = 18010
Public Const WATCH_VAR_SCAN_PRF_POS_Y As Long = 18020

Public Const WATCH_VAR_SCAN_RUN As Long = 18200

Public Const WATCH_VAR_SCAN_SEGMENT_NUMBER As Long = 18202


Public Const WATCH_VAR_LASER_HSIO As Long = 18600
Public Const WATCH_VAR_LASER_POWER As Long = 18601

Public Const WATCH_VAR_AXIS_PRF_POS As Long = 20000
Public Const WATCH_VAR_AXIS_PRF_VEL As Long = 20001
Public Const WATCH_VAR_AXIS_PRF_ACC	As Long = 20002
Public Const WATCH_VAR_AXIS_ENC_POS As Long = 20003

Public Const WATCH_VAR_AXIS_PRF_VEL_FILTER As Long = 20011

Public Const WATCH_VAR_ENC_POS As Long = 30000

Public Const WATCH_VAR_ENC_VEL As Long = 30001

Public Const WATCH_VAR_GPI As Long = 31000

Public Const WATCH_VAR_GPO As Long = 32000

Public Const WATCH_VAR_AI As Long = 33000

Public Const WATCH_VAR_A As Long = 34000

Public Const WATCH_VAR_AUTO_FOCUS_OUT As Long = 34006

Public Const WATCH_VAR_TRIGGER_EXECUTE As Long = 38000
Public Const WATCH_VAR_TRIGGER_STATUS As Long = 38001
Public Const WATCH_VAR_TRIGGER_POSITION As Long = 38002
Public Const WATCH_VAR_TRIGGER_COUNT As Long = 38010

Public Const WATCH_VAR_POS_LOOP_ERROR As Long = 40000

Public Const WATCH_VAR_CONTROL_REF_VEL As Long = 41000

Public Const WATCH_VAR_WATCH_TIME As Long = 52001

Public Const WATCH_VAR_INT32 As Long = 52020
Public Const WATCH_VAR_INT64 As Long = 52021
Public Const WATCH_VAR_FLOAT As Long = 52022
Public Const WATCH_VAR_DOUBLE As Long = 52023
Public Const WATCH_VAR_BOOL As Long = 52024

Public Type  TWatchVar
	type As Integer
	index As Integer
	id As Integer
End Type

Public Type  TWatchEvent
	type As Integer
	watchLoop As Integer
	watchCount As Integer
	var As TWatchVar
	condition As Integer
	value As Double
End Type

Public Declare Function  GT_ClearWatch Lib "gts.dll" (ByVal cardNum As Integer,ByVal mode As Integer) As Integer
Public Declare Function  GT_AddWatchVar Lib "gts.dll" (ByVal cardNum As Integer,ByRef pVar As TWatchVar) As Integer
Public Declare Function  GT_AddWatchEvent Lib "gts.dll" (ByVal cardNum As Integer,ByRef pEvent As TWatchEvent) As Integer
Public Declare Function  GT_WatchOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal interval As Integer,ByVal mode As Integer,ByVal count As Integer) As Integer
Public Declare Function  GT_WatchOff Lib "gts.dll" (ByVal cardNum As Integer)As Integer
Public Declare Function  GT_PrintWatch Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFileName As String,ByVal start As Long,ByVal printCount As Long) As Integer
Public Declare Function  GT_GetMcVar Lib "gts.dll" (ByVal cardNum As Integer,ByRef pVar As TWatchVar,ByRef pValue As Double) As Integer

Public Declare Function  GT_SetWatchGroup Lib "gts.dll" (ByVal cardNum As Integer,ByVal group As Integer) As Integer
Public Declare Function  GT_GetWatchGroup Lib "gts.dll" (ByVal cardNum As Integer,ByRef pGroup As Integer)As Integer
Public Declare Function  GT_LoadWatchConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal pFile As String) As Integer
Public Declare Function  GT_SaveWatchConfig Lib "gts.dll" (ByVal cardNum As Integer,ByVal group As Integer,ByVal pFile As String) As Integer
Public Declare Function  GT_ReadWatch Lib "gts.dll" (ByVal cardNum As Integer,ByVal varIndex As Integer,ByRef pBuffer As Double,ByVal bufferSize As Long,ByRef pReadCount As Long) As Integer

Public Type  TWatchInfo
	enable As Integer					' 采集使能
	run As Integer							' 采集状态
	time As Long					' 采集次数
	head As Long					' 头指针
	threshold As Long			' 最多容纳采集次数

	interval As Integer					' 采集间隔
	mode As Integer							' 采集模式
	countBeforeEvent As Integer	' 事件触发之前的采集数量
	countAfterEvent As Integer		' 事件触发以后的采集数量
	varCount As Integer			' 采集变量数量
	eventCount As Integer			' 采集事件数量
End Type

Public Type  TWatchVarInfo
	pAddress As Long
	length As Integer
	fraction As Integer
	format As Integer
	hex As Integer
	sign As Integer
	bit As Integer
End Type

Public Type  TWatchFormat
	width As Integer
	precision As Integer
	seperator As Byte
	hex As Integer
End Type

Public Declare Function  GT_GetWatchInfo Lib "gts.dll" (ByVal cardNum As Integer,ByRef pInfo As TWatchInfo) As Integer
Public Declare Function  GT_GetWatchVar Lib "gts.dll" (ByVal cardNum As Integer,ByVal index As Integer,ByRef pVar As TWatchVar,ByRef pVarInfo As TWatchVarInfo) As Integer
Public Declare Function  GT_GetWatchEvent Lib "gts.dll" (ByVal cardNum As Integer,ByVal index As Integer,ByRef pEvent As TWatchEvent) As Integer
Public Declare Function  GT_SetWatchFormat Lib "gts.dll" (ByVal cardNum As Integer,ByRef pFormat As TWatchFormat) As Integer
Public Declare Function  GT_GetWatchFormat Lib "gts.dll" (ByVal cardNum As Integer,ByRef pFormat As TWatchFormat) As Integer

'Event and Task
Public Const TASK_SET_DO_BIT As Integer = &H1101
Public Const TASK_CRD_START As Integer = &H4004
Public Const TASK_CRD_STOP As Integer = &H4005
Public Const TASK_CRD_OVERRIDE As Integer = &H4006

Public Type  TTaskSetDoBit
	doType As Integer
	doIndex As Integer
	doValue As Byte
	mode As Integer
	parameter1 As Long
	parameter2 As Long
	parameter3 As Long
	parameter4 As Long
	parameter5 As Long
	parameter6 As Long
	parameter7 As Long
	parameter8 As Long
End Type

Public Type  TTaskCrdStart
	mask As Integer
	option As Integer
End Type

Public Type  TTaskCrdStop
	mask As Integer
	option As Integer
End Type

Public Type  TTaskCrdOverride
	crd As Integer
	synVelOverride As Double
End Type

Public Type  TEvent
	loop As Long
	var As TWatchVar
	condition As Integer
	value As Double
End Type

Public Declare Function  GT_ClearEvent Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function  GT_ClearTask Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function  GT_ClearEventTaskLink Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function  GT_AddEvent Lib "gts.dll" (ByVal cardNum As Integer,ByRef pEvent As TEvent,pEventIndex As Integer) As Integer
Public Declare Function  GT_AddTask Lib "gts.dll" (ByVal cardNum As Integer,ByVal taskType As Integer,ByRef pTaskData As Long,ByRef pTaskIndex As Integer) As Integer
Public Declare Function  GT_AddEventTaskLink Lib "gts.dll" (ByVal cardNum As Integer,ByVal eventIndex As Integer,ByVal taskIndex As Integer,ByRef pLinkIndex As Integer) As Integer
Public Declare Function  GT_GetEventCount Lib "gts.dll" (ByVal cardNum As Integer,ByRef pCount As Integer) As Integer
Public Declare Function  GT_GetEvent Lib "gts.dll" (ByVal cardNum As Integer,ByVal eventIndex As Integer,ByRef pEvent As TEvent) As Integer
Public Declare Function  GT_GetEventLoop Lib "gts.dll" (ByVal cardNum As Integer,ByVal eventIndex As Integer,ByRef pCount As Long) As Integer
Public Declare Function  GT_GetTaskCount Lib "gts.dll" (ByVal cardNum As Integer,ByRef pCount As Integer) As Integer
Public Declare Function  GT_GetTask Lib "gts.dll" (ByVal cardNum As Integer,ByVal taskIndex As Integer,ByRef pTaskType As Integer,ByRef pTaskData As Long) As Integer
Public Declare Function  GT_GetEventTaskLinkCount Lib "gts.dll" (ByVal cardNum As Integer,ByRef pCount As Integer) As Integer
Public Declare Function  GT_GetEventTaskLink Lib "gts.dll" (ByVal cardNum As Integer,ByVal linkIndex As Integer,ByRef pEventIndex As Integer,ByRef pTaskIndex As Integer) As Integer
Public Declare Function  GT_EventOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal eventIndex As Integer,ByVal count As Integer) As Integer
Public Declare Function  GT_EventOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal eventIndex As Integer,ByVal count As Integer) As Integer
Public Declare Function  GT_BufEventOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer,ByVal eventIndex As Integer,ByVal count As Integer,ByVal fifo As Integer) As Integer
Public Declare Function  GT_BufEventOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer,ByVal eventIndex As Integer,ByVal count As Integer,ByVal fifo As Integer) As Integer

Public Const VAR_CALCULATE_NONE As Integer = 0
Public Const VAR_CALCULATE_OR As Integer = 1
Public Const VAR_CALCULATE_AND As Integer = 3
Public Const VAR_CALCULATE_NOT As Integer = 5

Public Const VAR_CALCULATE_ADD As Integer = 11
Public Const VAR_CALCULATE_SUB As Integer = 12
Public Const VAR_CALCULATE_MUL As Integer = 13
Public Const VAR_CALCULATE_DIV As Integer = 14

Public Type  TWatchCondition
	var As TWatchVar
	condition As Integer
	value As Double
End Type

Public Type  TVarCalculate
	operation As Integer
	varType As Integer
	result As Integer
	lhs As Integer
	rhs As Integer
End Type

Public Declare Function  GT_ClearVar Lib "gts.dll" (ByVal cardNum As Integer) As Integer
Public Declare Function  GT_SetVarBoolCondition Lib "gts.dll" (ByVal cardNum As Integer,ByVal varIndex As Integer,ByRef pWatchCondition As TWatchCondition) As Integer
Public Declare Function  GT_GetVarBoolCondition Lib "gts.dll" (ByVal cardNum As Integer,ByVal varIndex As Integer,ByRef pWatchCondition As TWatchCondition) As Integer
Public Declare Function  GT_AddVarCalculate Lib "gts.dll" (ByVal cardNum As Integer,ByRef pVarCalculate As TVarCalculate,ByRef pIndex As Integer) As Integer
Public Declare Function  GT_GetVarCalculateCount Lib "gts.dll" (ByVal cardNum As Integer,ByRef pCount As Integer) As Integer
Public Declare Function GT_GetVarCalculate Lib "gts.dll" (ByVal cardNum As Integer, ByVal index As Integer, ByRef pVarCalculate As TVarCalculate) As Integer

Public Type TWatchVarEx
        type As Long
        index As Integer
        id As Integer
End Type

Public Declare Function GT_AddWatchVarEx Lib "gts.dll" (ByVal cardNum As Integer, ByRef pVar As TWatchVarEx) As Integer