#ifndef __COMMON_H__
#define __COMMON_H__

#define TRUE 1
#define FALSE 0
#define MAX(a,b) ((a)>(b)?(a):(b))
typedef enum STATUS {
    OK,
    ERROR,
    INFEASIBLE,
    OVERFLOW,
    INVALID_ARGUMENT
} Status;

#define STACK_INIT_LEN 20

typedef char bool;

typedef int ElemType;
typedef struct bintree {
    ElemType data;
    struct bintree *L;
    struct bintree *R;
} BinTree;

typedef struct edge {
    int v1,v2;
    int len;
} Edge;

typedef struct bintree *   SElemType;


typedef struct {
    SElemType base[STACK_INIT_LEN];
    unsigned int size;
} LinerStack;

typedef struct {
    SElemType	*data;
    int head;
    int rear;
    int len;

} queue;


#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K" //or "\e[1K\r"

#define FONT_COLOR L_CYAN
#define HEAD_COLOR YELLOW
//#define COLORTEXT
#endif // !__COMMON_H__
