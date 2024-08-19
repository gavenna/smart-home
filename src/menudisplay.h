#ifndef __MENUDISPLAY_H__
#define __MENUDISPLAY_H__

// 图片目录索引
static char *nation_con[6] = {"storepic/CN", "storepic/USA", "storepic/UK", "storepic/UN", "storepic/MDV", "storepic/SWE"};

void MENU_INIT(void);

void *pic_circle(void *arg);

void *total_display(void *arg);

// void *suolue_goto_deep(void *arg);

// 缩略显示
void suolue_display();

// icon show
void *show_icon(void *arg);

void *global_stop(void *arg);

void join_new_for_detail(int option_suolue);

void *detail_display(void *arg);

void *show_free(void *arg);

void *word_effect(void *arg);

void *FStop_xc(void *arg);

void *FORCE_SP_SUOLUE(void *arg);

void *playmusic(void *arg);

void daohan_display();

#endif