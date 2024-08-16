#include "bmp.h"
#include "hanzi.h"
#include "filelist.h"

void MENU_INIT(FileList *list)
{
    // background
    bmp_display(list->cur->pic_name, 494, 0);
    // message_show
    word_cicle_display(500, 100, 40, 37, 0, 3);

    word_cicle_display(500, 200, 40, 37, 0, 3);

    word_cicle_display(500, 300, 40, 37, 0, 3);
}

void pic_circle(FileList *list)
{
    while (!terminate)
    {
        bmp_display(list->cur->pic_name, 0, 0);
        change_to_next_pictures(list);
        sleep(1);
        if ()
    }
}