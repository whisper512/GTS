# GTSController 项目长期记忆

## 项目约定
- 使用 GTS.md 管理所有任务和问题，统一 `- [ ]` / `- [x]` checkbox 格式
- 项目基于固高 GTS-400 运动控制卡，HAL 抽象层已封装
- **C++ 注释只用英文标点** — `//` 注释中的括号、逗号、问号一律用英文 (`()` `,` `?`)，禁止全角 (`（）` `，` `？`)，否则缩进对齐会错位
- **源文件编码**: 项目 .vcxproj 无 /utf-8 选项, MSVC 对无 BOM 文件按 GBK 解读。含中文的源文件必须是 **UTF-8+BOM** 或 **GBK**, 不能是 UTF-8 无 BOM。Edit 工具修改 GBK 文件会转为 UTF-8 无 BOM, 需手动用 Python 补 BOM 或转码。

## 用户偏好

### 代码修改规则（最高优先级）
- **任何代码文件的修改，必须先以文字形式给出修改内容和变动清单，等用户确认后才能动手改文件。**
- 这一点适用于所有 .cpp、.h、.vcxproj 等源代码/配置文件。
- GTS.md 这类纯文档文件不受此限制。

### 输出偏好
- 不要生成 HTML 报告文件，用户自己会检查代码结果
- 审查 / 分析结论直接在对话中用文字和表格给出即可

## 架构决策
- **Mgr 拆分原则**: 功能有独立数据流/生命周期/可独立测就独立成 mgr，否则集成到现有 mgr
- **模块归属(按功能域)**: 高速IO+触发→HighSpeedIOMgr(新建)、PID+滤波+补偿→ControlMgr(新建)、龙门→GantryMgr(新建)、坐标变换→CoordMgr、手轮→AxisMgr(暂缓)
- **功能域划分**: 运动域(MotionMgr)/插补域(CoordMgr+Engine)/IO域(IOMgr+HSIO)/控制调优域(ControlMgr)/结构域(GantryMgr)/反馈域(FeedbackMgr)/配置域(ConfigMgr)
- **ConfigMgr 定位**: 只做参数读写和持久化，不再当"垃圾桶"，高级功能迁到对应 mgr
- **插补引擎**: CoordEngine 归 GtsMgr 管理(unique_ptr)，与 UI 解耦，直接读 CoordCfg 配置(单一数据源)
