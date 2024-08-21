

#ifndef __BMP_H__
#define __BMP_H__

void bmp_display(const char *bmp_file, int x0, int y0);

void bmp_irea_display(const char *bmp_file, int x0, int y0, int x_end, int y_end);

void bmp_icon_display(const char *bmp_file, int x0, int y0);
#endif