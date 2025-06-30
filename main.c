#include <stdio.h>
#include "grafo.h"

void imprimeGrafo(Grafo g) {
    for (int v = 0; v < g->vertices; v++) {
        printf("Vértice %d:", v);
        for (link a = g->conexoes[v]; a != NULL; a = a->prox) {
            printf(" %d", a->destino);
        }
        printf("\n");
    }
}

int main() {
    Grafo g = initGrafo(5); // cria grafo com 5 vértices (0 a 4)
    char dir = 1;
    // inserindo arcos
    insereArcoNoGrafo(g, 0, 1, dir);
    insereArcoNoGrafo(g, 0, 2, dir);
    insereArcoNoGrafo(g, 1, 2, dir);
    insereArcoNoGrafo(g, 2, 3, dir);
    insereArcoNoGrafo(g, 3, 4, dir);
    insereArcoNoGrafo(g, 3, 1, dir);
    insereArcoNoGrafo(g, 4, 0, dir);

    // tentando inserir arco já existente (não deve duplicar)
    insereArcoNoGrafo(g, 0, 1, dir);

    // imprime a lista de adjacência
    imprimeGrafo(g);

    return 0;
}
