# GTS400封装

- [x] 完成HAL抽象层
- [x] lib改为相对位置
- [ ] 样式表QssStylesheetEditor

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

# 插补
- [x] ui和基础数据结构
- [x] 实时绘制和数据添加修改等
- [x] 绘制
- [x] 仿真
- [x] 插补模式，一次行多条指令或动态加载执行
- [x] 模拟模式按 长度/速度 计算段执行时长
- [x] 插补配置(静态/动态模式 + 模拟开关)持久化到 gtsConfig.json
- [ ] 单位转换 — executeSegment 里 mm 转 pulse
- [ ] 加速度字段 — CoordSegment 加独立 accel，不再复用 f 当加速度
- [ ] 圆弧平面路由 — 引擎支持 YZ/ZX 圆弧
- [ ] 实时位置反馈 — 执行中读 getCrdPosition

# IO

- [x] IO 界面
- [x] 表格状态不明显
- [x] 配置界面编码器当量好像无法读取
- [x] GPI 电平极性设置

# 编码器

- [x] 编码器界面
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
- [x] 单位同步

# 其他

- [x] 完成两个 widget，一个是简单轴控 widget，一个是复杂的插补 widget
- [ ] 需要一个管理编码器分辨率，当量，丝杆导程等的函数
- [x] 关闭软件有溢出问题
- [ ] 添加同步trap方法,未测试
- [x] 修改为gstcore的管理类
- [x] 耦合在 Manager 层 — MotionMgr::startTrapMotion / startJogMotion 中弹出错误对话框，headless/GUI-less 场景无法使用。方案：emit errorOccurred(int axisId, QString msg) 信号，由上层决定如何处理。(2026-07-03 已修复，移除 QMessageBox 依赖)
- [x] 循环 Trap 忙轮询阻塞主线程 — MotionMgr::startTrapMotion 中 for + processEvents 忙等，无取消/超时机制。方案：onTrapCycleStep 递归自调度（waitMotionDone + QMetaObject::invokeMethod Qt::QueuedConnection）+ cancelTrapCycle。(2026-07-03 已修复)

