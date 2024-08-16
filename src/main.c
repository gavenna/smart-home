

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

int terminate = 0; // 进程(程序)退出的标记
                   //  terminate = 1 进程要退出啦
                   //  terminate = 0 进程继续
int flags == 0;

int main(int argc, char *argv[])
{
    lcd_open();
    printf("action!\n");

    FileList *list = search_pictures(argv[1]);
    print_FistList(list);

    MENU_INIT(list);

    pthread_t tid;
    pthread_create(&tid, NULL, pic_circle, NULL);

    int option;
    while (!terminate)
    {
        option = get_touch();

        printf("option = %d\n", option);
        switch (option)
        {
        case 1:
            MENU_INIT(list);
            break;
        case 2:
            pic_circle(list);
            break;

        default:
            break;
        }
        MENU_INIT(list);
    }

    lcd_close();

    return 0;
}
