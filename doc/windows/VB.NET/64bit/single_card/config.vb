Module gts_cfg

    Public Const RES_LIMIT As Short = 8
    Public Const RES_ALARM As Short = 8
    Public Const RES_HOME As Short = 8
    Public Const RES_GPI As Short = 16
    Public Const RES_ARRIVE As Short = 8
    Public Const RES_MPG As Short = 7

    Public Const RES_ENABLE As Short = 8
    Public Const RES_CLEAR As Short = 8
    Public Const RES_GPO = 16

    Public Const RES_DAC As Short = 12
    Public Const RES_STEP As Short = 8
    Public Const RES_PULSE As Short = 8
    Public Const RES_ENCODER As Short = 11
    Public Const RES_LASER As Short = 2

    Public Const AXIS_MAX As Short = 8
    Public Const PROFILE_MAX As Short = 8
    Public Const CONTROL_MAX As Short = 8

    Public Const PRF_MAP_MAX As Short = 2
    Public Const ENC_MAP_MAX As Short = 2

    Public Const STEP_DIR As Short = 0
    Public Const STEP_PULSE As Short = 1

    Public Const CRD_BUF_DATA_NULL As Short = 0

    Public Structure TDiConfig
        Dim active As Short
        Dim reverse As Short
        Dim filterTime As Short
    End Structure

    Public Structure TCountConfig
        Dim active As Short
        Dim reverse As Short
        Dim filterType As Short

        Dim captureSource As Short
        Dim captureHomeSense As Short
        Dim captureIndexSense As Short
    End Structure

    Public Structure TDoConfig
        Dim active As Short
        Dim axis As Short
        Dim axisItem As Short
        Dim reverse As Short
    End Structure

    Public Structure TStepConfig
        Dim active As Short
        Dim axis As Short
        Dim mode As Short
        Dim parameter As Short
        Dim reverse As Short
    End Structure

    Public Structure TDacConfig
        Dim active As Short
        Dim control As Short
        Dim reverse As Short
        Dim bias As Short
        Dim limit As Short
    End Structure
    Public Structure TControlConfig
        Dim active As Short
        Dim axis As Short
        Dim encoder1 As Short
        Dim encoder2 As Short
        Dim errorLimit As Integer
        Dim filterType1 As Short
        Dim filterType2 As Short
        Dim filterType3 As Short
        Dim encoderSmooth As Short
        Dim controlSmooth As Short
    End Structure

    Public Structure TProfileConfig
        Dim active As Short
        Dim decSmoothStop As Double
        Dim decAbruptStop As Double
    End Structure

    Public Structure TAxisConfig
        Dim active As Short
        Dim alarmType As Short
        Dim alarmIndex As Short
        Dim limitPositiveType As Short
        Dim limitPositiveIndex As Short
        Dim limitNegativeType As Short
        Dim limitNegativeIndex As Short
        Dim smoothStopType As Short
        Dim smoothStopIndex As Short
        Dim abruptStopType As Short
        Dim abruptStopIndex As Short
        Dim prfMap As Integer
        Dim encMap As Integer
        Dim prfMapAlpha1 As Short
        Dim prfMapAlpha2 As Short
        Dim prfMapBeta1 As Short
        Dim prfMapBeta2 As Short
        Dim encMapAlpha1 As Short
        Dim encMapAlpha2 As Short
        Dim encMapBeta1 As Short
        Dim encMapBeta2 As Short
    End Structure

    Public Structure TMcConfig
        Dim profile1 As TProfileConfig
        Dim profile2 As TProfileConfig
        Dim profile3 As TProfileConfig
        Dim profile4 As TProfileConfig
        Dim profile5 As TProfileConfig
        Dim profile6 As TProfileConfig
        Dim profile7 As TProfileConfig
        Dim profile8 As TProfileConfig
        Dim axis1 As TAxisConfig
        Dim axis2 As TAxisConfig
        Dim axis3 As TAxisConfig
        Dim axis4 As TAxisConfig
        Dim axis5 As TAxisConfig
        Dim axis6 As TAxisConfig
        Dim axis7 As TAxisConfig
        Dim axis8 As TAxisConfig
        Dim control1 As TControlConfig
        Dim control2 As TControlConfig
        Dim control3 As TControlConfig
        Dim control4 As TControlConfig
        Dim control5 As TControlConfig
        Dim control6 As TControlConfig
        Dim control7 As TControlConfig
        Dim control8 As TControlConfig
        Dim dac1 As TDacConfig
        Dim dac2 As TDacConfig
        Dim dac3 As TDacConfig
        Dim dac4 As TDacConfig
        Dim dac5 As TDacConfig
        Dim dac6 As TDacConfig
        Dim dac7 As TDacConfig
        Dim dac8 As TDacConfig
        Dim dac9 As TDacConfig
        Dim dac10 As TDacConfig
        Dim dac11 As TDacConfig
        Dim dac12 As TDacConfig
        Dim step1 As TStepConfig
        Dim step2 As TStepConfig
        Dim step3 As TStepConfig
        Dim step4 As TStepConfig
        Dim step5 As TStepConfig
        Dim step6 As TStepConfig
        Dim step7 As TStepConfig
        Dim step8 As TStepConfig
        Dim encoder1 As TCountConfig
        Dim encoder2 As TCountConfig
        Dim encoder3 As TCountConfig
        Dim encoder4 As TCountConfig
        Dim encoder5 As TCountConfig
        Dim encoder6 As TCountConfig
        Dim encoder7 As TCountConfig
        Dim encoder8 As TCountConfig
        Dim encoder9 As TCountConfig
        Dim encoder10 As TCountConfig
        Dim encoder11 As TCountConfig
        Dim pulse1 As TCountConfig
        Dim pulse2 As TCountConfig
        Dim pulse3 As TCountConfig
        Dim pulse4 As TCountConfig
        Dim pulse5 As TCountConfig
        Dim pulse6 As TCountConfig
        Dim pulse7 As TCountConfig
        Dim pulse8 As TCountConfig
        Dim enable1 As TDoConfig
        Dim enable2 As TDoConfig
        Dim enable3 As TDoConfig
        Dim enable4 As TDoConfig
        Dim enable5 As TDoConfig
        Dim enable6 As TDoConfig
        Dim enable7 As TDoConfig
        Dim enable8 As TDoConfig
        Dim clear1 As TDoConfig
        Dim clear2 As TDoConfig
        Dim clear3 As TDoConfig
        Dim clear4 As TDoConfig
        Dim clear5 As TDoConfig
        Dim clear6 As TDoConfig
        Dim clear7 As TDoConfig
        Dim clear8 As TDoConfig
        Dim gpo1 As TDoConfig
        Dim gpo2 As TDoConfig
        Dim gpo3 As TDoConfig
        Dim gpo4 As TDoConfig
        Dim gpo5 As TDoConfig
        Dim gpo6 As TDoConfig
        Dim gpo7 As TDoConfig
        Dim gpo8 As TDoConfig
        Dim gpo9 As TDoConfig
        Dim gpo10 As TDoConfig
        Dim gpo11 As TDoConfig
        Dim gpo12 As TDoConfig
        Dim gpo13 As TDoConfig
        Dim gpo14 As TDoConfig
        Dim gpo15 As TDoConfig
        Dim gpo16 As TDoConfig
        Dim limitPositive1 As TDiConfig
        Dim limitPositive2 As TDiConfig
        Dim limitPositive3 As TDiConfig
        Dim limitPositive4 As TDiConfig
        Dim limitPositive5 As TDiConfig
        Dim limitPositive6 As TDiConfig
        Dim limitPositive7 As TDiConfig
        Dim limitPositive8 As TDiConfig
        Dim limitNegative1 As TDiConfig
        Dim limitNegative2 As TDiConfig
        Dim limitNegative3 As TDiConfig
        Dim limitNegative4 As TDiConfig
        Dim limitNegative5 As TDiConfig
        Dim limitNegative6 As TDiConfig
        Dim limitNegative7 As TDiConfig
        Dim limitNegative8 As TDiConfig
        Dim alarm1 As TDiConfig
        Dim alarm2 As TDiConfig
        Dim alarm3 As TDiConfig
        Dim alarm4 As TDiConfig
        Dim alarm5 As TDiConfig
        Dim alarm6 As TDiConfig
        Dim alarm7 As TDiConfig
        Dim alarm8 As TDiConfig
        Dim home1 As TDiConfig
        Dim home2 As TDiConfig
        Dim home3 As TDiConfig
        Dim home4 As TDiConfig
        Dim home5 As TDiConfig
        Dim home6 As TDiConfig
        Dim home7 As TDiConfig
        Dim home8 As TDiConfig
        Dim gpi1 As TDiConfig
        Dim gpi2 As TDiConfig
        Dim gpi3 As TDiConfig
        Dim gpi4 As TDiConfig
        Dim gpi5 As TDiConfig
        Dim gpi6 As TDiConfig
        Dim gpi7 As TDiConfig
        Dim gpi8 As TDiConfig
        Dim gpi9 As TDiConfig
        Dim gpi10 As TDiConfig
        Dim gpi11 As TDiConfig
        Dim gpi12 As TDiConfig
        Dim gpi13 As TDiConfig
        Dim gpi14 As TDiConfig
        Dim gpi15 As TDiConfig
        Dim gpi16 As TDiConfig
        Dim arrive1 As TDiConfig
        Dim arrive2 As TDiConfig
        Dim arrive3 As TDiConfig
        Dim arrive4 As TDiConfig
        Dim arrive5 As TDiConfig
        Dim arrive6 As TDiConfig
        Dim arrive7 As TDiConfig
        Dim arrive8 As TDiConfig
        Dim mpg1 As TDiConfig
        Dim mpg2 As TDiConfig
        Dim mpg3 As TDiConfig
        Dim mpg4 As TDiConfig
        Dim mpg5 As TDiConfig
        Dim mpg6 As TDiConfig
        Dim mpg7 As TDiConfig
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

    Public Declare Function GT_SetDiConfig Lib "gts.dll" (ByVal diType As Short, ByVal diIndex As Short, ByRef pDi As TDiConfig) As Short
    Public Declare Function GT_GetDiConfig Lib "gts.dll" (ByVal diType As Short, ByVal diIndex As Short, ByRef pDi As TDiConfig) As Short
    Public Declare Function GT_SetDoConfig Lib "gts.dll" (ByVal doType As Short, ByVal doIndex As Short, ByRef pDo As TDoConfig) As Short
    Public Declare Function GT_GetDoConfig Lib "gts.dll" (ByVal doType As Short, ByVal doIndex As Short, ByRef pDo As TDoConfig) As Short
    Public Declare Function GT_SetStepConfig Lib "gts.dll" (ByVal mcStep As Short, ByRef pStep As TStepConfig) As Short
    Public Declare Function GT_GetStepConfig Lib "gts.dll" (ByVal mcStep As Short, ByRef pStep As TStepConfig) As Short
    Public Declare Function GT_SetDacConfig Lib "gts.dll" (ByVal dac As Short, ByRef pDac As TDacConfig) As Short
    Public Declare Function GT_GetDacConfig Lib "gts.dll" (ByVal dac As Short, ByRef pDac As TDacConfig) As Short
    Public Declare Function GT_SetCountConfig Lib "gts.dll" (ByVal countType As Short, ByVal countIndex As Short, ByRef pCount As TCountConfig) As Short
    Public Declare Function GT_GetCountConfig Lib "gts.dll" (ByVal countType As Short, ByVal countIndex As Short, ByRef pCount As TCountConfig) As Short
    Public Declare Function GT_SetControlConfig Lib "gts.dll" (ByVal control As Short, ByRef pControl As TControlConfig) As Short
    Public Declare Function GT_GetControlConfig Lib "gts.dll" (ByVal control As Short, ByRef pControl As TControlConfig) As Short
    Public Declare Function GT_SetProfileConfig Lib "gts.dll" (ByVal profile As Short, ByRef pProfile As TProfileConfig) As Short
    Public Declare Function GT_GetProfileConfig Lib "gts.dll" (ByVal profile As Short, ByRef pProfile As TProfileConfig) As Short
    Public Declare Function GT_SetAxisConfig Lib "gts.dll" (ByVal axis As Short, ByRef pAxis As TAxisConfig) As Short
    Public Declare Function GT_GetAxisConfig Lib "gts.dll" (ByVal axis As Short, ByRef pAxis As TAxisConfig) As Short
    Public Declare Function GT_GetConfigTable Lib "gts.dll" (ByVal type As Short, ByRef pCount As Short) As Short
    Public Declare Function GT_GetConfigTableAll Lib "gts.dll" () As Short

    Public Declare Function GT_SetMcConfig Lib "gts.dll" (ByRef pMc As TMcConfig) As Short
    Public Declare Function GT_GetMcConfig Lib "gts.dll" (ByRef pMc As TMcConfig) As Short

    Public Declare Function GT_SetMcConfigToFile Lib "gts.dll" (ByRef pMc As TMcConfig, ByVal pFile As String) As Short
    Public Declare Function GT_GetMcConfigFromFile Lib "gts.dll" (ByRef pMc As TMcConfig, ByVal pFile As String) As Short

    Public Declare Function GT_SaveConfig Lib "gts.dll" (ByVal pFile As String) As Short

    Public Declare Function GT_GetInterruptTime Lib "gts.dll" (ByRef pServoRunTime As Double, ByRef pProfileRunTime As Double) As Short
    Public Declare Function GT_GetInterruptTimeMax Lib "gts.dll" (ByRef pServoRunTimeMax As Double, ByRef pProfileRunTimeMax As Double) As Short

    'New Watch
    Public Const WATCH_MODE_STATIC As Short = 0
    Public Const WATCH_MODE_LOOP As Short = 1
    Public Const WATCH_MODE_DYNAMIC As Short = 2

    Public Const WATCH_MODE_STATIC_BACKGROUND As Short = 10
    Public Const WATCH_MODE_LOOP_BACKGROUND As Short = 11
    Public Const WATCH_MODE_DYNAMIC_BACKGROUND As Short = 12

    Public Const WATCH_EVENT_RUN As Short = 1
    Public Const WATCH_EVENT_START As Short = 10
    Public Const WATCH_EVENT_STOP As Short = 20
    Public Const WATCH_EVENT_OFF As Short = 30

    Public Const WATCH_CONDITION_EQ As Short = 1
    Public Const WATCH_CONDITION_NE As Short = 2
    Public Const WATCH_CONDITION_GE As Short = 3
    Public Const WATCH_CONDITION_LE As Short = 4

    Public Const WATCH_CONDITION_CHANGE_TO As Short = 11
    Public Const WATCH_CONDITION_CHANGE As Short = 12
    Public Const WATCH_CONDITION_UP As Short = 13
    Public Const WATCH_CONDITION_DOWN As Short = 14

    Public Const WATCH_CONDITION_REMAIN_AT As Short = 21
    Public Const WATCH_CONDITION_REMAIN As Short = 22

    Public Const WATCH_VAR_CLOCK As Integer = 1200
    Public Const WATCH_VAR_PRF_LOOP As Integer = 1201

    Public Const WATCH_VAR_COMMAND_CODE As Integer = 1220
    Public Const WATCH_VAR_COMMAND_DATA As Integer = 1221
    Public Const WATCH_VAR_COMMAND_COUNT As Integer = 1222
    Public Const WATCH_VAR_COMMAND_READ_FLAG As Integer = 1223

    Public Const WATCH_VAR_PRF_POS As Integer = 6000
    Public Const WATCH_VAR_PRF_VEL As Integer = 6001
    Public Const WATCH_VAR_PRF_ACC As Integer = 6002

    Public Const WATCH_VAR_PRF_RUN As Integer = 6200

    Public Const WATCH_VAR_CRD_PRF_POS As Integer = 8000
    Public Const WATCH_VAR_CRD_PRF_VEL As Integer = 8001
    Public Const WATCH_VAR_CRD_PRF_ACC As Integer = 8002

    Public Const WATCH_VAR_CRD_RUN As Integer = 8200

    Public Const WATCH_VAR_CRD_SEGMENT_NUMBER As Integer = 8202
    Public Const WATCH_VAR_CRD_SEGMENT_NUMBER_USER As Integer = 8203
    Public Const WATCH_VAR_CRD_COMMAND_RECEIVE As Integer = 8204
    Public Const WATCH_VAR_CRD_COMMAND_EXECUTE As Integer = 8205

    Public Const WATCH_VAR_SCAN_PRF_POS As Integer = 18000
    Public Const WATCH_VAR_SCAN_PRF_VEL As Integer = 18001
    Public Const WATCH_VAR_SCAN_PRF_ACC As Integer = 18002

    Public Const WATCH_VAR_SCAN_PRF_POS_X As Integer = 18010
    Public Const WATCH_VAR_SCAN_PRF_POS_Y As Integer = 18020

    Public Const WATCH_VAR_SCAN_RUN As Integer = 18200

    Public Const WATCH_VAR_SCAN_SEGMENT_NUMBER As Integer = 18202


    Public Const WATCH_VAR_LASER_HSIO As Integer = 18600
    Public Const WATCH_VAR_LASER_POWER As Integer = 18601

    Public Const WATCH_VAR_AXIS_PRF_POS As Integer = 20000
    Public Const WATCH_VAR_AXIS_PRF_VEL As Integer = 20001
    Public Const WATCH_VAR_AXIS_PRF_ACC As Integer = 20002
    Public Const WATCH_VAR_AXIS_ENC_POS As Integer = 20003

    Public Const WATCH_VAR_ENC_POS As Integer = 30000

    Public Const WATCH_VAR_PULSE_POS As Integer = 30001

    Public Const WATCH_VAR_GPI As Integer = 31000

    Public Const WATCH_VAR_GPO As Integer = 32000

    Public Const WATCH_VAR_AI As Integer = 33000

    Public Const WATCH_VAR_A As Integer = 34000

    Public Const WATCH_VAR_AUTO_FOCUS_OUT As Integer = 34006

    Public Const WATCH_VAR_TRIGGER_STATUS As Integer = 38001

    Public Const WATCH_VAR_POS_LOOP_ERROR As Integer = 40000

    Public Const WATCH_VAR_CONTROL_REF_VEL As Integer = 41000

    Public Const WATCH_VAR_WATCH_TIME As Integer = 52001



    Public Structure TWatchVar
        Dim type As UShort
        Dim index As UShort
        Dim id As UShort
    End Structure

    Public Structure TWatchEvent
        Dim type As UShort
        Dim watchLoop As UShort
        Dim watchCount As UShort
        Dim var As TWatchVar
        Dim condition As UShort
        Dim value As Double
    End Structure

    Public Declare Function GT_ClearWatch Lib "gts.dll" (ByVal mode As Short) As Short
    Public Declare Function GT_AddWatchVar Lib "gts.dll" (ByRef pVar As TWatchVar) As Short
    Public Declare Function GT_AddWatchEvent Lib "gts.dll" (ByRef pEvent As TWatchEvent) As Short
    Public Declare Function GT_WatchOn Lib "gts.dll" (ByVal interval As Short, ByVal mode As Short, ByVal count As Short) As Short
    Public Declare Function GT_WatchOff Lib "gts.dll" () As Short
    Public Declare Function GT_PrintWatch Lib "gts.dll" (ByVal pFileName As String, ByVal start As Integer, ByVal printCount As UInteger) As Short
    Public Declare Function GT_GetMcVar Lib "gts.dll" (ByRef pVar As TWatchVar, ByRef pValue As Double) As Short

    Public Declare Function GT_SetWatchGroup Lib "gts.dll" (ByVal group As Short) As Short
    Public Declare Function GT_GetWatchGroup Lib "gts.dll" (ByRef pGroup As Short) As Short
    Public Declare Function GT_LoadWatchConfig Lib "gts.dll" (ByVal pFile As String) As Short
    Public Declare Function GT_SaveWatchConfig Lib "gts.dll" (ByVal group As Short, ByVal pFile As String) As Short
    Public Declare Function GT_ReadWatch Lib "gts.dll" (ByVal varIndex As Short, ByRef pBuffer As Double, ByVal bufferSize As UInteger, ByRef pReadCount As UInteger) As Short

    Public Structure TWatchInfo
        Dim enable As Short                 '采集使能
        Dim run As Short                            '采集状态
        Dim time As UInteger                    '采集次数
        Dim head As UInteger                    '头指针
        Dim threshold As UInteger           '最多容纳采集次数

        Dim interval As Short                   '采集间隔
        Dim mode As Short                           '采集模式
        Dim countBeforeEvent As UShort  '事件触发之前的采集数量
        Dim countAfterEvent As UShort       '事件触发以后的采集数量
        Dim varCount As UShort          '采集变量数量
        Dim eventCount As UShort            '采集事件数量
    End Structure

    Public Structure TWatchVarInfo
        Dim pAddress As UInteger
        Dim length As UShort
        Dim fraction As Short
        Dim format As UShort
        Dim hex As UShort
        Dim sign As UShort
        Dim bit As UShort
    End Structure

    Public Structure TWatchFormat
        Dim width As Short
        Dim precision As Short
        Dim seperator As Char
        Dim hex As Short
    End Structure

    Public Declare Function GT_GetWatchInfo Lib "gts.dll" (ByRef pInfo As TWatchInfo) As Short
    Public Declare Function GT_GetWatchVar Lib "gts.dll" (ByVal index As Short, ByRef pVar As TWatchVar, ByRef pVarInfo As TWatchVarInfo) As Short
    Public Declare Function GT_GetWatchEvent Lib "gts.dll" (ByVal index As Short, ByRef pEvent As TWatchEvent) As Short
    Public Declare Function GT_SetWatchFormat Lib "gts.dll" (ByRef pFormat As TWatchFormat) As Short
    Public Declare Function GT_GetWatchFormat Lib "gts.dll" (ByRef pFormat As TWatchFormat) As Short
    
    'Event and Task
    Public Const TASK_SET_DO_BIT As Integer = &H1101
    Public Const TASK_CRD_START As Integer = &H4004
    Public Const TASK_CRD_STOP As Integer = &H4005
    Public Const TASK_CRD_OVERRIDE As Integer = &H4006
    
    Public Structure TTaskSetDoBit
        Dim doType As Short
        Dim doIndex As Short
        Dim doValue As Short
        Dim mode As Short
        Dim parameter1 As Integer
        Dim parameter2 As Integer
        Dim parameter3 As Integer
        Dim parameter4 As Integer
        Dim parameter5 As Integer
        Dim parameter6 As Integer
        Dim parameter7 As Integer
        Dim parameter8 As Integer
    End Structure
    
    Public Structure TTaskCrdStart
        Dim mask As Short
        Dim option1 As Short
    End Structure
    
    Public Structure TTaskCrdStop
        Dim mask As Short
        Dim option1 As Short
    End Structure
    
    Public Structure TTaskCrdOverride
        Dim crd As Short
        Dim synVelOverride As Double
    End Structure
    
    Public Structure TEvent
        Dim loop1 As UInteger
        Dim var As TWatchVar
        Dim condition As UShort
        Dim value As Double
    End Structure
    
    Public Declare Function GT_ClearEvent Lib "gts.dll" () As Short
    Public Declare Function GT_ClearTask Lib "gts.dll" () As Short
    Public Declare Function GT_ClearEventTaskLink Lib "gts.dll" () As Short
    Public Declare Function GT_AddEvent Lib "gts.dll" (ByRef pEvent As TEvent, ByVal pEventIndex As Short) As Short
    Public Declare Function GT_AddTask Lib "gts.dll" (ByVal taskType As Short,ByVal pTaskData As Integer, ByRef pTaskIndex As Short) As Short
    Public Declare Function GT_AddEventTaskLink Lib "gts.dll" (ByVal eventIndex As Short, ByVal taskIndex As Short, ByRef pLinkIndex As Short) As Short
    Public Declare Function GT_GetEventCount Lib "gts.dll" (ByRef pCount As Short) As Short
    Public Declare Function GT_GetEvent Lib "gts.dll" (ByVal eventIndex As Short, ByRef pEvent As TEvent) As Short
    Public Declare Function GT_GetEventLoop Lib "gts.dll" (ByVal eventIndex As Short, ByRef pCount As UInteger) As Short
    Public Declare Function GT_GetTaskCount Lib "gts.dll" (ByRef pCount As Short) As Short
    Public Declare Function GT_GetTask Lib "gts.dll" (ByVal taskIndex As Short, ByRef pTaskType As Short, ByVal pTaskData As Integer) As Short
    Public Declare Function GT_GetEventTaskLinkCount Lib "gts.dll" (ByRef pCount As Short) As Short
    Public Declare Function GT_GetEventTaskLink Lib "gts.dll" (ByVal linkIndex As Short, ByRef pEventIndex As Short, ByRef pTaskIndex As Short) As Short
    Public Declare Function GT_EventOn Lib "gts.dll" (ByVal eventIndex As Short, ByVal count As Short) As Short
    Public Declare Function GT_EventOff Lib "gts.dll" (ByVal eventIndex As Short, ByVal count As Short) As Short
    Public Declare Function GT_BufEventOn Lib "gts.dll" (ByVal crd As Short, ByVal eventIndex As Short, ByVal count As Short, ByVal fifo As Short) As Short
    Public Declare Function GT_BufEventOff Lib "gts.dll" (ByVal crd As Short, ByVal eventIndex As Short, ByVal count As Short, ByVal fifo As Short) As Short
    
    Public Const VAR_CALCULATE_NONE As Integer = 0
    Public Const VAR_CALCULATE_OR As Integer = 1
    Public Const VAR_CALCULATE_AND As Integer = 3
    Public Const VAR_CALCULATE_NOT As Integer = 5
    
    Public Const VAR_CALCULATE_ADD As Integer = 11
    Public Const VAR_CALCULATE_SUB As Integer = 12
    Public Const VAR_CALCULATE_MUL As Integer = 13
    Public Const VAR_CALCULATE_DIV As Integer = 14
    
    Public Structure TWatchCondition
        Dim var As TWatchVar
        Dim condition As UShort
        Dim value As Double
    End Structure
    
    Public Structure TVarCalculate
        Dim operation As UShort
        Dim varType As UShort
        Dim result As UShort
        Dim lhs As UShort
        Dim rhs As UShort
    End Structure
    
    Public Declare Function GT_ClearVar Lib "gts.dll" () As Short
    Public Declare Function GT_SetVarBoolCondition Lib "gts.dll" (ByVal varIndex As Short, ByRef pWatchCondition As TWatchCondition) As Short
    Public Declare Function GT_GetVarBoolCondition Lib "gts.dll" (ByVal lvarIndex As Short, ByRef pWatchCondition As TWatchCondition) As Short
    Public Declare Function GT_AddVarCalculate Lib "gts.dll" (ByRef pVarCalculate As TVarCalculate, ByRef pIndex As Short) As Short
    Public Declare Function GT_GetVarCalculateCount Lib "gts.dll" (ByRef pCount As Short) As Short
    Public Declare Function GT_GetVarCalculate Lib "gts.dll" (ByVal index As Short, ByRef pVarCalculate As TVarCalculate) As Short

End Module