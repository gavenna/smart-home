#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "ts.h"

// 触摸屏函数,可以判断手指是否点击了指定的位置
int get_touch()
{
    // 打开触摸屏
    int fd_touch = open("/dev/input/event0", O_RDWR);
    if (fd_touch == -1)
    {
        printf("open event0 error!\n");
        return -1;
    }
    // 定义一个结构体,保存读取到的输入信息
    struct input_event ev;
    int x, y;
    while (1)
    {

        int ret = read(fd_touch, &ev, sizeof(ev));
        if (ret != sizeof(ev))
        {
            continue;
        }
        // 解析输入事件
        if (ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value; // 记录得到的x坐标
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value; // 记录得到的y坐标
        }
        // 当手指离开触摸屏的时候结束
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            break;
        }
    }
    // 关闭触摸屏
    close(fd_touch);

    // 得到坐标
    x = x / 1.28;
    y = y / 1.25;
    printf("x = %d,y = %d\n", x, y);
    // 得到坐标,完成什么逻辑,由用户控制
    if (x >= 280 && x < 350 && y >= 150 && y < 220)
    {
        return 1;
    }
    else if (x >= 500 && x < 600 && y >= 150 && y < 250)
    {
        return 2;
    }
    else if (x >= 280 && x <= 350 && y >= 300 && y <= 430)
    {
        return 3;
    }
    else if (x >= 500 && x < 600 && y >= 300 && y <= 430)
    {
        return 4;
    }
}

// 触摸屏函数,可以判断手指是否点击了指定的位置(suolue)
int get_touch_suolue()
{
    // 1.打开触摸屏
    int fd_touch = open("/dev/input/event0", O_RDWR);
    if (fd_touch == -1)
    {
        printf("open event0 error!\n");
        return -1;
    }
    // 定义一个结构体,保存读取到的输入信息
    struct input_event ev;
    int x, y;
    while (1)
    {
        // 2.读取输入事件
        // read是一个阻塞的函数,没有数据可读的时候,会一直等待
        int ret = read(fd_touch, &ev, sizeof(ev));
        if (ret != sizeof(ev))
        {
            continue;
        }
        // 3.解析输入事件
        if (ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value; // 记录得到的x坐标
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value; // 记录得到的y坐标
        }
        // 当手指离开触摸屏的时候结束
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            break;
        }
    }
    // 5.关闭触摸屏
    close(fd_touch);

    // 4.得到坐标
    x = x / 1.28;
    y = y / 1.25;
    printf("x = %d,y = %d\n", x, y);

    // 得到坐标,完成什么逻辑,由用户控制
    if (x >= 30 && x < 230 && y >= 60 && y < 210)
    {
        return 1;
    }
    else if (x >= 270 && x < 470 && y >= 60 && y < 210)
    {
        return 2;
    }
    else if (x >= 30 && x < 230 && y >= 240 && y < 390)
    {
        return 3;
    }
    else if (x >= 270 && x < 470 && y >= 240 && y < 390)
    {
        return 4;
    }
    else if (x >= 600 && x < 800 && y >= 0 && y < 200)
    {
        return 5;
    }
    else if (x >= 600 && x < 800 && y >= 200 && y < 400)
    {
        return 6;
    }
    else if (x >= 300 && x < 800 && y >= 400 && y <= 480)
    {
        return 100;
    }
}

// 触摸屏函数,可以判断手指是否点击了指定的位置(suolue_goto)
int get_touch_suolue_goto()
{
    // 1.打开触摸屏
    int fd_touch = open("/dev/input/event0", O_RDWR);
    if (fd_touch == -1)
    {
        printf("open event0 error!\n");
        return -1;
    }
    // 定义一个结构体,保存读取到的输入信息
    struct input_event ev;
    int x, y;
    while (1)
    {
        // 2.读取输入事件
        // read是一个阻塞的函数,没有数据可读的时候,会一直等待
        int ret = read(fd_touch, &ev, sizeof(ev));
        if (ret != sizeof(ev))
        {
            continue;
        }
        // 3.解析输入事件
        if (ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value; // 记录得到的x坐标
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value; // 记录得到的y坐标
        }
        // 当手指离开触摸屏的时候结束
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            break;
        }
    }
    // 5.关闭触摸屏
    close(fd_touch);

    // 4.得到坐标
    x = x / 1.28;
    y = y / 1.25;
    printf("x = %d,y = %d\n", x, y);
    // 得到坐标,完成什么逻辑,由用户控制
    if (x >= 30 && x < 230 && y >= 60 && y < 210)
    {
        return 1;
    }
}

// 触摸屏函数,可以判断手指是否点击了指定的位置
int get_touch_global_stop()
{
    // 1.打开触摸屏
    int fd_touch = open("/dev/input/event0", O_RDWR);
    if (fd_touch == -1)
    {
        printf("open event0 error!\n");
        return -1;
    }
    // 定义一个结构体,保存读取到的输入信息
    struct input_event ev;
    int x, y;
    while (1)
    {
        // 2.读取输入事件
        // read是一个阻塞的函数,没有数据可读的时候,会一直等待
        int ret = read(fd_touch, &ev, sizeof(ev));
        if (ret != sizeof(ev))
        {
            continue;
        }
        // 3.解析输入事件
        if (ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value; // 记录得到的x坐标
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value; // 记录得到的y坐标
        }
        // 当手指离开触摸屏的时候结束
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            break;
        }
    }
    // 5.关闭触摸屏
    close(fd_touch);

    // 4.得到坐标
    x = x / 1.28;
    y = y / 1.25;
    printf("x = %d,y = %d\n", x, y);
    // 得到坐标,完成什么逻辑,由用户控制
    if (x >= 350 && x < 550 && y >= 430 && y < 480)
    {
        return 1;
    }
}

int get_touch_video()
{
    // 1.打开触摸屏
    int fd_touch = open("/dev/input/event0", O_RDWR);
    if (fd_touch == -1)
    {
        printf("open event0 error!\n");
        return -1;
    }
    // 定义一个结构体,保存读取到的输入信息
    struct input_event ev;
    int x, y;
    while (1)
    {
        // 2.读取输入事件
        // read是一个阻塞的函数,没有数据可读的时候,会一直等待
        int ret = read(fd_touch, &ev, sizeof(ev));
        if (ret != sizeof(ev))
        {
            continue;
        }
        // 3.解析输入事件
        if (ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value; // 记录得到的x坐标
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value; // 记录得到的y坐标
        }
        // 当手指离开触摸屏的时候结束
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            break;
        }
    }
    // 5.关闭触摸屏
    close(fd_touch);

    // 4.得到坐标
    x = x / 1.28;
    y = y / 1.25;
    printf("x = %d,y = %d\n", x, y);
    // 得到坐标,完成什么逻辑,由用户控制
    if (x >= 550 && x < 800 && y >= 0 && y < 125)
    {
        return 1;
    }
    else if (x >= 550 && x < 800 && y >= 130 && y < 250)
    {
        return 2;
    }
    else if (x >= 550 && x < 800 && y > 270 & y < 430)
    {
        return 3;
    }
}

// 获取手指在触摸屏上的滑动方向
move_dir_t get_ts_direction(void)
{
    int ret;
    int fd;
    // printf("----1---\n");
    move_dir_t dir = MOVE_UNKNOWN;

    fd = open("/dev/input/event0", O_RDONLY);
    if (fd == -1)
    {
        perror("failed to open /dev/input/event0");
        return MOVE_UNKNOWN;
    }
    // printf("----2---\n");
    int x1 = -1, y1 = -1; // 记录点击事件中第一个点的坐标
    int x2, y2;           // 记录点出事件中最后一个点的坐标

    while (1)
    {
        struct input_event ev;
        ret = read(fd, &ev, sizeof(ev));
        if (ret != sizeof(ev))
        {
            continue;
        }

        // printf("type: %x  code: %x  value: %x\n", ev.type, ev.code, ev.value);

        // 触摸屏的x轴事件
        if (ev.type == EV_ABS && ev.code == ABS_X)
        {
            if (x1 == -1)
            {
                x1 = ev.value;
            }
            x2 = ev.value;
        }

        // 触摸屏的y轴事件
        if (ev.type == EV_ABS && ev.code == ABS_Y)
        {
            if (y1 == -1)
            {
                y1 = ev.value;
            }
            y2 = ev.value;
        }

        // 触摸屏弹起事件
        if ((ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) ||
            (ev.type == EV_ABS && ev.code == ABS_PRESSURE && ev.value == 0))
        {
            int delt_x = abs(x2 - x1);
            int delt_y = abs(y2 - y1);

            if (delt_x >= 2 * delt_y)
            {
                if (x2 > x1)
                {
                    dir = MOVE_RIGHT;
                }
                else
                {
                    dir = MOVE_LEFT;
                }

                break;
            }
            else if (delt_y >= 2 * delt_x)
            {
                if (y2 > y1)
                {
                    dir = MOVE_DOWN;
                }
                else
                {
                    dir = MOVE_UP;
                }
                break;
            }
            else
            {
                // 方向不明，请继续
                x1 = -1;
                y1 = -1;
            }
        }
    }

    close(fd);

    return dir;
}
