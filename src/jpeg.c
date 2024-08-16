

#include <stdio.h>
#include <stdlib.h>

#include "jpeglib.h"
#include "lcd.h"

void jpeg_display(const char *jpeg_file, int x0, int y0)
{
    //printf("%s L_%d\n", __FUNCTION__, __LINE__);
    // -（1）分配并且初始化一个JPEG对象

    // struct jpeg_decompree_struct//这个结构体在LIBJPEG这个库中
    // //是用来保存一个解压JPEG文件所需要的信息的

    // struct jpeg_error_mgr //这个结构体在libjpeg库中用来保存
    // //解压或则压缩过程中一些出错信息的

    struct jpeg_decompress_struct dinfo;//申明一个解压对象

    struct jpeg_error_mgr jerr;//声明一个出错信息的对象

    dinfo.err=jpeg_std_error(&jerr);

    jpeg_create_decompress(&dinfo);//初始化dinfo这个对象



    //printf("%s L_%d\n", __FUNCTION__, __LINE__);

    //    2 用标准IO来打开这个文件
    FILE *infile=fopen(jpeg_file,"r");
    if(infile==NULL)
    {
        perror("faile to open jpeg_file");
        return ;
    }
    
    jpeg_stdio_src(&dinfo, infile);//指定要解压的图像文件

    //printf("%s L_%d\n", __FUNCTION__, __LINE__);

    //- （3）调用 jpeg_read_header()获得我们的图像信息
    jpeg_read_header(&dinfo, TRUE);

    //printf("%s L_%d\n", __FUNCTION__, __LINE__);

    //- （4）调用jpeg_start_decompress()启动解压过程
    jpeg_start_decompress(&dinfo);

    // -（5）在调用完上面这个函数之后，jpeg对象dinfo中
    // >	下面几个字段（成员变量）将会比较有用：
    // >	dinfo.output_width: 解压后图像的输出宽度，一行占多少个像素点
    // >   dinfo.output_height: 解压后图像的输出高度，占多少行
    // >   dinfo.output_components: 每个像素点的分量数，每个像素点占多少个字节
    // >>					3 RGB
    // >>					4 ARGB
    // >	总字节数=dinfo.output_width*dinfo.output_height*dinfo.output_components
                        
                
    // >	在调用完jpeg_start_decompress()后，往往需要为解压后的扫描线上所有的像素点分配空间
    // >  存一行：	malloc(dinfo.output_width * dinfo.output_components);	jpeg_start_decompress(&dinfo);

    printf(" jpg: %d x %d\n", dinfo.output_width, dinfo.output_height);

    unsigned char * buffer = (unsigned char*) malloc( dinfo.output_width * dinfo.output_components);
// - (6)读取一行或者多行扫描线上数据处理通常是这样的
	//    对扫描线的读取是按照从上到下的顺序进行的，也就是说图像最上方的扫描线最先
    // 被jpeg_read_scanlines()读入到存储空间中，紧接着是第二行扫描线，最后是
    // 图像底边的扫描线被读入到存储空间中去。		
    //dinfo.output_scanline   表示的意思是已经扫描了多少行
    while(dinfo.output_scanline<dinfo.output_height)
    {
        jpeg_read_scanlines(&dinfo,//解压对象
                            &buffer, //保存解压后数据的二级指针
                            1//读取多少行数据来解压
                            );

        // ... 
        // 第 dinfo.output_scanline - 1 行 解压后的数据 保存 buffer
        int i = 0;
        for (int x = 0; x < dinfo.output_width; x++)
        {
            unsigned char a = 0, r,g, b;
            int color;
            
            if (dinfo.output_components == 3)
            {
                // R G B R G B R G B ...
                a = 0;
                r = buffer[i++];
                g = buffer[i++];
                b = buffer[i++];
            }
            else if (dinfo.output_components == 4) 
            {
                //A R G B A R G B A R G B ...
                a = buffer[i++];
                r = buffer[i++];
                g = buffer[i++];
                b = buffer[i++];
            }
            color = (a << 24) | (r << 16) | (g << 8) | b;

            lcd_draw_point(x0 + x, y0 + dinfo.output_scanline - 1, color );
        }
    }

			
    // - 7. 调用jpeg_finish_decompress()完成解压过程
    jpeg_finish_decompress(&dinfo);

    //- 8. 调用jpeg_destroy_decompress释放jpeg解压对象dinfo
    jpeg_destroy_decompress(&dinfo);


    free(buffer);
    fclose(infile);

    return ;
 

}