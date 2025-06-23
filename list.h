#ifndef LIST_H
#define LIST_H

typedef struct List{
    int dado;
    struct List* prox;
}List;

void addList(List** list, int dado);
#endif