#include "grafo.h"
#include <stdlib.h>

link novoNo(int vertices, link prox){
    link a = mallloc(sizeof(struct No));
    a->vertices = vertices;
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
        if(a->vertices = w) return;
    g->conexoes[v] = novoNo(w, g->conexoes[v]);
    g->arcos++;
}