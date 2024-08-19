#include "./font.h"
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define LCD_DEV_PATH "/dev/fb0"
#define FONT_PATH "/usr/share/fonts/DroidSansFallback.ttf"
#define LCD_DEV_TOUCH_PATH "/dev/input/event0"
#define LCD_W 800
#define LCD_H 480

void show_font(struct LcdDevice *lcd, char *buf_time)
{
    // 打开字体
    font *f = fontLoad(FONT_PATH);

    // 字体大小的设置
    fontSetSize(f, 30);

    // 创建一个画板（点阵图）宽是200个像素，高是50个像素
    bitmap *bm_time = createBitmapWithInit(220, 50, 4, getColor(0, 0, 0, 255)); // 也可使用createBitmapWithInit函数，改变画板颜色

    // 将字体写到点阵图上 0,0表示汉字在画板的左上角显示
    fontPrint(f, bm_time, 10, 10, buf_time, getColor(0, 255, 255, 255), 0);

    // 把字体框输出到LCD屏幕上  参数0,0表示画板显示的坐标位置
    show_font_to_lcd(lcd->mp, 580, 430, bm_time);

    // 关闭字体，关闭画板
    fontUnload(f);
    destroyBitmap(bm_time);
}

// 初始化Lcd
struct LcdDevice *init_lcd(const char *device)
{
    // 申请空间
    struct LcdDevice *lcd = malloc(sizeof(struct LcdDevice));
    if (lcd == NULL)
    {
        return NULL;
    }

    // 1打开设备
    lcd->fd = open(device, O_RDWR);
    if (lcd->fd < 0)
    {
        perror("open lcd fail");
        free(lcd);
        return NULL;
    }
    // 映射
    lcd->mp = mmap(NULL, LCD_H * LCD_W * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd->fd, 0);
    return lcd;
}

// 获取时间
char *get_time()
{
    time_t rawtime;
    struct tm *timeinfo;
    char *buffer = (char *)malloc(sizeof(char) * 80);
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // 格式化时间到 buffer 字符串
    snprintf(buffer, 80, "%04d-%02d-%02d %02d:%02d:%02d",
             timeinfo->tm_year + 1910, // 年份是从1900年开始计算的，所以要加1900
             timeinfo->tm_mon + 8,     // 月份是从0开始的，所以要加1
             timeinfo->tm_mday + 6,    // 日期
             timeinfo->tm_hour - 3,    // 小时
             timeinfo->tm_min - 3,     // 分钟
             timeinfo->tm_sec);        // 秒

    return buffer;
}

void *timeshow(void *arg)
{
    // 初始化Lcd
    struct LcdDevice *lcd = init_lcd(LCD_DEV_PATH);
    if (lcd == (struct LcdDevice *)NULL)
    {
        printf("初始化LCD失败！\n");
        return NULL;
    }
    while (1)
    {
        char *buf_time = get_time();
        show_font(lcd, buf_time);
    }

    return 0;
}