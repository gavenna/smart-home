

#include "filelist.h"
#include "lcd.h"
#include "hanzi.h"
#include "bmp.h"
#include "jpeg.h"
#include "ts.h"
#include "menudisplay.h"
#include "font.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

FileList *list_content = NULL;
FileList *list_menu = NULL;
FileList *list_suolue = NULL;
FileList *list_icon = NULL;

#define MAINPIC "storepic"
#define MENU "storepic/menu"
#define SUOLUE "storepic/suolue"
#define ICON "storepic/icon"

int terminate = 0;        // 进程(程序)退出的标记
                          //  terminate = 1 进程要退出啦
                          //  terminate = 0 进程继续
int thread_flag = 0;      // 主线标记
int thread_menu_flag = 0; // effect
int thread_music_flag = 0;
int thread_suolue_flag = 0;

int thread_prevent_redefine_cicle = 0;
int thread_prevent_redefine_suolue = 0;
int thread_prevent_redefine_detail = 0;
int thread_prevent_redefine_effect = 0;

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

    list_content = search_pictures(MAINPIC);
    make_inode(list_content);
    print_FistList(list_content);

    list_menu = search_pictures(MENU);
    make_inode(list_menu);
    print_FistList(list_menu);

    list_suolue = search_pictures(SUOLUE);
    make_inode(list_suolue);
    print_FistList(list_suolue);

    list_icon = search_pictures(ICON);
    make_inode(list_icon);
    print_FistList(list_icon);

    MENU_INIT();

    pthread_t tid_icon, tid_global_stop, tid_time, tid_effect, tid_music;
    // global_stop
    int done_stop = pthread_create(&tid_global_stop, NULL, global_stop, NULL);
    if (done_stop != 0)
    {
        printf("thread_icon creation failed\n");
        exit(1);
    }
    // icon_show
    int done_icon = pthread_create(&tid_icon, NULL, show_icon, NULL);
    if (done_icon != 0)
    {
        printf("thread_stop creation failed\n");
        exit(1);
    }
    // time_show
    int done_time = pthread_create(&tid_time, NULL, timeshow, NULL);
    if (done_time != 0)
    {
        printf("thread_time creation failed\n");
        exit(1);
    }
    // effect_print
    int done_efect = pthread_create(&tid_effect, NULL, word_effect, NULL);
    if (done_efect != 0)
    {
        printf("thread_efect creation failed\n");
        exit(1);
    }
    // display_music
    int done_music = pthread_create(&tid_music, NULL, playmusic, NULL);

    sleep(2);

    while (1)
    {

        int option = get_touch();
        printf("option = %d\n", option);
        switch (option)
        {
        case 1:
        {

            // if (thread_prevent_redefine_suolue != 0) // initial_value is 0
            // {
            //     continue;
            // }
            // initial_stat
            // thread_flag = 0;
            thread_menu_flag = 1; // close_efect
            thread_suolue_flag = 0;

            pthread_t tid_ttdisplay;
            int status;
            int done_suolue = pthread_create(&tid_ttdisplay, NULL, total_display, NULL);
            if (done_suolue != 0)
            {
                printf("thread creation failed\n");
                exit(1);
            }
            pthread_join(tid_ttdisplay, (void *)&status); // prevt  away from main
            MENU_INIT();                                  // prevt_lastshadow
            printf("thread_ttdisplay exit code %d\n", status);
            // if (status == 0)
            // {
            //     printf("suolue_xc is exit\n");
            // }
            // sleep(1);
            // MENU_INIT();
        }
        break;
        case 2:
        {
            if (thread_prevent_redefine_cicle == 1)
            {
                continue;
            }
            thread_flag = 0;
            thread_menu_flag = 1;
            usleep(2000);
            pthread_t tid1;
            int status;
            printf("main thread,ID is %u\n", pthread_self());
            int done = pthread_create(&tid1, NULL, pic_circle, NULL);
            if (done != 0)
            {
                printf("thread creation failed\n");
                exit(1);
            }
            pthread_join(tid1, (void *)&status);
            if (status == 0)
            {
                printf("xc is exit\n");
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
        case 100:
        {
            thread_flag = 1;
            thread_music_flag = !thread_music_flag;
            system("killall -9 madplay");
            // MENU_INIT();

            // int done_efect = pthread_create(&tid_effect, NULL, word_effect, NULL);
            // if (done_efect != 0)
            // {
            //     printf("thread_efect creation failed\n");
            //     exit(1);
            // }
        }

        default:
            break;
        }
    }

    lcd_close();

    return 0;
}
