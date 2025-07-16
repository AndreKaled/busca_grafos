#include "grafo.h"
#include <stdlib.h>
#include <time.h>

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

void dfsVisita(Grafo g, int v, char imprimir){
    g->visitado[v] = 1;
    if(imprimir)
        printf("%d ",v);
    link vizinhos;
    for(vizinhos = g->conexoes[v]; vizinhos; vizinhos = vizinhos->prox){
        int w = vizinhos->destino; //w é vizinho de v
        if(g->visitado[w] == 0)
            dfsVisita(g, w, imprimir);
    }
}

void dfs(Grafo g, int verticeInicial){
    if (g == NULL || verticeInicial < 0 || verticeInicial >= g->vertices) {
        printf("ERRO DE GRAFO NULO OU VERTICE INVALIDO.\n");
        return;
    }
    inicializarVisitados(g);
    printf("DFS: ");
    dfsVisita(g, verticeInicial, 1);
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

void encontrarCaminhosAux(Grafo g, int u, int *caminhoAtual, int nivel, int *visitadoNoCaminho, int *numCaminhos){
    caminhoAtual[nivel] = u;
    visitadoNoCaminho[u] = 1;
    if(nivel == g->vertices -1){
        int todosVisitados = 1;
        for(int i = 0; i < g->vertices; i++){
            if(visitadoNoCaminho[i] == 0){
                todosVisitados = 0;
                break;
            }
        }
        if(todosVisitados){
            (*numCaminhos)++;
            printf("Caminho %d: ", *numCaminhos);
            for(int i = 0; i <= nivel; i++){
                printf("%d%s", caminhoAtual[i], (i == nivel) ? "" : " -> ");
            }
            printf("\n");
        }
    } else {
        link adj = g->conexoes[u];
        while(adj != NULL){
            int v = adj->destino;
            if(visitadoNoCaminho[v] == 0)
                encontrarCaminhosAux(g,v,caminhoAtual,nivel+1,visitadoNoCaminho, numCaminhos);
            adj = adj->prox;
        }
    }

    //marca como nao visitado para backtracking
    visitadoNoCaminho[u] = 0;
}

void encontrarTodosCaminhos(Grafo g, int verticeInicial){
    if(g == NULL || verticeInicial < 0 || verticeInicial >=g->vertices){
        printf("ERRO DE GRAFO NULO OU VERTICE FORA DOS LIMITES!\n");
        exit(1);
    }
    if(g->vertices == 0){
        printf("Nenhum caminho possível de um grafo vazio\n");
        return;
    }
    if(g->vertices == 1){
        printf("Caminho 1: %d\n", verticeInicial);
        return;
    }
    int *caminhoAtual = (int *) malloc(g->vertices * sizeof(int));
    if(caminhoAtual == NULL){
        printf("FALHA AO ALOCAR MEMORIA PARA {caminhoAtual}\n");
        exit(1);
    }

    //calloc aparentemente aloca e inicia com 0
    int *visitados = (int *) calloc(g->vertices, sizeof(int));
    if(visitados == NULL){
        printf("FALHA AO ALOCAR MEMORIA PARA {visitados}\n");
        exit(1);
    }

    int numCaminhos = 0;
    printf("encontrando todos os caminhos com inicio em %d que visita todos os vertices do grafo:\n", verticeInicial);
    encontrarCaminhosAux(g, verticeInicial, caminhoAtual, 0, visitados, &numCaminhos);
    if (numCaminhos == 0)
        printf("Nenhum caminho encontrado para visitar todos os vertices :(\n");
    
    free(caminhoAtual);
    free(visitados);
}

char grafoConexo(Grafo g){
    if(g == NULL){
        printf("ERRO: O GRAFO E NULO\n");
        return 0;
    }
    if(g->vertices==0)
        return 1;

    inicializarVisitados(g);

    dfsVisita(g, 0, 0);
    int contaVisitados = 0;
    for(int i = 0; i < g->vertices; i++){
        if(g->visitado[i] == 1)
            contaVisitados++;
    }
    return (contaVisitados == g->vertices);
}

Grafo gerarGrafoAleatorio(int numVertices, float grau_conectividade, char direcionado){
    if(numVertices <= 0){
        printf("ERRO: numero e vertices deve ser positivo\n");
        exit(1);
    }
    if(grau_conectividade < 0.0 || grau_conectividade > 1.0){
        printf("ERRO: grau nao pode passar do intervalo (0, 1)");
        exit(1);
    }
    Grafo g = inicializarGrafo(numVertices);
    srand(time(NULL));
    if(g == NULL)
        return NULL;
    
        for(int i=0; i < numVertices; i++){
            for(int j = (direcionado? 0 : i+1); j < numVertices; j++){
                double prob = (double)rand() / RAND_MAX;
                if(prob<grau_conectividade)
                    insereArcoNoGrafo(g,i,j, direcionado);
            }
        }

        if(!direcionado && numVertices > 1){
            int tentativas = 0;
            int MAX_TENTATIVAS = numVertices*numVertices*2;
            while(!grafoConexo(g) && tentativas < MAX_TENTATIVAS){
                int u = rand() % numVertices;
                int v = rand() % numVertices;
                if(u==v) 
                    continue;

                char arestaExite = 0;
                for(link a = g->conexoes[u]; a != NULL; a = a->prox){
                    if(a->destino == v){
                        arestaExite = 1;
                        break;
                    }
                }
                if(arestaExite) 
                    continue; // tenta outro
                
                insereArcoNoGrafo(g,u,v,direcionado);
                tentativas++;
            }

            if(!grafoConexo(g)){
                printf("Nao foi possivel garantir grafo conexo, tente novamente...\n");
                return NULL;
            }
        }
    return g;
}

void imprimeGrafo(Grafo g) {
    for (int v = 0; v < g->vertices; v++) {
        printf("Vertice %d:", v);
        for (link a = g->conexoes[v]; a != NULL; a = a->prox) {
            printf(" %d", a->destino);
        }
        printf("\n");
    }
}