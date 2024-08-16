#ifndef __TS_H__
#define __TS_H__

typedef struct point
{
    int x; // 点击“点”的x轴坐标
    int y; // 点击“点”的y轴坐标

} ts_point;

// “滑动方向”
typedef enum
{
    MOVE_UP = 1, // 向上滑动
    MOVE_DOWN,   // 向下滑动
    MOVE_LEFT,   // 向左滑动
    MOVE_RIGHT,  // 向右滑动

    MOVE_UNKNOWN = 100
} move_dir_t;

int get_touch();

void get_ts_point(ts_point *p);

move_dir_t get_ts_direction(void);

#endif