#include "relatorio.h"

FILE* iniciaRelatorio(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo de relatorio.\n");
        return NULL;
    }

    fprintf(arquivo, "*******************************************************************\n");
    fprintf(arquivo, "** **\n");
    fprintf(arquivo, "** RELATORIO - TRABALHO PRATICO 4 - GRAFOS              **\n");
    fprintf(arquivo, "** Algoritmos e Estruturas de Dados 2 - UFAM/ICOMP        **\n");
    fprintf(arquivo, "** **\n");
    fprintf(arquivo, "*******************************************************************\n\n");
    fprintf(arquivo, "Equipe:\n- Kaua Amorim\n- Carlos Henrick\n- Adrian Batista\n- Andre Kaled\n\n");
    fprintf(arquivo, "-------------------------------------------------------------------\n\n");
    
    return arquivo;
}

void escreveSecaoDemonstracao(FILE* stream, Grafo* g_pequeno, Grafo* g_hamiltoniano) {
    if (stream == NULL) return;

    fprintf(stream, "===================================================================\n");
    fprintf(stream, " PARTE 1: DEMONSTRACAO COM GRAFO PEQUENO (V=%d)\n", g_pequeno->num_vertices);
    fprintf(stream, "===================================================================\n\n");
    
    fprintf(stream, "[Questao 1] Apresentacao Visual do Grafo (Lista de Adjacencia):\n");
    mostraGrafo(g_pequeno, stream);

    fprintf(stream, "\n[Questao 2] Exemplo de Busca em Largura (BFS):\n");
    buscaEmLarguraGrafo(g_pequeno, 0, stream);

    fprintf(stream, "\n[Questao 3] Exemplo de Busca em Profundidade (DFS):\n");
    buscaEmProfundidadeGrafo(g_pequeno, 0, stream);

    fprintf(stream, "\n[Questao 5] Exemplo de Deteccao de Ciclo:\n");
    if (temCicloGrafo(g_pequeno)) {
        fprintf(stream, "Resultado: O grafo de teste POSSUI ciclo(s).\n");
    } else {
        fprintf(stream, "Resultado: O grafo de teste NAO possui ciclos.\n");
    }

    fprintf(stream, "\n[Questao 4] Exemplo de Busca por Todos os Caminhos (Hamiltonianos):\n");
    fprintf(stream, "Um novo grafo foi criado para garantir a existencia de caminhos Hamiltonianos:\n");
    mostraGrafo(g_hamiltoniano, stream);
    encontraTodosOsCaminhosGrafo(g_hamiltoniano, 0, stream);
}


void escreveSecaoAnalise(FILE* stream, ResultadosAnalise* resultados, int num_resultados, int num_vertices, int num_execucoes) {
    if (stream == NULL) return;

    fprintf(stream, "\n\n===================================================================\n");
    fprintf(stream, " PARTE 2: ANALISE DE DESEMPENHO (BFS vs DFS)\n");
    fprintf(stream, "===================================================================\n\n");
    fprintf(stream, "Configuracao: V = %d vertices | Media de %d execucoes por teste.\n\n", num_vertices, num_execucoes);

    for (int i = 0; i < num_resultados; i++) {
        fprintf(stream, "--- Testando Conectividade: %.0f%% ---\n", resultados[i].conectividade * 100);
        fprintf(stream, "Tempo medio de execucao (BFS): %f segundos.\n", resultados[i].tempo_medio_bfs);
        fprintf(stream, "Tempo medio de execucao (DFS): %f segundos.\n", resultados[i].tempo_medio_dfs);
        fprintf(stream, "-----------------------------------------------------\n");
    }
}


void escreveSecaoDiscussao(FILE* stream) {
    if (stream == NULL) return;

    fprintf(stream, "\n\n===================================================================\n");
    fprintf(stream, " PARTE 3: DISCUSSAO E ANALISE DOS RESULTADOS\n");
    fprintf(stream, "===================================================================\n\n");
    
    fprintf(stream, "[Relacao entre Grau de Conectividade e Tempo de Execucao]\n\n");
    fprintf(stream, "A complexidade de tempo tanto da Busca em Largura (BFS) quanto da Busca em Profundidade (DFS) e O(V + A), onde V e o numero de vertices e A e o numero de arestas. Ao manter V constante e aumentar o grau de conectividade, estamos essencialmente aumentando o numero de arestas (A).\n\n");
    fprintf(stream, "Observa-se nos testes de desempenho que o tempo de execucao de ambos os algoritmos aumenta de forma aproximadamente linear com o aumento da conectividade. Isso e esperado, pois com mais arestas, os algoritmos precisam explorar mais vizinhos para cada vertice, resultando em mais operacoes. Para grafos esparsos (baixa conectividade), o tempo e dominado por O(V), mas a medida que o grafo se torna mais denso, o termo O(A) se torna predominante.\n\n");
    
    fprintf(stream, "[Diferenca de Uso de Memoria entre BFS e DFS]\n\n");
    fprintf(stream, "Embora a complexidade de espaco assintotica de ambos seja O(V), a estrutura de dados que utilizam e a forma como exploram o grafo levam a diferencas praticas significativas no uso de memoria:\n\n");
    fprintf(stream, "* Busca em Largura (BFS): Utiliza uma FILA para armazenar os vertices a serem visitados. No pior caso (um grafo em formato de estrela, onde um vertice central esta conectado a todos os outros), a fila pode precisar armazenar quase todos os V vertices simultaneamente. Portanto, a memoria da BFS tende a ser proporcional a largura maxima do grafo.\n\n");
    fprintf(stream, "* Busca em Profundidade (DFS): Utiliza a PILHA de recursao (ou uma pilha explicita) para o backtracking. A memoria necessaria e proporcional a profundidade maxima do caminho explorado. No pior caso (um grafo degenerado em uma longa linha), a pilha de recursao pode conter todos os V vertices. No entanto, em grafos mais 'largos' e menos 'profundos', o pico de uso de memoria do DFS pode ser consideravelmente menor que o da BFS.\n\n");
    fprintf(stream, "Conclusao da memoria: Nao ha um vencedor universal. A BFS e mais 'gastadora' de memoria em grafos largos e rasos, enquanto a DFS pode ser mais 'gastadora' em grafos estreitos e profundos. Na pratica, para grafos muito grandes e densos, o uso de memoria da BFS pode se tornar um fator limitante mais rapidamente do que o da DFS.\n");
}


void finalizaRelatorio(FILE* stream) {
    if (stream != NULL) {
        fclose(stream);
    }
}