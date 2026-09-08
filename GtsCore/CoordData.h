#pragma once
#include <vector>

// ============================================================
// CoordData — 插补段数据结构
// 描述单段运动指令，多段按顺序组成一条完整路径
// ============================================================

// 段类型
enum class SegmentType : short
{
    Line = 0,       // G01 直线插补
    Arc  = 1,       // G02/G03 圆弧插补
};

// 圆弧方向
enum class ArcDir : short
{
    CW  = 0,        // 顺时针 G02
    CCW = 1,        // 逆时针 G03
};

// 单段插补数据
struct CoordSegment
{
    SegmentType type = SegmentType::Line;   // 段类型
    double      x    = 0.0;                // 终点 X mm (绝对坐标)
    double      y    = 0.0;                // 终点 Y mm (绝对坐标)
    double      z    = 0.0;                // 终点 Z mm (绝对坐标)
    double      f    = 200.0;              // 进给速度 mm/s
    double      accel = 200.0;             // 加速度 mm/s²
    double      velEnd = 0.0;              // 结束速度 mm/s (0=匀速到终点)
    double      r    = 0.0;                // 半径 mm (仅 Arc 有效, Line 时为 0)
    ArcDir      dir  = ArcDir::CW;         // 圆弧方向 (仅 Arc 有效)
};

// 插补表,段数组
using CoordTable = std::vector<CoordSegment>;
