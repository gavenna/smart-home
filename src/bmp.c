
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "lcd.h"

void bmp_display(const char *bmp_file, int x0, int y0)
{

    int fd = open(bmp_file, O_RDONLY);
    if (fd == -1)
    {
        printf("failed to open bmp file: %s\n", bmp_file);

        return;
    }

    int width;
    unsigned char buf[4];

    lseek(fd, 0x12, SEEK_SET);
    read(fd, buf, 4);
    width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

    int height;

    lseek(fd, 0x16, SEEK_SET);
    read(fd, buf, 4);
    height = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

    short depth;

    lseek(fd, 0x1C, SEEK_SET);
    read(fd, buf, 2);
    depth = (buf[1] << 8) | buf[0];
    if (!(depth == 24 || depth == 32))
    {
        printf("Not Supported!!!\n");
        return;
    }

    int valid_bytes_per_line; // 每一行有效的数据字节数
    int laizi = 0;            // 每一行末尾的填充的“赖子”数
    int total_bytes_per_line; // 每一行实际的字节数.
    int total_bytes;          // 整个像素数组的字节数

    valid_bytes_per_line = abs(width) * (depth / 8);
    if (valid_bytes_per_line % 4)
    {
        laizi = 4 - valid_bytes_per_line % 4;
    }
    total_bytes_per_line = valid_bytes_per_line + laizi;
    total_bytes = abs(height) * total_bytes_per_line;

    unsigned char *pixel = (unsigned char *)malloc(total_bytes);
    lseek(fd, 54, SEEK_SET);
    read(fd, pixel, total_bytes);

    // 解析像素数据，并在屏幕上显示
    // ... do it yourself ...
    unsigned char b, g, r, a = 0;
    int color;
    int i = 0;
    int x, y;
    for (y = 0; y < abs(height); y++)
    {
        for (x = 0; x < abs(width); x++)
        {
            b = pixel[i++];
            g = pixel[i++];
            r = pixel[i++];
            if (depth == 32)
            {
                a = pixel[i++];
            }

            color = (a << 24) | (r << 16) | (g << 8) | b;
            lcd_draw_point(x0 + x, y0 + abs(height) - 1 - y, color);
        }
        i += laizi;
    }

    free(pixel);

    close(fd);
}

void bmp_icon_display(const char *bmp_file, int x0, int y0)
{

    int fd = open(bmp_file, O_RDONLY);
    if (fd == -1)
    {
        printf("failed to open bmp file: %s\n", bmp_file);

        return;
    }

    int width;
    unsigned char buf[4];

    lseek(fd, 0x12, SEEK_SET);
    read(fd, buf, 4);
    width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

    int height;

    lseek(fd, 0x16, SEEK_SET);
    read(fd, buf, 4);
    height = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

    short depth;

    lseek(fd, 0x1C, SEEK_SET);
    read(fd, buf, 2);
    depth = (buf[1] << 8) | buf[0];
    if (!(depth == 24 || depth == 32))
    {
        printf("Not Supported!!!\n");
        return;
    }

    int valid_bytes_per_line; // 每一行有效的数据字节数
    int laizi = 0;            // 每一行末尾的填充的“赖子”数
    int total_bytes_per_line; // 每一行实际的字节数.
    int total_bytes;          // 整个像素数组的字节数

    valid_bytes_per_line = abs(width) * (depth / 8);
    if (valid_bytes_per_line % 4)
    {
        laizi = 4 - valid_bytes_per_line % 4;
    }
    total_bytes_per_line = valid_bytes_per_line + laizi;
    total_bytes = abs(height) * total_bytes_per_line;

    unsigned char *pixel = (unsigned char *)malloc(total_bytes);
    lseek(fd, 54, SEEK_SET);
    read(fd, pixel, total_bytes);

    // 解析像素数据，并在屏幕上显示
    // ... do it yourself ...
    unsigned char b, g, r, a = 0;
    int color;
    int i = 0;
    int x, y;
    for (y = 0; y < abs(height); y++)
    {
        for (x = 0; x < abs(width); x++)
        {
            b = pixel[i++];
            g = pixel[i++];
            r = pixel[i++];
            if (depth == 32)
            {
                a = pixel[i++];
            }

            color = (a << 24) | (r << 16) | (g << 8) | b;
            if (color == 0x00000000)
                continue;
            lcd_draw_point(x0 + x, y0 + abs(height) - 1 - y, color);
        }
        i += laizi;
    }

    free(pixel);

    close(fd);
}

void bmp_irea_display(const char *bmp_file, int x0, int y0, int x_end, int y_end)
{

    int fd = open(bmp_file, O_RDONLY);
    if (fd == -1)
    {
        printf("failed to open bmp file: %s\n", bmp_file);
        return;
    }

    int width;
    unsigned char buf[4];

    lseek(fd, 0x12, SEEK_SET);
    read(fd, buf, 4);
    width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

    int height;

    lseek(fd, 0x16, SEEK_SET);
    read(fd, buf, 4);
    height = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

    short depth;

    lseek(fd, 0x1C, SEEK_SET);
    read(fd, buf, 2);
    depth = (buf[1] << 8) | buf[0];
    if (!(depth == 24 || depth == 32))
    {
        printf("Not Supported!!!\n");
        return;
    }

    int valid_bytes_per_line; // 每一行有效的数据字节数
    int laizi = 0;            // 每一行末尾的填充的“赖子”数
    int total_bytes_per_line; // 每一行实际的字节数.
    int total_bytes;          // 整个像素数组的字节数

    valid_bytes_per_line = abs(width) * (depth / 8);
    if (valid_bytes_per_line % 4)
    {
        laizi = 4 - valid_bytes_per_line % 4;
    }
    total_bytes_per_line = valid_bytes_per_line + laizi;
    total_bytes = abs(height) * total_bytes_per_line;

    unsigned char *pixel = (unsigned char *)malloc(total_bytes);
    lseek(fd, 54, SEEK_SET);
    read(fd, pixel, total_bytes);

    // 解析像素数据，并在屏幕上显示
    // ... do it yourself ...
    unsigned char b, g, r, a = 0;
    int color;
    int i = 0;
    int x, y;
    for (y = 0; y < abs(height); y++)
    {
        for (x = 0; x < abs(width); x++)
        {
            b = pixel[i++];
            g = pixel[i++];
            r = pixel[i++];
            if (depth == 32)
            {
                a = pixel[i++];
            }
            color = (a << 24) | (r << 16) | (g << 8) | b;
            // if (buff[(height - 1 - y) * width + x] == 0x00ffffff)
            //     continue;
            if (x < x_end && y > y_end)
            {
                lcd_draw_point(x0 + x, y0 + abs(height) - 1 - y, color);
            }
        }
        i += laizi;
    }
    free(pixel);

    close(fd);
}
