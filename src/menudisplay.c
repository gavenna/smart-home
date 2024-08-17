#include "bmp.h"
#include "hanzi.h"
#include "filelist.h"
#include "ts.h"
#include "lcd.h"

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

extern FileList *list_content;
extern FileList *list_menu;
extern FileList *list_suolue;

extern int thread_flag;
extern int thread_prevent_redefine;

// static int stop_change_pic = 0;

void *MENU_INIT(void)
{
    list_menu->cur = list_menu->first;
    bmp_display(list_menu->cur->pic_name, 0, 0);
    // message_show
    word_cicle_display(500, 100, 40, 37, 0, 3);

    word_cicle_display(500, 200, 40, 37, 0, 3);

    word_cicle_display(500, 300, 40, 37, 0, 3);
}

// circle-display
void *pic_circle(void *arg)
{
    lcd_draw_rectangle(0, 0, 800, 480, 0x0f0f0f);
    while (1)
    {
        bmp_display(list_content->cur->pic_name, 0, 0);
        change_to_next_pictures(list_content);
        sleep(1);
        if (thread_flag != 0)
        {
            thread_prevent_redefine = 0;
            pthread_exit(0);
        }
    }
}

// 缩略显示
void suolue_display()
{
    int count_1 = 0;
    int count_2 = 0;
    for (int i = 0; i < 4; i++)
    {
        if (i < 2)
        {
            bmp_display(list_suolue->cur->pic_name, 30 + count_1 * 240, 60);

            count_1++;
        }
        else
        {
            bmp_display(list_suolue->cur->pic_name, 30 + count_2 * 240, 270);
            count_2++;
        }
        list_suolue->cur = list_suolue->cur->next;
    }
}

// 缩略换页
void *total_display(void *arg)
{
    lcd_draw_rectangle(0, 0, 800, 480, 0x0f0f0f);
    suolue_display();
    while (1)
    {
        // suolue_display();
        int option_suolue = get_touch_suolue();

        printf("option_SUOLUE is :%d", option_suolue);
        switch (option_suolue)
        {
        case 1:
        {
        }
        break;
        case 5:
        {
            for (int i = 0; i < 4; i++)
            {
                list_suolue->cur = list_suolue->cur->next;
            }
            suolue_display();
        }
        break;
        case 6:
        {
            for (int i = 0; i < 7; i++)
            {
                list_suolue->cur = list_suolue->cur->prev;
            }
            suolue_display();
        }
        break;
        case 7:
        {
            return NULL;
        }
        break;
        default:
            break;
        }
    }
}

// // 线程进入详情页面
// void *suolue_goto_deep(void *arg)
// {
//     int goto_index;
//     while (1)
//     {
//         goto_index = get_touch_suolue_goto();
//         // stop_change_pic = 1;
//         if (goto_index < 7)
//             printf("suolue-goto:%d\n", goto_index);
//         if (thread_flag != 0)
//         {
//             return NULL;
//         }
//     }
// }