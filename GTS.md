# GTS400 简单轴控类封装

- [x] 完成HAL抽象层
- [x] lib改为相对位置
- [ ] 样式表改造界面

# 板卡界面

# 总控界面

- [x] 界面本身
- [x] 添加实现
- [x] 添加轴四，改其他轴为轴数，不显示xyz
- [x] 整数据结构，读取当量 — 注意：gts的 GT_SetProfileScale 及下面的三个当量函数无法正常调用
- [x] 实际距离转换
- [x] 获取编码器位置
- [x] 回零

# 轴界面

- [x] 轴状态刷新
- [x] 点位运动 trap
- [x] jog 运动
- [x] trap 运动无法运动，combox 切换过去也无法运动
- [x] 一个轴点位运动和 jog 只有存在一种，只能读取到一个数据，改运动参数已程序结构体为主
- [x] 只有在点位运动下才能获取到运动速度，jog 获取不到
- [x] jog 运动应该是按着按钮运动，松开停止
- [x] 加编码器位置，速度，加速度
- [x] 使能有问题 — 等待没有伺服器的问题，mct 配套软件也使能失败

# IO

- [x] IO 界面
- [x] 表格状态不明显
- [x] 配置界面编码器当量好像无法读取

# 编码器

- [x] 编码器界面
- [ ] 三菱驱动器编码器没有回馈数据，检查驱动和接线等
- [ ] 闭环编码器读取和当量换算
- [ ] 闭环回零方式

# 设置

- [x] 设置界面
- [x] 设置的数据结构准备和界面事件预备
- [x] 界面重置，根据编程手册重改设置项
- [x] 实现功能
- [x] 改为只设置能读取当前值的功能
- [x] 从 total 整理配置的相关函数
- [x] IO 配置 — 输出出入功能配置表
- [x] 轴的软限位，回零参数设置
- [x] 当量设置有问题
- [x] 速度/加速度等有问题
- [x] 同步到主控
- [x] 参数的加载不应该依赖开卡
- [x] 加速度的显示还是有问题 — mct 也是这样，但是速度是正常的
- [x] 回零修改和测试
- [x] 如果设置编码器来源为脉冲计数源是不是也可以读取到编码器数据
- [x] 当量计算函数
- [ ] 界面因为数据变化而变化，需要占位固定
- [x] 单位同步
- [ ] 主控同步修改

# 其他

- [x] 完成两个 widget，一个是简单轴控 widget，一个是复杂的插补 widget
- [ ] 需要一个管理编码器分辨率，当量，丝杆导程等的函数
- [ ] 单位现在是 mm/ms，要不要改为 mm/s 呢，只处理速度？
- [x] 关闭软件有溢出问题

# 集成审查问题 (2026-07-02) — GTSSimpleController 点位运动 / JOG 运动

## P0 — 阻断集成

- [x] 耦合在 Manager 层 — MotionMgr::startTrapMotion / startJogMotion 中弹出错误对话框，headless/GUI-less 场景无法使用。方案：emit errorOccurred(int axisId, QString msg) 信号，由上层决定如何处理。(2026-07-03 已修复，移除 QMessageBox 依赖)
- [ ] 循环 Trap 忙轮询阻塞主线程 — MotionMgr::MotionTrapExecute 中 for + processEvents 忙等，无取消/超时机制。方案：改为 QTimer 异步轮询 + 超时保护 + 取消标志。
- [ ] MotionMgr 强依赖 CTotalMgr — MotionMgr 通过 m_pTotalMgr 获取轴参数，无法脱离 CTotalMgr 单独复用。方案：抽象轴参数接口 IAxisParamProvider，或改为直接注入参数。

## P1 — 建议修复

- [ ] 全局 typo — ControllerData.h / AxisWidget.h 等文件中 `somoothTime` 应为 `smoothTime`。
- [ ] 线程安全缺失 — AxisWidget 直接读写共享运动状态，无互斥保护，多线程场景下有竞态风险。
- [ ] 缺少日志系统 — 运动失败时仅弹窗或静默，无持久化日志，排查问题困难。
- [ ] GTSSimpleController 和 GTSAdvancedController 结构不一致 — 两个模块文件组织方式差异大，后续维护成本高。



# GTS400 复杂插补类封装
