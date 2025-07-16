#include <stdio.h>
#include "grafo.h"

int main() {
    char dir = 0;
    // inserindo arcos
    Grafo g = NULL;
    int tam = 10;
    float grau_conectividade = 0.25;
    while(!g){
        g = gerarGrafoAleatorio(tam,grau_conectividade,dir);
    }
    // imprime a lista de adjacência
    imprimeGrafo(g);
    dfs(g, 0);
    encontrarTodosCaminhos(g, 0);
    destruirGrafo(g);
    return 0;
}
