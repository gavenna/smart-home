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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

extern FileList *list_content;
extern FileList *list_menu;
extern FileList *list_suolue;
extern FileList *list_icon;

extern int thread_prevent_redefine_cicle;
extern int thread_prevent_redefine_suolue;
extern int thread_prevent_redefine_detail;
extern int thread_prevent_redefine_effect;
extern int thread_prevent_redefine_video;

extern int thread_flag;
extern int thread_menu_flag;
extern int thread_music_flag;
extern int thread_suolue_flag;
extern int thread_video_flag;
// int id_node = 0;
int music_i = 1;
int video_i = 1;
char count = 'A';
int ary_video[2] = {0};

unsigned int tid_detail = 0;

char *icon_name[] = {"storepic/icon/home.bmp", "storepic/icon/wet1.bmp", "storepic/icon/temp2.bmp", "storepic/icon/wet2.bmp", "storepic/icon/temp1.bmp", "storepic/icon/photo.bmp", "storepic/icon/circle.bmp", "storepic/icon/music.bmp", "storepic/icon/video.bmp", "storepic/icon/action.bmp", "storepic/icon/stop.bmp"};
#define left "storepic/icon/left.bmp"
#define right "storepic/icon/right.bmp"
void MENU_INIT(void)
{
    printf("add--in--menu--\n");
    list_menu->cur = list_menu->first;
    printf("what is :%s\n", list_menu->cur->pic_name);
    jpeg_display(list_menu->cur->pic_name, 0, 0);
    printf("check---jpg--\n");
    // word_cicle_display(500, 100, 40, 37, 0, 3);

    // word_cicle_display(500, 200, 40, 37, 0, 3);

    // word_cicle_display(500, 300, 40, 37, 0, 3);

    lcd_draw_rectangle(0, 430, 800, 50, 0x0f0000);
    daohan_display();

    bmp_icon_display(icon_name[5], 220, 200);

    bmp_icon_display(icon_name[5], 420, 200);
    bmp_icon_display(icon_name[6], 500, 210);

    bmp_icon_display(icon_name[7], 220, 310);

    bmp_icon_display(icon_name[8], 420, 310);

    word_cicle_display(240, 280, 16, 13, 0, 1);
    word_cicle_display(445, 280, 16, 13, 2, 3);
    word_cicle_display(240, 400, 16, 13, 4, 5);
    word_cicle_display(445, 400, 16, 13, 6, 7);

    // thread_menu_flag = 0;
}

// circle-display
void *pic_circle(void *arg)
{
    pthread_t force_circle_stop, current_tid;
    current_tid = pthread_self();
    printf("circle tid :%d--\n");
    pthread_create(&force_circle_stop, NULL, FORCE_StoP, (void *)&current_tid);

    thread_prevent_redefine_cicle = 1;
    int ary = 0;
    while (1)
    {

        FileList *list_circle = search_pictures(nation_con[ary]);
        FileNode *p = list_circle->first;
        do
        {
            bmp_display(p->pic_name, 0, 0);
            p = p->next;
            sleep(1);
        } while (p != list_circle->first);
        ary++;
        if (ary == 8)
        {
            ary = 0;
        }
    }
}

void suolue_name(int i, int j)
{
    switch (i)
    {
    case 0:
    {
        word_suolue_display(30 + j * 240, 20 + 150, 40, 37, 0, 1);
    }
    break;
    case 1:
    {
        word_suolue_display(30 + j * 240, 20 + 150, 40, 37, 2, 5);
    }
    break;
    case 4:
    {
        word_suolue_display(30 + j * 240, 20 + 150, 40, 37, 13, 17);
    }
    break;
    case 5:
    {
        word_suolue_display(30 + j * 240, 20 + 150, 40, 37, 18, 22);
    }
    break;
    case 2:
    {
        word_suolue_display(30 + j * 240, 230 + 150, 40, 37, 6, 9);
    }
    break;
    case 3:
    {
        word_suolue_display(30 + j * 240, 230 + 150, 40, 37, 10, 12);
    }
    break;
    case 6:
    {
        word_suolue_display(30 + j * 240, 230 + 150, 40, 37, 23, 26);
    }
    break;
    case 7:
    {
        word_suolue_display(30 + j * 240, 230 + 150, 40, 37, 27, 31);
    }
    break;
    default:
        break;
    }
}

// suolue_display
void suolue_display()
{
    int count_1 = 0;
    int count_2 = 0;
    FileNode *p = list_suolue->cur;
    lcd_draw_rectangle(0, 0, 480, 430, 0x0f0f0f);
    for (int i = 0; i < 4; i++)
    {
        printf("idnode--is:%d\n", p->i_node);
        if (i < 2)
        {
            bmp_display(p->pic_name, 30 + count_1 * 240, 20);
            // digit_display(p->i_node, 30 + 100 + count_1 * 240, 20 + 150);
            suolue_name(p->i_node, count_1);
            // display_digit(0x0f0f03, 30 + 100 + count_1 * 240, 20 + 150,p->i_node, 24, 37);
            count_1++;
        }
        else
        {
            bmp_display(p->pic_name, 30 + count_2 * 240, 230);
            suolue_name(p->i_node, count_2);
            // digit_display(p->i_node, 30 + 100 + count_2 * 240, 230 + 150);
            // display_digit(0x0f0f03, 30 + 100 + count_2 * 240, 230 + 150,p->i_node, 24, 37);
            count_2++;
        }
        p = p->next;
    }
}

// suolue_page_change
void *total_display(void *arg)
{

    pthread_t force_suolue_stop, current_tid;
    current_tid = pthread_self();
    printf("effect tid :%d--\n");
    pthread_create(&force_suolue_stop, NULL, FORCE_StoP, (void *)&current_tid);

    count = 'E';

    while (1)
    {

        if (count == 'E') // Only_f_One
        {
            printf("new_TIMING:%s\n", list_suolue->cur->pic_name);
            lcd_draw_rectangle(480, 0, 320, 430, 0x0f0f20);
            bmp_icon_display(left, 560, 60);
            bmp_icon_display(right, 560, 260);
            suolue_display();
        }
        count = 'C';

        int option_suolue = get_touch_suolue();
        printf("Option_SUOLUE is----:%d\n", option_suolue);

        switch (option_suolue)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        {
            join_new_for_detail(option_suolue);
            printf("joinis_TIMING:%s\n", list_suolue->cur->pic_name);
        }
        break;
        case 5:
        {
            printf("--5--test--if---\n");
            for (int i = 0; i < 4; i++)
            {
                list_suolue->cur = list_suolue->cur->next;
            }
            suolue_display();
        }
        break;
        case 6:
        {
            printf("--6--test--if---\n");
            for (int i = 0; i < 4; i++)
            {
                list_suolue->cur = list_suolue->cur->prev;
            }
            suolue_display();
        }
        break;
        default:
        {
            printf("--default--test--if---\n");
            continue;
        }
        break;
        }
        printf("swich_end_TIMING:%s\n", list_suolue->cur->pic_name);
    }
}

void join_new_for_detail(int option_suolue)
{
    FileNode *p = list_suolue->cur;
    for (int i = 0; i < option_suolue - 1; i++)
    {
        p = p->next;
    }
    printf("will--display:%s-----%d--\n", p->pic_name, p->i_node);

    pthread_t tid_detail;
    int status;
    int done_suolue = pthread_create(&tid_detail, NULL, detail_display, (void *)&(p->i_node));
    pthread_join(tid_detail, (void *)&status);
}

void *detail_display(void *arg)
{
    // pthread_t force_detail_stop, current_detail_tid;
    // current_detail_tid = pthread_self();
    // printf("circle tid :%d--\n");
    // pthread_create(&force_detail_stop, NULL, FORCE_StoP, (void *)&current_detail_tid);

    int ary = *((int *)arg);
    FileList *list_nation = search_pictures(nation_con[ary]);
    bmp_display(list_nation->first->pic_name, 0, 0);
    if (list_nation->cur != list_nation->first)
    {
        list_nation->cur == list_nation->first;
    }
    while (1)
    {
        if (thread_flag != 0)
        {
            printf("detail_global_exit--\n");
            pthread_exit(0);
        }
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
            count = 'E';
            printf("thread_detail exit\n");
            printf("exit_TIMING:%s\n", list_suolue->cur->pic_name);
            // list_suolue->cur = list_suolue->first;

            pthread_exit(0);
        }
    }
}

// exit_suolue
void *FORCE_StoP(void *arg)
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

// exit_suolue
void *FORCE_StoP_detail(void *arg)
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
    while (1)
    {
        // bmp_display(home, 375, 430);
        bmp_icon_display(icon_name[0], 375, 430);
        bmp_icon_display(icon_name[1], 90, 430);
        bmp_icon_display(icon_name[4], 230, 430);
    }
}

// global_exit
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
            thread_video_flag = 1;
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
            // sleep(2);
            thread_prevent_redefine_effect = 0;
            pthread_exit(0);
        }
    }
}

void line_shining(int x0, int y0, int w, int h, int color, int times)
{
    while (times--)
    {
        lcd_draw_rectangle(x0, y0, w, h, 0xffffff);
        usleep(340000);
        jpeg_effect_display(list_menu->first->pic_name, x0, y0, w + 50, h + 5);
        usleep(340000);
    }
}

void *word_effect(void *arg)
{
    int x0 = 0, y0 = 50;
    pthread_t force_stop, current_suolue_tid;
    current_suolue_tid = pthread_self();
    printf("effect tid :%d--\n");
    pthread_create(&force_stop, NULL, FStop_xc, (void *)&current_suolue_tid);

    while (1)
    {
        thread_prevent_redefine_effect = 1; // open_prevt
        int count = 0;
        line_shining(x0 + 230, y0, 2, 37, 0xffffff, 5);
        for (int i = 0; i < 8; i++)
        {
            hanzi_no_bk_display(0xf20201, x0 + 230 + count * 40, y0, 40, 37, hanzi_title[i]);
            lcd_draw_rectangle(x0 + 225 + (count + 1) * 40, y0, 2, 37, 0xffffff);
            usleep(340000);
            jpeg_effect_display(list_menu->first->pic_name, x0 + 225 + (count + 1) * 40, y0, 45, 37);
            count++;
        }
        // sleep(10);
        line_shining(x0 + 550, y0, 2, 37, 0xffffff, 5);
        count = 0;
        for (int i = 0; i <= 9; i++)
        {
            jpeg_effect_display(list_menu->first->pic_name, x0 + 552 - count * 40, y0, 45, 37);
            sleep(0.5);
            if (i < 9)
                lcd_draw_rectangle(x0 + 552 - count * 40, y0, 2, 37, 0xffffff);
            count++;
        }
    }
}

void *playmusic(void *arg)
{
    // divorce_xc

    pthread_detach(pthread_self());

    char music_buf[128] = {0};
    while (1)
    {
        if (thread_music_flag != 0)
        {
            continue;
        }
        system("killall -9 madplay"); // 保证别的madplay死掉
        sprintf(music_buf, "madplay -Q ./mp3/%d.mp3", music_i);
        printf("%s\n", music_buf);
        system(music_buf);
        music_i++;
        if (music_i > 3)
            music_i = 1;
    }
}

void Video_play()
{
    INIT_VIDEO(); // cancle_efect,initial_menu
    printf("----test1---\n");
    Video_thread(); // creat_scren_thread_to_control_video,and start_the_thread_video
}

void INIT_VIDEO()
{
    thread_music_flag = 1;
    thread_menu_flag = 1;
    thread_video_flag = 0;
    lcd_draw_rectangle(0, 0, 800, 430, 0x7c3672);
    lcd_draw_REBOX(3, 3, 641, 428, 3, 0xf1f1f1);
    bmp_icon_display(icon_name[9], 680, 50);
    bmp_icon_display(icon_name[10], 680, 150);
    bmp_icon_display(icon_name[10], 680, 290);
    bmp_icon_display(icon_name[10], 270, 150);
}

void Video_thread()
{

    pthread_t adin_video, testid;
    int done_advo = pthread_create(&adin_video, NULL, adin_Video, NULL);

    printf("---verify_id--if:%d--\n", done_advo);
    if (done_advo != 0)
    {
        printf("thread_music creation failed\n");
        exit(1);
    }
    printf("------test2---\n");
    pthread_join(adin_video, NULL);
}

void *adin_Video(void *arg)
{
    // if (thread_video_flag != 0)
    // {
    //     pthread_exit(0);
    // }

    pthread_t vstop, current_tid;
    current_tid = pthread_self();
    ary_video[0] = (int)current_tid;
    printf("---test3---effect tid :%d--\n", ary_video[0]);
    int done_vostop = pthread_create(&vstop, NULL, Video_stop, (void *)&current_tid);
    if (done_vostop != 0)
    {
        printf("Video_stop creation failed\n");
        exit(1);
    }

    int fd_1 = open("/home/china/1.fifo", O_RDWR);
    printf("--fd--is :%d\n", fd_1);
    if (fd_1 == -1)
    {
        perror("open fifo error");
        exit(1);
    }

    while (1)
    {
        int option_video = get_touch_video();
        printf("---video_option--:%d\n", option_video);
        switch (option_video)
        {
        case 1:
        {
            if (thread_prevent_redefine_video == 1)
            {
                continue;
            }
            pthread_t tid_video;
            int done_video = pthread_create(&tid_video, NULL, playvideo, NULL);
            if (done_video != 0)
            {
                printf("thread_video creation failed\n");
                exit(1);
            }
            thread_prevent_redefine_video = 1;
        }
        break;
        case 2:
        {
            const char *cmd = "pause\n";
            int ret = write(fd_1, cmd, strlen(cmd));
            printf("write cmd %d bytes \n", ret);
        }
        break;
        case 3:
        {
            system("killall -9 mplayer");
            video_i++;
            if (video_i > 3)
            {
                video_i = 1;
            }
            // thread_music_flag = !thread_music_flag;
            // thread_video_flag = !thread_video_flag;
        }
        break;
        default:
            break;
        }
    }
}

void *Video_stop(void *arg)
{
    printf("add-----if--\n");
    int stio_tid = *((int *)arg);
    while (1)
    {
        if (thread_video_flag != 0)
        {
            pthread_cancel(stio_tid);
            if (ary_video != 0)
            {
                pthread_cancel(ary_video[1]);
                printf("test---exit--from--this--\n");
            }

            system("killall -9 mplayer");

            ary_video[0] = 0;
            ary_video[1] = 0;
            // sleep(2);
            thread_prevent_redefine_video = 0; // close_safe
            pthread_exit(0);
        }
    }
}

void *playvideo(void *arg)
{
    pthread_t ct_id;
    ct_id = pthread_self();
    ary_video[1] = (int)ct_id;
    // divorce_xc
    pthread_detach(pthread_self());
    char video_buf[128] = {0};

    int fd_1 = open("/home/china/1.fifo", O_RDWR);
    printf("--fd--is :%d\n", fd_1);
    if (fd_1 == -1)
    {
        perror("open fifo error");
        exit(1);
    }
    while (1)
    {
        // if (thread_video_flag != 0)
        // {
        //     continue;
        // }
        // system("killall -9 mplayer"); // 保证别的madplay死掉
        const char *cmd = "pause\n";
        int ret = write(fd_1, cmd, strlen(cmd));
        printf("write cmd %d bytes \n", ret);
        sprintf(video_buf, "mplayer -slave -quiet -input  file=/home/china/1.fifo  -geometry  3:3 -zoom -x 640 -y 427  ./mp4/%d.mp4", video_i);
        printf("%s\n", video_buf);
        system(video_buf);
    }
}

void icon_effect_touch(int option)
{
    switch (option)
    {
    case 1:
    {
        lcd_draw_REBOX(220, 199, 80, 70, 5, 0x234122);
        jpeg_effect_display(list_menu->first->pic_name, 215, 194, 90, 90);
        usleep(75000);
        bmp_icon_display(icon_name[5], 220, 200);
    }
    break;
    case 2:
    {
        lcd_draw_REBOX(420, 200, 80, 70, 5, 0x234122);
        jpeg_effect_display(list_menu->first->pic_name, 415, 194, 90, 90);
        usleep(75000);
        bmp_icon_display(icon_name[5], 420, 200);
        bmp_icon_display(icon_name[6], 500, 210);
    }
    break;
    case 3:
    {
        lcd_draw_REBOX(223, 310, 70, 80, 1, 0x234122);
        jpeg_effect_display(list_menu->first->pic_name, 215, 304, 80, 90);
        usleep(75000);
        bmp_icon_display(icon_name[7], 220, 310);
    }
    break;
    case 4:
    {
        lcd_draw_REBOX(420, 310, 70, 80, 1, 0x234122);
        jpeg_effect_display(list_menu->first->pic_name, 415, 304, 80, 90);
        usleep(75000);
        bmp_icon_display(icon_name[8], 420, 310);
    }
    break;

    default:
        break;
    }
}