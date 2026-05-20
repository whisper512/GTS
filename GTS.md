#GTS400系类封装

##完成HAL抽象层 √
##lib改为相对位置


BoardMgr			~25	板卡级别操作
AxisMgr				~30	每根轴的状态控制
MotionMgr			~55	所有单轴运动模式
InterpolationMgr	~35	多轴插补
IOMgr				~30	IO + 模拟量 + 扩展模块
FeedbackMgr			~30	编码器 + 捕获 + 回零
ConfigMgr 所有高级配置功能


┌─────────────────────────────────────────────┐
│  GTSWidget (QWidget)                         │
│  ├── QStackedWidget                          │
│  ├── AxisPanel      → m_mgr->axis()          │
│  ├── MotionPanel    → m_mgr->motion()        │
│  ├── IOPanel        → m_mgr->io()            │
│  ├── FeedbackPanel  → m_mgr->feedback()      │
│  ├── InterpPanel    → m_mgr->interpolation() │
│  └── ConfigPanel    → m_mgr->config()        │
├─────────────────────────────────────────────┤
│  TotalManager                                │
│  ├── board()  → BoardMgr*                │
│  ├── axis()   → AxisMgr*                 │
│  ├── motion() → MotionMgr*               │
│  ├── interpolation() → InterpolationMgr* │
│  ├── io()     → IOMgr*                   │
│  ├── feedback() → FeedbackMgr*           │
│  └── config() → ConfigMgr*               │
├─────────────────────────────────────────────┤
│  GtsHal (静态转发层，保留不变)                 │
├─────────────────────────────────────────────┤
│  gts.dll                                     │
└─────────────────────────────────────────────┘
