

#include "filelist.h"
#include "lcd.h"
#include "hanzi.h"
#include "bmp.h"
#include "jpeg.h"
#include "ts.h"
#include "menudisplay.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

FileList *list;
FileList *list_menu;
FileList *list_suolue;

#define MAINPIC "storepic"
#define MENU "storepic/menu"
#define SUOLUE "storepic/suolue"

int terminate = 0;   // 进程(程序)退出的标记
                     //  terminate = 1 进程要退出啦
                     //  terminate = 0 进程继续
int thread_flag = 0; // 主线标记
int thread_prevent_redefine = 0;

int main(int argc, char *argv[])
{
    // 显示主菜单
    // 背景--菜单页---音乐播放
    // 选择模式
    //  循环播放
    //  滑动翻页
    //  详情总览查看
    //  显示总概图(6 or 9张)---点击进入对应具体介绍

    lcd_open();
    printf("action!\n");

    list = search_pictures(MAINPIC);
    print_FistList(list);

    list_menu = search_pictures(MENU);
    print_FistList(list_menu);

    list_suolue = search_pictures(SUOLUE);
    print_FistList(list_suolue);

    MENU_INIT();

    // pthread_t tid2;
    // printf("main thread,ID is %u\n", pthread_self());
    // int done = pthread_create(&tid2, NULL, total_display, NULL);
    // if (done != 0)
    // {
    //     printf("thread creation failed\n");
    //     exit(1);
    // }

    while (1)
    {
        int option = get_touch();
        printf("option = %d\n", option);
        switch (option)
        {
        case 1:
        {
            thread_flag = 0;
            pthread_t tid2;
            int status;
            int done_suolue = pthread_create(&tid2, NULL, total_display, NULL);
            if (done_suolue != 0)
            {
                printf("thread creation failed\n");
                exit(1);
            }
            pthread_join(tid2, (void *)&status);
            if (status == 0)
            {
                printf("xc is exit\n");
            }
            // sleep(1);
            MENU_INIT();
        }
        break;
        case 2:
        {
            thread_flag = 0;

            if (thread_prevent_redefine == 1)
            {
                continue;
            }
            thread_prevent_redefine = 1;
            pthread_t tid1;
            int status;
            printf("main thread,ID is %u\n", pthread_self());
            int done = pthread_create(&tid1, NULL, pic_circle, NULL);
            if (done != 0)
            {
                printf("thread creation failed\n");
                exit(1);
            }
            // pthread_join(tid1, (void *)&status);
            // if (status == 0)
            // {
            //     printf("xc is exit\n");
            // }
            // sleep(1);
            // MENU_INIT();
        }
        break;
        case 3:
            thread_flag = 1;
            MENU_INIT();
        default:
            break;
        }
    }

    lcd_close();

    return 0;
}
