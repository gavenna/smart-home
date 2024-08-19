#include "bmp.h"
#include "hanzi.h"
#include "filelist.h"
#include "ts.h"
#include "lcd.h"
#include "menudisplay.h"
#include "jpeg.h"

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

extern FileList *list_content;
extern FileList *list_menu;
extern FileList *list_suolue;
extern FileList *list_icon;

extern int thread_prevent_redefine_cicle;
extern int thread_prevent_redefine_suolue;
extern int thread_prevent_redefine_detail;
extern int thread_prevent_redefine_effect;

extern int thread_flag;
extern int thread_menu_flag;
extern int thread_music_flag;
extern int thread_suolue_flag;
int id_node = 0;
int music_i = 1;

int tid_ary[4] = {0};

// static int stop_change_pic = 0;
// char *testpic = "1.bmp";
// static char *citypic[6][10] =
//     {
//         {"1.bmp", "2.bmp", "3.bmp"},
//         {"1.bmp", "2.bmp", "3.bmp"},
//         {"1.bmp", "2.bmp", "3.bmp"}};

void MENU_INIT(void)
{
    printf("add--in--menu--\n");
    list_menu->cur = list_menu->first;
    printf("what is :%s\n", list_menu->cur->pic_name);
    jpeg_display(list_menu->cur->pic_name, 0, 0);
    printf("check---jpg--\n");
    word_cicle_display(500, 100, 40, 37, 0, 3);

    word_cicle_display(500, 200, 40, 37, 0, 3);

    word_cicle_display(500, 300, 40, 37, 0, 3);

    lcd_draw_rectangle(0, 430, 800, 50, 0x0f0000);
    // thread_menu_flag = 0;
}

// circle-display
void *pic_circle(void *arg)
{
    thread_prevent_redefine_cicle = 1;
    // lcd_draw_rectangle(0, 0, 800, 480, 0x0f0f0f);
    while (1)
    {
        if (thread_flag != 0)
        {
            thread_prevent_redefine_cicle = 0;
            printf("xc_circle is exit\n");
            pthread_exit(0);
        }
        daohan_display();
        bmp_irea_display(list_content->cur->pic_name, 0, 0, 800, 50);
        // lcd_draw_rectangle(0, 430, 800, 50, 0x000000);
        daohan_display();
        change_to_next_pictures(list_content);
        sleep(1);
        // if (thread_flag != 0)
        // {
        //     thread_prevent_redefine_cicle = 0;
        //     printf("xc_circle is exit\n");
        //     pthread_exit(0);
        // }
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
            bmp_display(list_suolue->cur->pic_name, 30 + count_1 * 240, 20);
            printf("idnode--is--:%d\n", id_node);
            count_1++;
        }
        else
        {
            bmp_display(list_suolue->cur->pic_name, 30 + count_2 * 240, 230);
            count_2++;
        }
        list_suolue->cur = list_suolue->cur->next;
    }
}

// 缩略换页
void *total_display(void *arg)
{

    pthread_t force_suolue_stop, current_tid;
    current_tid = pthread_self();
    printf("effect tid :%d--\n");
    pthread_create(&force_suolue_stop, NULL, FORCE_SP_SUOLUE, (void *)&current_tid);
    // thread_prevent_redefine_suolue = 1;     // open_pret
    // lcd_draw_rectangle(0, 0, 800, 480, 0x000000);
    // suolue_display();
    char count = 'Y';
    while (1)
    {
        lcd_draw_rectangle(0, 0, 800, 430, 0x0f0f20);
        suolue_display();
        if (count == 'Y') // Only_f_One
        {
            list_suolue->cur = list_suolue->first;
            count = 'N';
        }
        int option_suolue = get_touch_suolue();
        printf("option_SUOLUE is :%d\n", option_suolue);

        switch (option_suolue)
        {
        case 1:
        {
            join_new_for_detail(option_suolue);
        }
        break;
        case 2:
        {
            join_new_for_detail(option_suolue);
        }
        break;
        case 3:
        {
            join_new_for_detail(option_suolue);
        }
        break;
        case 4:
        {
            join_new_for_detail(option_suolue);
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
            for (int i = 0; i < 4; i++)
            {
                list_suolue->cur = list_suolue->cur->prev;
            }
            suolue_display();
        }
        break;
        // case 7:
        // {
        //     list_suolue->cur = list_suolue->first;
        //     suolue_display();
        // }
        // break;
        default:
            break;
        }
        printf("-----test--if--influ--\n");
    }
}

void join_new_for_detail(int option_suolue)
{

    FileNode *p = list_suolue->cur;
    for (int i = 0; i < 4 - option_suolue; i++)
    {
        p = p->prev;
    }
    id_node = p->i_node;

    pthread_t tid_detail;
    int status;
    int done_suolue = pthread_create(&tid_detail, NULL, detail_display, NULL);
    // current_detail_tid = pthread_self();
    pthread_join(tid_detail, (void *)&status);
}

void *detail_display(void *arg)
{
    if (id_node > 4)
    {
        id_node = 4;
    }
    FileList *list_nation = search_pictures(nation_con[id_node]);
    bmp_display(list_nation->first->pic_name, 0, 0);
    list_nation->cur = list_nation->first;
    while (1)
    {
        // if (thread_flag != 0)
        // {
        //     // thread_prevent_redefine_detail = 0;
        //     pthread_exit(0);
        // }
        int done_detail = get_ts_direction();
        if (done_detail == 1)
        {
            list_nation->cur = list_nation->cur->next;
            bmp_display(list_nation->cur->pic_name, 0, 0);
        }
        else if (done_detail == 2)
        {
            list_nation->cur = list_nation->cur->prev;
            bmp_display(list_nation->cur->pic_name, 0, 0);
        }
        else if (done_detail == 3)
        {
            printf("thread_detail exit\n");
            pthread_exit(0);
        }
    }
}

void *FORCE_SP_SUOLUE(void *arg)
{
    int stio_tid = *((int *)arg);
    while (1)
    {
        if (thread_suolue_flag != 0)
        {
            pthread_cancel(stio_tid);
            pthread_exit(0);
        }
    }
}

void daohan_display()
{
    lcd_draw_rectangle(0, 430, 90, 50, 0x000000);
    lcd_draw_rectangle(140, 430, 90, 50, 0x000000);
    lcd_draw_rectangle(280, 430, 95, 50, 0x000000);
    lcd_draw_rectangle(425, 430, 155, 50, 0x000000);
}

void *show_icon(void *arg)
{
    list_icon->cur = list_icon->first;
    while (1)
    {
        bmp_display(list_icon->first->pic_name, 375, 430);
        bmp_display(list_icon->first->next->pic_name, 90, 430);
        // bmp_display(list_icon->first->next->next->pic_name, 275, 430);
        bmp_display(list_icon->last->prev->pic_name, 230, 430);
        // bmp_display(list_icon->last->pic_name, 175, 430);
    }
}

void *show_free(void *arg)
{
    while (1)
    {
        int i = 0;
        for (int i = 0; i < 4; i++)
        {
            hanzi_display(200 + i * 40, 200, 40, 37, hanzi[i]);
            hanzi_display(200 + (i + 1) * 40, 200, 40, 37, hanzi[4]);
        }
        int j = 4;
        while (j--)
        {
            hanzi_display(200 + 4 * 200, 200, 40, 37, hanzi[4]);
            sleep(0.5);
        }
        for (int i = 0; i < 4; i++)
        {
            lcd_draw_rectangle;
        }
    }
}

// 全局退出
void *global_stop(void *arg)
{
    while (1)
    {
        int option_stop = get_touch_global_stop();
        if (option_stop == 1)
        {
            pthread_t tid_effect;
            printf("---global-stop----\n");
            thread_flag = 1;
            thread_menu_flag = 0;   // open_efect
            thread_suolue_flag = 1; // close_suolue
            printf("----menu--addin?--\n");
            MENU_INIT();
            printf("---test---erro1--\n");
            if (thread_prevent_redefine_effect != 0)
            {
                continue;
            }
            int done_efect = pthread_create(&tid_effect, NULL, word_effect, NULL);
            printf("---test---erro1--\n");
            if (done_efect != 0)
            {
                printf("thread_efect creation failed\n");
                exit(1);
            }
        }
    }
}

void *FStop_xc(void *arg)
{
    int stio_tid = *((int *)arg);
    while (1)
    {
        if (thread_menu_flag != 0)
        {

            pthread_cancel(stio_tid);
            sleep(2);
            thread_prevent_redefine_effect = 0;
            pthread_exit(0);
        }
    }
}

void *word_effect(void *arg)
{

    pthread_t force_stop, current_suolue_tid;
    current_suolue_tid = pthread_self();
    printf("effect tid :%d--\n");
    pthread_create(&force_stop, NULL, FStop_xc, (void *)&current_suolue_tid);

    while (1)
    {
        thread_prevent_redefine_effect = 1; // open_prevt
        int count = 0;
        // lcd_draw_rectangle(200, 150, 2, 37, 0xffffff);
        // sleep(1);
        // jpeg_effect_display(list_menu->first->pic_name, 200, 150, 2, 37);
        lcd_draw_rectangle(195 + 1 * 40, 150, 2, 37, 0xffffff);
        sleep(0.5);
        jpeg_effect_display(list_menu->first->pic_name, 195, 150, 2, 37);
        sleep(0.5);
        lcd_draw_rectangle(195 + 1 * 40, 150, 2, 37, 0xffffff);

        sleep(0.5);
        jpeg_effect_display(list_menu->first->pic_name, 195, 150, 2, 37);

        for (int i = 0; i < 4; i++)
        {
            hanzi_no_bk_display(0xabcdef, 200 + count * 40, 150, 40, 37, hanzi[i]);
            lcd_draw_rectangle(195 + (count + 1) * 40, 150, 2, 37, 0xffffff);
            // jpeg_display(list_menu->first, 200 + (count + 1) * 40, 150);
            // hanzi_no_bk_display(0xffffff, 200 + (count + 1) * 40, 150, 40, 37, hanzi[4]);
            usleep(340000);
            jpeg_effect_display(list_menu->first->pic_name, 195 + (count + 1) * 40, 150, 45, 37);
            count++;
        }

        jpeg_effect_display(list_menu->first->pic_name, 195 + (count - 1) * 40, 150, 45, 37);
        sleep(0.5);
        lcd_draw_rectangle(195 + (count - 1) * 40, 150, 2, 37, 0xffffff);
        sleep(0.5);
        jpeg_effect_display(list_menu->first->pic_name, 195 + (count - 1) * 40, 150, 45, 37);
        sleep(0.5);
        lcd_draw_rectangle(195 + (count - 1) * 40, 150, 2, 37, 0xffffff);

        count = 0;
        for (int i = 0; i <= 5; i++)
        {
            jpeg_effect_display(list_menu->first->pic_name, 355 - count * 40, 150, 45, 37);
            sleep(0.5);
            if (i < 5)
                lcd_draw_rectangle(355 - count * 40, 150, 2, 37, 0xffffff);
            // jpeg_display(list_menu->first, 200 + (count + 1) * 40, 150);
            // hanzi_no_bk_display(0xffffff, 200 + (count + 1) * 40, 150, 40, 37, hanzi[4]);
            count++;
        }
        lcd_draw_rectangle(200, 150, 2, 37, 0xffffff);
        sleep(1);
        jpeg_effect_display(list_menu->first->pic_name, 200, 150, 2, 37);
    }
}

void *playmusic(void *arg)
{
    // 让其分离
    pthread_detach(pthread_self());

    char music_buf[128] = {0};
    while (1)
    {
        if (thread_music_flag != 0)
        {
            continue;
        }
        // system("killall -9 madplay"); // 保证别的madplay死掉
        sprintf(music_buf, "madplay -Q ./mp3/%d.mp3", music_i);
        printf("%s\n", music_buf);
        system(music_buf);
        // music_i++;
        // if(music_i > 2)
        // music_i = 1;
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