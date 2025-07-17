#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Defines e Structs */

typedef int Vertice;

typedef struct No {
    Vertice vertice_adjacente;
    struct No *proximo;
} No;

typedef struct {
    int num_vertices;
    int num_arestas;
    No **lista_adj;
} Grafo;

/* Operações do Grafo */

Grafo* criaGrafo(int num_vertices);
void insereArcoGrafo(Grafo *g, Vertice v, Vertice w);
void insereArestaGrafoNaoDirecionado(Grafo *g, Vertice v, Vertice w);
void liberaGrafo(Grafo *g);
// A função agora recebe um stream para onde escrever (ex: stdout ou um ficheiro)
void mostraGrafo(Grafo *g, FILE* stream);


/* Algoritmos de Busca */

// As funções de busca agora recebem um stream para imprimir os resultados
void buscaEmLarguraGrafo(Grafo *g, Vertice inicio, FILE* stream);
void buscaEmProfundidadeGrafo(Grafo *g, Vertice inicio, FILE* stream);


/* Funções Específicas do Trabalho */

bool temCicloGrafo(Grafo *g);
void encontraTodosOsCaminhosGrafo(Grafo *g, Vertice inicio, FILE* stream);

#endif // GRAFO_H