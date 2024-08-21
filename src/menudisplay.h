#ifndef __MENUDISPLAY_H__
#define __MENUDISPLAY_H__

// 图片目录索引
static char *nation_con[8] = {"storepic/CN", "storepic/USA", "storepic/BD", "storepic/ERIC", "storepic/BLWY", "storepic/AHL", "storepic/RUSSIA", "storepic/ROMA"};

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

void *word_effect(void *arg);

void *FStop_xc(void *arg);

void *FORCE_StoP(void *arg);

void *Video_stop(void *arg);

void *playmusic(void *arg);

void *playvideo(void *arg);

void *adin_Video(void *arg);

void daohan_display();

void icon_effect_touch(int option);

void Video_thread();

void Video_play();

void INIT_VIDEO();

#endif