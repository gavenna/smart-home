

#ifndef __LCD_H__
#define __LCD_H__

extern int fb_fd ; //帧缓冲设备的 文件描述符

extern int  lcd_width ;//屏幕宽度
extern int  lcd_height;//屏幕高度
extern int  bytes_per_pixel; //每个像素点所占字节数

extern int* plcd ; //指向帧缓冲区的首地址


//打开屏幕
void lcd_open(void);


//关闭屏幕
void lcd_close(void);


/*
    lcd_draw_point:画点函数
        给屏幕上坐标(x,y)的像素点，显示一个颜色。
    @x : 像素点的x轴坐标
    @y : 像素点的y轴坐标
    @color: 要显示的颜色值
    返回值：
        无。
*/
void lcd_draw_point(int x, int y, int color);




void lcd_draw_rectangle(int x0, int y0, //矩形左上顶点的坐标
                        int w, int h,  //矩形的宽和高
                        int color); //矩形的颜色

#endif 