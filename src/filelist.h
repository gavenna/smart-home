
#ifndef __FILELIST_H__
#define __FILELIST_H__

// "数据结点"
typedef struct FileNode
{
    char pic_name[512];
    int i_node;
    struct FileNode *next;
    struct FileNode *prev;
} FileNode;

// "头结点"
typedef struct FileList
{
    FileNode *first;
    FileNode *last;

    FileNode *cur; // 指向“当前显示的图片结点”
    // ...
} FileList;

/*
    search_pictures:在一个指定的目录下，搜索图片文件
    @path:指定的搜索目录
    返回值：
        把搜索到的图片文件名，构造一个“FileList”的链表
*/
FileList *search_pictures(const char *path);

FileList *create_FileList(void);

void print_FistList(FileList *list);

void change_to_next_pictures(FileList *list);

void make_inode(FileList *list);
#endif