#include "grafo.h"
#include <string.h>

/* ... (criaNoLista, criaGrafo, insereArcoGrafo, insereArestaGrafoNaoDirecionado, liberaGrafo - INALTERADAS) ... */

// Implementação das funções inalteradas...

static No* criaNoLista(Vertice w, No *proximo_no) {
    No *novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro: Falha na alocacao de memoria para o no.\n");
        exit(1);
    }
    novo_no->vertice_adjacente = w;
    novo_no->proximo = proximo_no;
    return novo_no;
}

Grafo* criaGrafo(int num_vertices) {
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    Vertice v;
    
    if (g == NULL) {
        printf("Erro: Falha na alocacao de memoria para o grafo.\n");
        exit(1);
    }
    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->lista_adj = (No**)malloc(num_vertices * sizeof(No*));
    if (g->lista_adj == NULL) {
        printf("Erro: Falha na alocacao de memoria para a lista de adjacencia.\n");
        exit(1);
    }
    for (v = 0; v < num_vertices; ++v) {
        g->lista_adj[v] = NULL;
    }
    return g;
}

void insereArcoGrafo(Grafo *g, Vertice v, Vertice w) {
    No *no_atual;
    for (no_atual = g->lista_adj[v]; no_atual != NULL; no_atual = no_atual->proximo) {
        if (no_atual->vertice_adjacente == w) return;
    }
    g->lista_adj[v] = criaNoLista(w, g->lista_adj[v]);
    g->num_arestas++;
}

void insereArestaGrafoNaoDirecionado(Grafo *g, Vertice v, Vertice w) {
    insereArcoGrafo(g, v, w);
    insereArcoGrafo(g, w, v);
}

void liberaGrafo(Grafo *g) {
    int v;
    if (g == NULL) return;

    for (v = 0; v < g->num_vertices; ++v) {
        No *no_atual = g->lista_adj[v];
        while (no_atual != NULL) {
            No *no_temporario = no_atual;
            no_atual = no_atual->proximo;
            free(no_temporario);
        }
    }
    free(g->lista_adj);
    free(g);
}

// ALTERADA
void mostraGrafo(Grafo *g, FILE* stream) {
    if (stream == NULL) return; // Se não houver stream, não imprime
    Vertice v;
    No *no_atual;
    fprintf(stream, "Grafo (V=%d, A=%d):\n", g->num_vertices, g->num_arestas);
    for (v = 0; v < g->num_vertices; ++v) {
        fprintf(stream, "%2d:", v);
        for (no_atual = g->lista_adj[v]; no_atual != NULL; no_atual = no_atual->proximo) {
            fprintf(stream, " %2d", no_atual->vertice_adjacente);
        }
        fprintf(stream, "\n");
    }
}

// ALTERADA
void buscaEmLarguraGrafo(Grafo *g, Vertice inicio, FILE* stream) {
    // ... (lógica interna da BFS inalterada) ...
    int *pais = (int*)malloc(g->num_vertices * sizeof(int));
    bool *visitado = (bool*)malloc(g->num_vertices * sizeof(bool));
    Vertice *fila = (Vertice*)malloc(g->num_vertices * sizeof(Vertice));
    int cabeca_fila = 0, cauda_fila = 0;
    int i;
    Vertice v;
    No *no_adjacente;
    for (i = 0; i < g->num_vertices; i++) {
        pais[i] = -1;
        visitado[i] = false;
    }
    visitado[inicio] = true;
    pais[inicio] = inicio;
    fila[cauda_fila++] = inicio;
    while (cabeca_fila != cauda_fila) {
        v = fila[cabeca_fila++];
        for (no_adjacente = g->lista_adj[v]; no_adjacente != NULL; no_adjacente = no_adjacente->proximo) {
            Vertice w = no_adjacente->vertice_adjacente;
            if (!visitado[w]) {
                visitado[w] = true;
                pais[w] = v;
                fila[cauda_fila++] = w;
            }
        }
    }

    if (stream != NULL) {
        fprintf(stream, "Iniciando BFS a partir de %d...\n", inicio);
        fprintf(stream, "Arvore de busca em largura (formato: pai->filho):\n");
        for(i = 0; i < g->num_vertices; i++) {
            if(pais[i] != -1 && pais[i] != i) {
                fprintf(stream, "(%d->%d) ", pais[i], i);
            }
        }
        fprintf(stream, "\n");
    }

    free(pais);
    free(visitado);
    free(fila);
}


// As funções a seguir também devem ser alteradas para aceitar o stream
// e usar fprintf em vez de printf.

static int contador_visita_dfs;
static int *sequencia_visitados_dfs;

static void dfsRecursiva(Grafo *g, Vertice v, bool visitado[]) {
    No *no_adjacente;
    visitado[v] = true;
    sequencia_visitados_dfs[contador_visita_dfs++] = v; 
    
    for (no_adjacente = g->lista_adj[v]; no_adjacente != NULL; no_adjacente = no_adjacente->proximo) {
        Vertice w = no_adjacente->vertice_adjacente;
        if (!visitado[w]) {
            dfsRecursiva(g, w, visitado);
        }
    }
}

void buscaEmProfundidadeGrafo(Grafo *g, Vertice inicio, FILE* stream) {
    bool *visitado = (bool*)calloc(g->num_vertices, sizeof(bool));
    Vertice v;
    int i;

    sequencia_visitados_dfs = (int*)malloc(g->num_vertices * sizeof(int));
    contador_visita_dfs = 0;

    dfsRecursiva(g, inicio, visitado);
    
    for(v = 0; v < g->num_vertices; v++){
        if(!visitado[v]){
            dfsRecursiva(g, v, visitado);
        }
    }

    if (stream != NULL) {
        fprintf(stream, "Iniciando DFS a partir de %d...\n", inicio);
        fprintf(stream, "Sequencia de vertices visitados: ");
        for (i = 0; i < contador_visita_dfs; i++) {
            fprintf(stream, "%d ", sequencia_visitados_dfs[i]);
        }
        fprintf(stream, "\n");
    }

    free(visitado);
    free(sequencia_visitados_dfs);
}


static int contador_caminho;

static void imprimeCaminho(int caminho[], int tam_caminho, FILE* stream) {
    int i;
    fprintf(stream, "Caminho %d: ", ++contador_caminho);
    for (i = 0; i < tam_caminho; i++) {
        fprintf(stream, "%d ", caminho[i]);
    }
    fprintf(stream, "\n");
}

static void encontraTodosOsCaminhosRecursiva(Grafo *g, Vertice u, bool visitado[], int caminho[], int indice_caminho, FILE* stream) {
    No *no_adjacente;
    visitado[u] = true;
    caminho[indice_caminho] = u;
    indice_caminho++;

    if (indice_caminho == g->num_vertices) {
        imprimeCaminho(caminho, indice_caminho, stream);
    } else {
        for (no_adjacente = g->lista_adj[u]; no_adjacente != NULL; no_adjacente = no_adjacente->proximo) {
            Vertice v = no_adjacente->vertice_adjacente;
            if (!visitado[v]) {
                encontraTodosOsCaminhosRecursiva(g, v, visitado, caminho, indice_caminho, stream);
            }
        }
    }
    
    indice_caminho--;
    visitado[u] = false;
}

void encontraTodosOsCaminhosGrafo(Grafo *g, Vertice inicio, FILE* stream) {
    if (stream == NULL) return;
    
    bool *visitado = (bool*)calloc(g->num_vertices, sizeof(bool));
    int *caminho = (int*)malloc(g->num_vertices * sizeof(int));
    contador_caminho = 0;

    fprintf(stream, "Procurando todos os caminhos a partir de %d que visitam todos os vertices:\n", inicio);
    encontraTodosOsCaminhosRecursiva(g, inicio, visitado, caminho, 0, stream);

    if (contador_caminho == 0) {
        fprintf(stream, "Nenhum caminho Hamiltoniano encontrado a partir do vertice %d.\n", inicio);
    }

    free(visitado);
    free(caminho);
}

// A função temCicloGrafo não foi alterada pois não imprimia nada.
bool temCicloRecursiva(Grafo *g, Vertice u, bool visitado[], int pai) {
    No *no_adjacente;
    visitado[u] = true;

    for (no_adjacente = g->lista_adj[u]; no_adjacente != NULL; no_adjacente = no_adjacente->proximo) {
        Vertice v = no_adjacente->vertice_adjacente;
        if (!visitado[v]) {
            if (temCicloRecursiva(g, v, visitado, u))
                return true;
        } else if (v != pai) {
            return true;
        }
    }
    return false;
}

bool temCicloGrafo(Grafo *g) {
    bool *visitado = (bool*)calloc(g->num_vertices, sizeof(bool));
    int u;
    
    for (u = 0; u < g->num_vertices; u++) {
        if (!visitado[u]) {
            if (temCicloRecursiva(g, u, visitado, -1)) {
                free(visitado);
                return true;
            }
        }
    }
    free(visitado);
    return false;
}