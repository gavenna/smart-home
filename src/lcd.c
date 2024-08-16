

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "lcd.h"

#define FB_FILE "/dev/fb0"

int fb_fd = -1; // 帧缓冲设备的 文件描述符

int lcd_width;       // 屏幕宽度
int lcd_height;      // 屏幕高度
int bytes_per_pixel; // 每个像素点所占字节数

int *plcd = NULL; // 指向帧缓冲区的首地址

/*
    lcd_open: 打开显示屏设备(帧缓冲设备)
    无参数、无返回值
*/

void lcd_open(void)
{
    int ret;

    //(1) 打开设备
    int fd = open(FB_FILE, O_RDWR);
    if (fd == -1)
    {
        perror("failed to open /dev/fb0");
        return;
    }
    fb_fd = fd;

    //(2) 获取屏幕信息
    struct fb_var_screeninfo var;
    ret = ioctl(fd, FBIOGET_VSCREENINFO, &var);
    if (ret == -1)
    {
        perror("failed to FBIOGET_VSCREENINFO");
        close(fd);
        fb_fd = -1;

        return;
    }
    // var.xres  var.yres  这个屏幕的分辨率
    // var.bits_per_pixel 每个像素点所占的bit位数
    // 整个帧缓冲区的大小: var.xres * var.yres * (var.bits_per_pixel/8)
    lcd_width = var.xres;
    lcd_height = var.yres;
    bytes_per_pixel = var.bits_per_pixel / 8;
    printf("resultion: %d x %d\n", lcd_width, lcd_height);
    printf("bytes_per_pixel: %d\n", bytes_per_pixel);

    // (3) mmap
    plcd = (int *)mmap(NULL,
                       lcd_width * lcd_height * bytes_per_pixel,
                       PROT_WRITE,
                       MAP_SHARED,
                       fd,
                       0);
    if (plcd == MAP_FAILED)
    {
        perror("failed to mmap");
        close(fd);
        fb_fd = -1;
        return;
    }
}

/*
    lcd_close: 关闭显示屏设备(帧缓冲设备)
    无参数、无返回值
*/
void lcd_close(void)
{
    // (5) 解映射
    munmap(plcd, lcd_width * lcd_height * bytes_per_pixel);

    //(6) 关闭设备
    close(fb_fd);
}

/*
    lcd_draw_point: 画点函数
    @x: 像素点的x轴坐标
    @y: 像素点的y轴坐标
    @color: 要显示的颜色值
    返回值：
        无。
*/
// inline内联函数： 建议编译器在编译时，把函数在调用处展开
//  内联函数中 不能使用 static全局变量!!! why ?你懂的。if you don't know, please call me.
inline void lcd_draw_point(int x, int y, int color)
{
    if (x >= 0 && x < lcd_width && y >= 0 && y < lcd_height)
    {
        *(plcd + y * lcd_width + x) = color;
    }
}

void lcd_draw_rectangle(int x0, int y0, // 矩形左上顶点的坐标
                        int w, int h,   // 矩形的宽和高
                        int color)      // 矩形的颜色
{
    // 设像素点(x,y)为该矩形内的任意一个点
    int x, y;
    for (y = y0; y < y0 + h; y++)
    {
        for (x = x0; x < x0 + w; x++)
        {
            lcd_draw_point(x, y, color);
        }
    }
}
