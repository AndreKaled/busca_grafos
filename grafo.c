#include "grafo.h"
#include <stdlib.h>

link novoNo(int destino, link prox){
    link a = malloc(sizeof(struct No));
    if(!a){
        printf("ERRO DE ALOCAÇÃO DE MEMORIA AO NO!\n");
        exit(1);
    }
    a->destino = destino;
    a->prox = prox;
    return a;
}

Grafo inicializarGrafo(int vertices){
    Grafo g = malloc(sizeof(grafo));
    if(!g){
        printf("ERRO DE ALOCAÇÃO DE MEMORIA AO GRAFO!\n");
        exit(1);
    }

    g->vertices = vertices;
    g->arcos = 0;
    g->conexoes = malloc(vertices * sizeof(link));
    if(!g->conexoes){
        printf("ERRO DE ALOCAÇÃO DE MEMORIA PARA CONEXÕES DO GRAFO!\n");
        free(g);
        exit(1);
    }

    for(int v = 0; v < vertices; v++)
        g->conexoes[v] = NULL;

    g->ultimosNos = malloc(vertices * sizeof(link));
    if (!g->ultimosNos) {
        printf("ERRO DE ALOCACAO DE MEMORIA PARA ULTIMOS NOS DO GRAFO!\n");
        free(g->conexoes);
        free(g);
        exit(1);
    }

    for(int v = 0; v < vertices; v++) {
        g->ultimosNos[v] = NULL;
    }

    g->visitado = malloc(vertices*sizeof(int));
    if(!g->visitado){
        printf("ERRO DE ALOCAÇÃO DE MEMORIA PARA O VETOR DE VISITADOS!\n");
        for (int v = 0; v < vertices; v++) {
            link atual = g->conexoes[v];
            while (atual != NULL) {
                link tmp = atual;
                atual = atual->prox;
                free(tmp);
            }
        }
        free(g->conexoes);
        free(g);
        exit(1);
    }

    for(int i = 0; i < vertices; i++){
        g->visitado[i] = 0;
    }

    return g;
}

void insereArcoNoGrafo(Grafo g, int v, int w, char direcionado){
    if(!g || v < 0 || v >= g->vertices || w < 0 || w >= g->vertices){
        printf("ERRO DE VERTICE INVALIDO OU GRAFO NULO AO INSERIR ARCO (%d, %d)!\n",
        v,w);
        exit(1);
    }

    for(link a = g->conexoes[v]; a != NULL; a = a->prox)
        if(a->destino == w) return; //arco ja existe
    
    link novo = novoNo(w, NULL);
    if(!g->conexoes[v]){
        g->conexoes[v] = novo;
        g->ultimosNos[v] = novo;
    }else{
        g->ultimosNos[v]->prox = novo;
        g->ultimosNos[v] = novo;
    }
    g->arcos++;
    
    if(!direcionado){
        for(link a = g->conexoes[w]; a != NULL; a = a->prox)
            if(a->destino == v) return; //arco ja existe

        link novo = novoNo(v, NULL);
        if(!g->conexoes[w]){
            g->conexoes[w] = novo;
            g->ultimosNos[w] = novo;
        }else{
            g->ultimosNos[w]->prox = novo;
            g->ultimosNos[w] = novo;
        }
        g->arcos++;
    }
}

void inicializarVisitados(Grafo g){
    if(!g || !g->visitado){
        printf("ERRO GRAFO OU VETOR DE VISITADOS NULO");
        exit(1);
    }
    for(int i = 0; i < g->vertices; i++){
        g->visitado[i] = 0;
    }
}

void dfsVisita(Grafo g, int v){
    g->visitado[v] = 1;
    printf("%d ",v);
    link vizinhos;
    for(vizinhos = g->conexoes[v]; vizinhos; vizinhos = vizinhos->prox){
        int w = vizinhos->destino; //w é vizinho de v
        if(g->visitado[w] == 0)
            dfsVisita(g, w);
    }
}

void dfs(Grafo g, int verticeInicial){
    if (g == NULL || verticeInicial < 0 || verticeInicial >= g->vertices) {
        printf("ERRO DE GRAFO NULO OU VERTICE INVALIDO.\n");
        return;
    }
    inicializarVisitados(g);
    printf("DFS: ");
    dfsVisita(g, verticeInicial);
    printf("\n");
}

void destruirGrafo(Grafo g) {
    if (g == NULL) return;

    for (int i = 0; i < g->vertices; i++) {
        link atual = g->conexoes[i];
        while (atual != NULL) {
            link tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->conexoes);
    free(g->ultimosNos);
    free(g->visitado);
    free(g);  
}