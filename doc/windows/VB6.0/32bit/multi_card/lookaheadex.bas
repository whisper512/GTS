Attribute VB_Name = "gts_la"
    Public Const LA_AXIS_NUM As Integer = 8
    Public Const LA_WORK_AXIS_NUM As Integer = 6
    Public Const LA_MACHINE_AXIS_NUM As Integer = 5

    Public Const AXIS_LIMIT_NONE As Integer = 0
    Public Const AXIS_LIMIT_MAX_VEL As Integer = 1
    Public Const DAXIS_LIMIT_MAX_ACC As Integer = 2
    Public Const AXIS_LIMIT_MAX_DV As Integer = 4
    Public Const KIN_MSG_BUFFER_SIZE As Integer = 32

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
    Public Type TLookAheadParameter
         lookAheadNum As Long                      '前瞻段数
         dumb1 As Integer
         dumb2 As Integer
         time As Double                          '时间常数
         radiusRatio As Double                   '曲率限制调节参数
         vMax1 As Double                        '各轴的最大速度
         vMax2 As Double
         vMax3 As Double
         vMax4 As Double
         vMax5 As Double
         vMax6 As Double
         vMax7 As Double
         vMax8 As Double
         aMax1 As Double                        '各轴的最大加速度
         aMax2 As Double
         aMax3 As Double
         aMax4 As Double
         aMax5 As Double
         aMax6 As Double
         aMax7 As Double
         aMax8 As Double
         DVMax1 As Double                       '各轴的最大速度变化量（在时间常数内）
         DVMax2 As Double
         DVMax3 As Double
         DVMax4 As Double
         DVMax5 As Double
         DVMax6 As Double
         DVMax7 As Double
         DVMax8 As Double
         scale1 As Double                       '各轴的脉冲当量
         scale2 As Double
         scale3 As Double
         scale4 As Double
         scale5 As Double
         scale6 As Double
         scale7 As Double
         scale8 As Double
         axisRelation1 As Integer                 '输入坐标和内部坐标的对应关系
         axisRelation2 As Integer
         axisRelation3 As Integer
         axisRelation4 As Integer
         axisRelation5 As Integer
         axisRelation6 As Integer
         axisRelation7 As Integer
         axisRelation8 As Integer
         machineCfgFileName As String            '机床配置文件名
         dumb3 As Integer
         dumb4 As Integer
    End Type
    
        Public Type RC_KIN_CONFIG
         RobotType As Integer
         reserved1 As Integer

         KinParUse1 As Integer
         KinParUse2 As Integer
         KinParUse3 As Integer
         KinParUse4 As Integer
         KinParUse5 As Integer
         KinParUse6 As Integer
         KinParUse7 As Integer
         KinParUse8 As Integer
         KinParUse9 As Integer
         KinParUse10 As Integer
         KinParUse11 As Integer
         KinParUse12 As Integer
         KinParUse13 As Integer
         KinParUse14 As Integer
         KinParUse15 As Integer
         KinParUse16 As Integer
         KinParUse17 As Integer
         KinParUse18 As Integer

         KinPar1 As Double
         KinPar2 As Double
         KinPar3 As Double
         KinPar4 As Double
         KinPar5 As Double
         KinPar6 As Double
         KinPar7 As Double
         KinPar8 As Double
         KinPar9 As Double
         KinPar10 As Double
         KinPar11 As Double
         KinPar12 As Double
         KinPar13 As Double
         KinPar14 As Double
         KinPar15 As Double
         KinPar16 As Double
         KinPar17 As Double
         KinPar18 As Double

         KinLimitUse1 As Integer
         KinLimitUse2 As Integer
         KinLimitUse3 As Integer
         KinLimitUse4 As Integer
         KinLimitUse5 As Integer
         KinLimitUse6 As Integer
         KinLimitUse7 As Integer
         KinLimitUse8 As Integer
         KinLimitUse9 As Integer
         KinLimitUse10 As Integer
         KinLimitUse11 As Integer
         KinLimitUse12 As Integer

         KinLimitMin1 As Double
         KinLimitMin2 As Double
         KinLimitMin3 As Double
         KinLimitMin4 As Double
         KinLimitMin5 As Double
         KinLimitMin6 As Double
         KinLimitMin7 As Double
         KinLimitMin8 As Double
         KinLimitMin9 As Double
         KinLimitMin10 As Double
         KinLimitMin11 As Double
         KinLimitMin12 As Double

         KinLimitMax1 As Double
         KinLimitMax2 As Double
         KinLimitMax3 As Double
         KinLimitMax4 As Double
         KinLimitMax5 As Double
         KinLimitMax6 As Double
         KinLimitMax7 As Double
         KinLimitMax8 As Double
         KinLimitMax9 As Double
         KinLimitMax10 As Double
         KinLimitMax11 As Double
         KinLimitMax12 As Double

         KinLimitMinShift1 As Double
         KinLimitMinShift2 As Double
         KinLimitMinShift3 As Double
         KinLimitMinShift4 As Double
         KinLimitMinShift5 As Double
         KinLimitMinShift6 As Double
         KinLimitMinShift7 As Double
         KinLimitMinShift8 As Double
         KinLimitMinShift9 As Double
         KinLimitMinShift10 As Double
         KinLimitMinShift11 As Double
         KinLimitMinShift12 As Double

         KinLimitMaxShift1 As Double
         KinLimitMaxShift2 As Double
         KinLimitMaxShift3 As Double
         KinLimitMaxShift4 As Double
         KinLimitMaxShift5 As Double
         KinLimitMaxShift6 As Double
         KinLimitMaxShift7 As Double
         KinLimitMaxShift8 As Double
         KinLimitMaxShift9 As Double
         KinLimitMaxShift10 As Double
         KinLimitMaxShift11 As Double
         KinLimitMaxShift12 As Double

         AxisUse1 As Integer
         AxisUse2 As Integer
         AxisUse3 As Integer
         AxisUse4 As Integer
         AxisUse5 As Integer
         AxisUse6 As Integer
         AxisUse7 As Integer
         AxisUse8 As Integer

         AxisPosSignSwitch As String

         AxisPosOffset1 As Double
         AxisPosOffset2 As Double
         AxisPosOffset3 As Double
         AxisPosOffset4 As Double
         AxisPosOffset5 As Double
         AxisPosOffset6 As Double
         AxisPosOffset7 As Double
         AxisPosOffset8 As Double

         CartUnitUse1 As Integer
         CartUnitUse2 As Integer
         CartUnitUse3 As Integer
         CartUnitUse4 As Integer
         CartUnitUse5 As Integer
         CartUnitUse6 As Integer
         CartPosKCSSignSwitch As String
         reserved21 As Integer
         reserved22 As Integer
         reserved23 As Integer
         CartPosKCSOffset1 As Double
         CartPosKCSOffset2 As Double
         CartPosKCSOffset3 As Double
         CartPosKCSOffset4 As Double
         CartPosKCSOffset5 As Double
         CartPosKCSOffset6 As Double
    End Type
    
    Public Type RC_ERROR_INTERFACE
    		 error1 As Byte
         errorID As Integer
         Message As String
    End Type
    
    Public Type RC_MSG_BUFFER_ELEMENT
         errorID As Integer
         Message As String
         LogTime As String
         InternalID As Long
    End Type
    
    Public Type RC_MSG_BUFFER
         LastMsgIndex As Integer
         MsgElement1 As RC_MSG_BUFFER_ELEMENT
         MsgElement2 As RC_MSG_BUFFER_ELEMENT
         MsgElement3 As RC_MSG_BUFFER_ELEMENT
         MsgElement4 As RC_MSG_BUFFER_ELEMENT
         MsgElement5 As RC_MSG_BUFFER_ELEMENT
         MsgElement6 As RC_MSG_BUFFER_ELEMENT
         MsgElement7 As RC_MSG_BUFFER_ELEMENT
         MsgElement8 As RC_MSG_BUFFER_ELEMENT
         MsgElement9 As RC_MSG_BUFFER_ELEMENT
         MsgElement10 As RC_MSG_BUFFER_ELEMENT
         MsgElement11 As RC_MSG_BUFFER_ELEMENT
         MsgElement12 As RC_MSG_BUFFER_ELEMENT
         MsgElement13 As RC_MSG_BUFFER_ELEMENT
         MsgElement14 As RC_MSG_BUFFER_ELEMENT
         MsgElement15 As RC_MSG_BUFFER_ELEMENT
         MsgElement16 As RC_MSG_BUFFER_ELEMENT
         MsgElement17 As RC_MSG_BUFFER_ELEMENT
         MsgElement18 As RC_MSG_BUFFER_ELEMENT
         MsgElement19 As RC_MSG_BUFFER_ELEMENT
         MsgElement20 As RC_MSG_BUFFER_ELEMENT
         MsgElement21 As RC_MSG_BUFFER_ELEMENT
         MsgElement22 As RC_MSG_BUFFER_ELEMENT
         MsgElement23 As RC_MSG_BUFFER_ELEMENT
         MsgElement24 As RC_MSG_BUFFER_ELEMENT
         MsgElement25 As RC_MSG_BUFFER_ELEMENT
         MsgElement26 As RC_MSG_BUFFER_ELEMENT
         MsgElement27 As RC_MSG_BUFFER_ELEMENT
         MsgElement28 As RC_MSG_BUFFER_ELEMENT
         MsgElement29 As RC_MSG_BUFFER_ELEMENT
         MsgElement30 As RC_MSG_BUFFER_ELEMENT
         MsgElement31 As RC_MSG_BUFFER_ELEMENT
         MsgElement32 As RC_MSG_BUFFER_ELEMENT

         LastMsgID As Long
    End Type
    
    '旋转轴范围设置
    Public Type TRotationAxisRange
         primaryAxisRangeOn As Long              '//第一旋转轴限定范围是否生效，0：不生效，1：生效
         slaveAxisRangeOn As Long                '//第二旋转轴限定范围是否生效，0：不生效，1：生效
         maxPrimaryAngle As Double              '//第一旋转轴最大值
         minPrimaryAngle As Double              '//第一旋转轴最小值
         maxSlaveAngle As Double                '//第二旋转轴最大值
         minSlaveAgnle As Double                '//第二旋转轴最小值
    End Type
    
    '选解参数
    Public Enum EGroupSelect
        Continuous = 0
        Group_1
        Group_2
    End Enum
    
    Public Type TPos
         machinePos1 As Double
         machinePos2 As Double
         machinePos3 As Double
         machinePos4 As Double
         machinePos5 As Double
         workPos1 As Double
         workPos2 As Double
         workPos3 As Double
         workPos4 As Double
         workPos5 As Double
         workPos6 As Double
    End Type
    
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
    
    Public Enum optimizeMethod
        NO_OPT
        OPT_BLENDING
        OPT_CIRCLEFITTING
        OPT_CUBICSPLINE
        OPT_BSPLINE
    End Enum
    
    Public Enum errorID
        INIT_ERROR = 1                          '没有进行参数初始化
        PASSWORD_ERROR                          '密码错误，请在固高运动控制平台上运行
        INDATA_ERROR                            '输入数据错误（检查圆弧数据是否正确）
        PRE_PROCESS_ERROR
        TOOL_RADIUS_COMPENSATE_ERROR_INOUT      '刀具半径补偿错误：进入/结束刀补处不能是圆弧
        TOOL_RADIUS_COMPENSATE_ERROR_NOCROSS    '刀具半径补偿错误：数据不合理，无法计算交点
        USERDATA_ERROR
    End Enum

    Public Type TOptimizeParamUser
         usePathOptimize As OptimizeState    '是否使用路径优化：OPT_OFF:不使用       OPT_ON:使用

         tolerance As Double             '公差(suggest: rough:0.1, pre-finish:0.05, finish:0.01)

         optimizeMethod As optimizeMethod   '选择曲线优化方式

         keepLargeArc As OptimizeState      '是否保留大圆弧：OPT_OFF：不保留， OPT_ON：保留

         blendingMinError As Double          'blending的最小设定误差

         blendingMaxAngle As Double           'blending的最大角度限制（即当线段向量角度大于该角度时，不做blending，单位：度）

    End Type

    Public Type TErrorInfo
         errorID As errorID
         errorRowNum As Long
    End Type
    
    Public Type TPreStartPos
         Pos1 As Double
         Pos2 As Double
         Pos3 As Double
         Pos4 As Double
         Pos5 As Double
         Pos6 As Double
         Pos7 As Double
         Pos8 As Double
    End Type

		Public Type TBufIoDelayData
			doType As Integer
			doMask As Integer
			doValue As Integer
			delayTime As Integer
			fifo As Integer
		End Type
		
		Public Type TBufDoBitPulseData
			doType As Integer
			doIndex As Integer
			highLevelTime As Integer
			lowLevelTime As Integer
			pulseNum As Long
			firstLevel As Integer
			fifo As Integer
		End Type
		
		Public Type TBufDaData
			channel As Integer
			daValue As Integer
			fifo As Integer
		End Type
		
		Public Type TBufLaserData
			channel As Integer
			fifo As Integer
			source As Integer
			laserPower As Double
			ratio As Double
			minPower As Double
			maxPower As Double
			tableId As Integer
		End Type
		
		Public Type TBufGearData
			axis As Integer
			deltaPos As Double
			fifo As Integer
			smoothFlag As Integer
			accPercent As Integer
			decPercent As Integer
		End Type
		
		Public Type TBufMoveData
			axis As Integer
			pos As Double
			vel As Double
			acc As Double
			modal As Integer
			fifo As Integer
		End Type
		
		Public Type TBufSegNumData
			segNum As Long 
			fifo As Integer
		End Type

    Public Declare Function GT_SetupLookAheadCrd Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal machineMode As EMachineMode) As Integer
    Public Declare Function GT_SetFollowAxisParaLa Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pAxisLimitMode As Integer, ByRef pVmax As Double, ByRef pAmax As Double, ByRef pDVmax As Double) As Integer
    Public Declare Function GT_SetVelDefineModeLa Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef velDefMode As EVelSettingDef) As Integer
    Public Declare Function GT_SetAxisLimitModeLa Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pAxisLimitMode As Long) As Integer
    Public Declare Function GT_SetWorkLimitModeLa Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef workLimitMode As EWorkLimitMode) As Integer
    Public Declare Function GT_SetAxisVelValidModeLa Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal velValidAxis As Long) As Integer
    Public Declare Function GT_SetVelSmoothMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal smoothMode As Long) As Integer
    Public Declare Function GT_SetArcAllowErrorLa Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal error as double)  As Integer
    Public Declare Function GT_InitLookAheadEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pLookAheadPara As TLookAheadParameter, ByVal fifo As Integer, ByVal motionMode As Integer, ByVal pPreStartPos As Long) As Integer
    Public Declare Function GT_PrintLACmdLa Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal printFlag as Long, ByVal clearFile As Long)  As Integer
    Public Declare Function GT_InitLookAheadPara Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal lookAheadNum As Long, ByVal time As Double, ByVal radiusRatio As Double, ByVal scale As Double, ByVal fifo As Integer) As Integer
    
    Public Declare Function GT_LnXYEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_LnXYG0Ex Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_LnXYZEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_LnXYZG0Ex Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_LnXYZAEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_LnXYZAG0Ex Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_LnXYZACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pPos As Double, ByVal posMask As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_LnXYZACG0Ex Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pPos As Double, ByVal posMask As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer

    Public Declare Function GT_LnXYZACUVWEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pPos As Double, ByVal posMask As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_LnXYZACUVWG0Ex Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pPos As Double, ByVal posMask As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer

    Public Declare Function GT_ArcXYREx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_ArcYZREx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Double, ByVal z As Double, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_ArcZXREx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Double, ByVal x As Double, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_ArcXYCEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal xCenter As Double, ByVal yCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_ArcYZCEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Double, ByVal z As Double, ByVal yCenter As Double, ByVal zCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_ArcZXCEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Double, ByVal x As Double, ByVal zCenter As Double, ByVal xCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_ArcXYZEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal interX As Double, ByVal interY As Double, ByVal interZ As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_HelixXYRZEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_HelixXYCZEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal xCenter As Double, ByVal yCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_BufDelayEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal delayTime As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_BufGearEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal gearAxis As Integer, ByVal deltaPos As Double, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_BufMoveEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal moveAxis As Integer, ByVal pos As Double, ByVal vel As Double, ByVal acc As Long, ByVal modal As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_BufIOEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal doType As Integer, ByVal doMask As Integer, ByVal doValue As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_BufDAEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal chn As Integer, ByVal daValue As Integer, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_SetUserSegNumEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal segNum As Long, Optional ByVal fifo As Integer = 0) As Integer

    'Add By lin.ga 20150330
    Public Declare Function GT_BufLaserOnEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
    Public Declare Function GT_BufLaserOffEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
    Public Declare Function GT_BufLaserPrfCmdEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal laserPower As Double, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
    Public Declare Function GT_BufLaserFollowRatioEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal ratio As Double, ByVal minPower As Double, ByVal maxPower As Double, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
    Public Declare Function GT_BufLaserFollowModeEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal source As Integer = 0, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
    Public Declare Function GT_BufLaserFollowSplineEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal tableId As Integer, ByVal minPower As Double, ByVal maxPower As Double, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer
    Public Declare Function GT_BufLaserFollowOffEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal fifo As Integer = 0, Optional ByVal channel As Integer = 0) As Integer

    Public Declare Function GT_BufDisableDoBitPulseEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal doType As Integer, ByVal doIndex As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_BufEnableDoBitPulseEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal doType As Integer, ByVal doIndex As Integer, ByVal highLevelTime As Integer, ByVal lowLevelTime As Integer, ByVal pulseNum As Long, ByVal firstLevel As Integer, ByVal fifo As Integer) As Integer

    Public Declare Function GT_CrdDataEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pCrdData As Long, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_CrdDataExEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pCrdData As Long, Optional ByVal fifo As Integer = 0) As Integer
    Public Declare Function GT_GetLookAheadSegCountEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pSegCount As Long, Optional ByVal fifo As Integer = 0) As Integer

    Public Declare Function GT_GetMotionTimeEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pTime As Double, ByVal fifo As Integer) As Integer
    
    Public Declare Function GT_SetPathOptPara Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef optPrm As TOptimizeParamUser, ByVal fifo As Integer) As Integer
    Public Declare Function GT_GetPathOptErrorInfo Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef errorInfo As TErrorInfo, ByVal fifo As Integer) As Integer
    
    '5AXIS
    Public Declare Function GT_CrdRTCPOn Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal crd As Integer = 0) As Integer
    Public Declare Function GT_CrdRTCPOff Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, Optional ByVal crd As Integer = 0) As Integer
    Public Declare Function GT_UpdateMachineBuildingFile Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal update As Long) As Integer
    Public Declare Function GT_InitialMachineBuilding Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pMachineCfgFileName As String, ByRef machineCoordCenter As Double, ByRef workCoordCenter As Double, ByVal toolLength As Double) As Integer
    Public Declare Function GT_SetRotationAxisRange Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pRotationAxisRange As TRotationAxisRange) As Integer
    Public Declare Function GT_SetInverseSolutionSelectPara Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal groupSelect As EGroupSelect, ByVal priorAxisSet As Long) As Integer
    Public Declare Function GT_MachineForwardTrans Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pMachinePos As Double, ByRef pWorkPos As Double) As Integer
    Public Declare Function GT_MachineRTCPTrans Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pInputPos As Double, ByRef pMachinePos As Double, ByRef pWorkPos As Double) As Integer
    Public Declare Function GT_MachineTransformation Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal posType As Long, ByRef pPrePos As Double, ByRef pPos As Double, ByRef pPosNum As Long, ByRef pReturnPos As TPos) As Integer
    Public Declare Function GT_SetCompToolLength Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal compToolLength As Double) As Integer
    Public Declare Function GT_SetCompWorkCoordOffset Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByRef pCompWorkOffset As Double) As Integer
    Public Declare Function GT_SetNonlinearErrorControl Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal enable As Long, ByVal nonlinearError As Double) As Integer
    Public Declare Function GT_EnableDiscreateArc Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal enable As Integer, ByVal arcError As Double) As Integer
    Public Declare Function GT_StartXYCMachineMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal dir As Integer, ByVal contactAngle As Double, ByVal rotationAngle As Double, ByRef pTranslation As Double, ByVal aValue As Double, ByVal fifo As Integer) As Integer
    Public Declare Function GT_EndXYCMachineMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_SetWorkCrdPlane Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal enable As Integer, ByRef pNormVector As Double, ByRef pPoint As Double, ByVal fifo As Integer) As Integer
    Public Declare Function GT_SetStartPointProcessMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal enable As Integer, ByVal z As Double, ByVal fifo As Integer) As Integer
    Public Declare Function GT_InitialMachineBuildingEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal pMachineCfgFileName As String, ByRef machineCoordCenter As Double, ByRef workCoordCenter As Double, ByVal toolLength As Double) As Integer
    Public Declare Function GT_SetWorkCrdLaserFollowMode Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal enbale As Integer, ByVal fifo As Integer, ByVal chn As Integer) As Integer
    Public Declare Function GT_ArcXYRACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal a As Double, ByVal c As Double, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_ArcXYCACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal a As Double, ByVal c As Double, ByVal xCenter As Double, ByVal yCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_ArcXYZACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal x As Double, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal c As Double, ByVal interX As Double,ByVal interY As Double, ByVal interZ As Double, ByVal interA As Double, ByVal interC As Double, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_ArcYZRACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal c As Double, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_ArcYZCACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal y As Double, ByVal z As Double, ByVal a As Double, ByVal c As Double, ByVal yCenter As Double, ByVal zCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_ArcZXRACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Double, ByVal x As Double, ByVal a As Double, ByVal c As Double, ByVal radius As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer
    Public Declare Function GT_ArcZXCACEx Lib "gts.dll" (ByVal cardNum As Integer,ByVal crd As Integer, ByVal z As Double, ByVal x As Double, ByVal a As Double, ByVal c As Double, ByVal zCenter As Double, ByVal xCenter As Double, ByVal circleDir As Integer, ByVal synVel As Double, ByVal synAcc As Double, ByVal segNum As Long, ByVal override2 As Integer, ByVal fifo As Integer) As Integer

