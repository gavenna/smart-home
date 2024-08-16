

#include "lcd.h"
#include "hanzi.h"

void hanzi_display(
    int x0, int y0,      // 该汉字在屏幕上要显示的位置
    int w, int h,        // 该汉字的宽 和  高
    unsigned char data[] // 要显示的汉字的“取模后的数据”
)
{

    int dian; // 第 dian 个像素点
              //  dian [0， w*h)

    for (dian = 0; dian < w * h; dian++)
    {
        // 显示 这个 dian: 要在屏幕上的合适位置上显示这个 dian
        // 设这个dian在屏幕的位置为 (x,y)
        int x, y;

        // dian在原始汉字的第  几 行呢?
        //   dian / w
        // dian在屏幕上是第几行呢？
        y = y0 + dian / w;

        // dian在原始汉字的第 几 列呢?
        //   dian % w
        // dian在屏幕上是第几列呢?
        x = x0 + dian % w;

        // 这个dian取模后的数据在 数组data[]的第几个元素中呢?
        int index = dian / 8; // 数据元素的下标

        // data[index] 包括了8个bits(代表8个像素点的数据),那你这个dian在第几bit呢?
        int bit = 7 - dian % 8; // 你在第几bit上？

        int color;
        if (data[index] & (1 << bit))
        {
            color = 0xFF0000; // 红色
        }
        else
        {
            color = 0; // 黑色
        }

        lcd_draw_point(x, y, color);
    }
}

// void int_display(int digtal, int x0, int y0)
// {
// int a[20]; //保存 整数digtal的每一位上的数字
// int i = 0;

// if (digtal == 0)
// {
//     // ...

//     return ;
// }

// while (digtal)
// {
//     a[i++] = digtal % 10;
//     digtal = digtal / 10;
// }

// //先显示 符号 +  -

// for ( i--; i >= 0; i--)
// {
//     hanzi_display(x0,y0, 8, 16,  digtal_[a[i]]);
//     x0 += 8;
// }
// }

// 从左往右输出 整数
void digit_display(int num, int x0, int y0)
{
    int count = 0;
    int cheng = 1;
    int gewei;
    int digit_width = 24;
    int digit_high = 37;
    if (num < 0)
    {
        hanzi_display(x0, y0, digit_width, digit_high, digit[11]);
        num *= -1;
        count++;
    }
    while (1)
    {
        cheng *= 10; // 比出位数，以便优先输出首位
        if (cheng > num)
        {
            cheng /= 10;
            while (num)
            {
                gewei = num / cheng;
                num -= gewei * cheng;
                hanzi_display((x0 + count * digit_width), y0, digit_width, digit_high, digit[gewei]);
                cheng /= 10;
                count++;
            }
            break;
        }
        if (cheng > 100000)
            break;
    }
}

// 从左往右输出 浮点数
void double_display(double num, int x0, int y0)
{
    int laizi = 0.000001;
    int count = 0;
    int cheng = 1;
    int gewei;
    int digit_width = 24;
    int digit_high = 37;
    if (num < 0)
    {
        hanzi_display(x0, y0, digit_width, digit_high, digit[11]);
        num *= -1;
        count++;
    }
    while (1)
    {
        cheng *= 10;
        if (cheng > num)
        {
            cheng /= 10;
            while ((int)num)
            {
                gewei = (int)num / cheng;
                num -= gewei * cheng;
                hanzi_display((x0 + count * digit_width), y0, digit_width, digit_high, digit[gewei]);
                cheng /= 10;
                count++;
            }
            hanzi_display((x0 + count * digit_width), y0, digit_width, digit_high, digit[10]);
            count++;
            int cishu = 3;
            while (cishu--)
            {
                num *= 10;
                gewei = (int)num;
                if (gewei != 0)
                {
                    num -= gewei;
                }
                hanzi_display((x0 + count * digit_width), y0, digit_width, digit_high, digit[gewei]);
                count++;
            }
            break;
        }
    }
}

// 从右往左输出 整数
void digit_new(int num, int x0, int y0)
{
    int gewei, count = 0;
    int digit_width = 24;
    int digit_high = 37;
    while (num)
    {
        gewei = num % 10;
        num /= 10;
        hanzi_display(x0 - count * digit_width, y0, digit_width, digit_high, digit[gewei]);
        count++;
    }
}

// 浮点数
void digit_double_new(double num, int x0, int y0)
{
    int gewei = (int)num;
    int count = 0;
    int baoliu = 3;
    int digit_width = 24;
    int digit_high = 37;
    digit_new(gewei, x0, y0);
    hanzi_display(x0, y0, digit_width, digit_high, digit[10]);
    num -= gewei;
    while (baoliu--)
    {
        num *= 10;
        gewei = (int)num;
        num -= gewei;
        hanzi_display(x0 - count * digit_width, y0, digit_width, digit_high, digit[gewei]);
        count++;
    }
}

// 循环显示文字
void word_cicle_display(int x0, int y0, int w, int h, int dest_first, int dest_last)
{
    int count = 0;
    for (int i = dest_first; i <= dest_last; i++)
    {
        hanzi_display(x0 + count * w, y0, w, h, hanzi[i]);
        count++;
    }
}