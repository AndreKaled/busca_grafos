#include "grafo.h"
#include <stdlib.h>

link novoNo(int destino, link prox){
    link a = malloc(sizeof(struct No));
    a->destino = destino;
    a->prox = prox;
    return a;
}

Grafo initGrafo(int vertices){
    Grafo g = malloc(sizeof(grafo));
    g->vertices = vertices;
    g->arcos = 0;
    g->conexoes = malloc(vertices * sizeof(link));

    for(int v = 0; v < vertices; v++)
        g->conexoes[v] = NULL;
    return g;
}

void insereArcoNoGrafo(Grafo g, int v, int w){
    for(link a = g->conexoes[v]; a != NULL; a = a->prox)
        if(a->destino == w) return;
    g->conexoes[v] = novoNo(w, g->conexoes[v]);
    g->arcos++;
}