#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"
#include "relatorio.h"

/*
 =================================================================
 ||            CONFIGURACOES PARA TESTES DO USUARIO             ||
 =================================================================
*/
#define NOME_ARQUIVO_RELATORIO "relatorio_trabalho4.txt"

// 1. Configuracao para o grafo de demonstracao geral (Questoes 1, 2, 3, 5)
#define V_PEQUENO 5

// 2. Configuracao Questao 4 (Todos os Caminhos) 
#define V_CAMINHOS_HAMILTONIANOS 4

// 3. Configuracao para a analise de desempenho
#define V_ANALISE 500
#define NUM_EXECUCOES 10
const double CONECTIVIDADES[] = {0.10, 0.25, 0.50, 0.75, 1.00};


/*
 =================================================================
 ||              FUNCOES AUXILIARES PARA TESTES                 ||
 =================================================================
*/

/* Gera um grafo conectado para os testes. */
Grafo* geraGrafoConexo(int num_vertices, double conectividade) {
    Grafo *g = criaGrafo(num_vertices);
    long max_arestas = (long)num_vertices * (num_vertices - 1) / 2;
    long target_arestas = (long)(conectividade * max_arestas);

    // Garante conectividade
    for (int i = 0; i < num_vertices - 1; i++) {
        insereArestaGrafoNaoDirecionado(g, i, i + 1);
    }
    if (num_vertices > 1) {
        insereArestaGrafoNaoDirecionado(g, num_vertices - 1, 0);
    }
    
    // Adiciona arestas aleatórias
    while(g->num_arestas / 2 < target_arestas && g->num_arestas / 2 < max_arestas) {
        Vertice u = rand() % num_vertices;
        Vertice v = rand() % num_vertices;
        if (u != v) {
            insereArestaGrafoNaoDirecionado(g, u, v);
        }
    }
    return g;
}

/* Orquestra a execução da demonstração com grafos pequenos. */
void executaDemonstracao(FILE* stream) {
    // Grafo para demonstrações gerais (BFS, DFS, Ciclo) usa V_PEQUENO
    Grafo *g_pequeno = criaGrafo(V_PEQUENO);
    insereArestaGrafoNaoDirecionado(g_pequeno, 0, 1);
    insereArestaGrafoNaoDirecionado(g_pequeno, 1, 2);
    insereArestaGrafoNaoDirecionado(g_pequeno, 2, 3);
    insereArestaGrafoNaoDirecionado(g_pequeno, 3, 0);
    if (V_PEQUENO > 4) insereArestaGrafoNaoDirecionado(g_pequeno, 1, 4);

    // Grafo para a Questão 4 (Todos os Caminhos) usa a onstante V_CAMINHOS_HAMILTONIANOS
    Grafo *g_hamiltoniano = criaGrafo(V_CAMINHOS_HAMILTONIANOS);
    insereArestaGrafoNaoDirecionado(g_hamiltoniano, 0, 1);
    insereArestaGrafoNaoDirecionado(g_hamiltoniano, 1, 2);
    insereArestaGrafoNaoDirecionado(g_hamiltoniano, 2, 3);
    // Adicionar mais arestas para criar múltiplos caminhos
    insereArestaGrafoNaoDirecionado(g_hamiltoniano, 3, 0); 
    insereArestaGrafoNaoDirecionado(g_hamiltoniano, 1, 3);
    
    // Passa os dois grafos para o relatório
    escreveSecaoDemonstracao(stream, g_pequeno, g_hamiltoniano);

    liberaGrafo(g_pequeno);
    liberaGrafo(g_hamiltoniano);
}


/* Orquestra a execução da análise de desempenho. */
void executaAnaliseDesempenho(FILE* stream) {
    int num_conectividades = sizeof(CONECTIVIDADES) / sizeof(double);
    ResultadosAnalise* resultados = (ResultadosAnalise*)malloc(num_conectividades * sizeof(ResultadosAnalise));

    for (int i = 0; i < num_conectividades; i++) {
        double conectividade_atual = CONECTIVIDADES[i];
        double tempo_total_bfs = 0.0;
        double tempo_total_dfs = 0.0;
        
        for (int j = 0; j < NUM_EXECUCOES; j++) {
            Grafo *g_teste = geraGrafoConexo(V_ANALISE, conectividade_atual);
            clock_t inicio, fim;

            inicio = clock();
            buscaEmLarguraGrafo(g_teste, 0, NULL);
            fim = clock();
            tempo_total_bfs += ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            inicio = clock();
            buscaEmProfundidadeGrafo(g_teste, 0, NULL);
            fim = clock();
            tempo_total_dfs += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            
            liberaGrafo(g_teste);
        }
        
        resultados[i].conectividade = conectividade_atual;
        resultados[i].tempo_medio_bfs = tempo_total_bfs / NUM_EXECUCOES;
        resultados[i].tempo_medio_dfs = tempo_total_dfs / NUM_EXECUCOES;
    }

    escreveSecaoAnalise(stream, resultados, num_conectividades, V_ANALISE, NUM_EXECUCOES);
    free(resultados);
}


/*
 =================================================================
 ||                     PONTO DE ENTRADA                        ||
 =================================================================
*/

int main() {
    FILE* arquivo_relatorio;
    
    srand(time(NULL));

    // 1. Iniciar Relatório
    arquivo_relatorio = iniciaRelatorio(NOME_ARQUIVO_RELATORIO);
    if (arquivo_relatorio == NULL) {
        return 1;
    }

    // 2. Executar testes e escrever
    executaDemonstracao(arquivo_relatorio);
    executaAnaliseDesempenho(arquivo_relatorio);
    escreveSecaoDiscussao(arquivo_relatorio);

    // 3. Finalizar Relatório
    finalizaRelatorio(arquivo_relatorio);
    
    printf("Relatorio '%s' gerado com sucesso!\n", NOME_ARQUIVO_RELATORIO);

    return 0;
}