#include <stdlib.h>
#include "list.h"

void addList(List** list, int dado) {
    List* novo = (List*) malloc(sizeof(List));
    novo->dado = dado;
    novo->prox = NULL;

    if (*list == NULL) {
        *list = novo;
        return;
    }

    List* atual = *list;
    while (atual->prox) atual = atual->prox;
    atual->prox = novo;
}