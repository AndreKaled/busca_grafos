#ifndef RELATORIO_H
#define RELATORIO_H

#include <stdio.h>
#include "grafo.h"

typedef struct {
    double conectividade;
    double tempo_medio_bfs;
    double tempo_medio_dfs;
} ResultadosAnalise;


/* === Funcoes para Montagem do Relatorio === */

FILE* iniciaRelatorio(const char* nome_arquivo);

void escreveSecaoDemonstracao(FILE* stream, Grafo* g_pequeno, Grafo* g_hamiltoniano);

void escreveSecaoAnalise(FILE* stream, ResultadosAnalise* resultados, int num_resultados, int num_vertices, int num_execucoes);

void escreveSecaoDiscussao(FILE* stream);

void finalizaRelatorio(FILE* stream);


#endif 