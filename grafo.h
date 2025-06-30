#ifndef GRAFO_H
#define GRAFO_H

/** 
 * Base: https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html 
 * */

typedef struct No *link;

typedef struct No{
    int destino; // pelo que entendi, isso pode ser trocado para TipoDado depois
    link prox;
}No;

typedef struct grafo{
    int vertices;
    int arcos;
    link *conexoes;
}grafo;

typedef struct grafo *Grafo;

static int num[1000];

/* Recebe um vertice e o endereço próx do no, retorna o novo no que aponta 
para o prox passado no argumento (no.dado e no->prox->prox...)*/
link novoNo(int vertices, link prox);

Grafo initGrafo(int vertices);

/* g é o grafo, v é a posição do vertice na lista, e w é a qnt 
de vertices que tem o nó
direcionado indica se a inserção é direcionada ou nao, para nao
direcionada, deve receber valor 0*/
void insereArcoNoGrafo(Grafo g, int v, int w, char direcionado);

void bfs(Grafo g, int v);
#endif