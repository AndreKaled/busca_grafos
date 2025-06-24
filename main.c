#include <stdio.h>
#include "grafo.h"

void imprimeGrafo(Grafo g) {
    for (int v = 0; v < g->vertices; v++) {
        printf("Vértice %d:", v);
        for (link a = g->conexoes[v]; a != NULL; a = a->prox) {
            printf(" %d", a->vertices);
        }
        printf("\n");
    }
}

int main() {
    Grafo g = initGrafo(5); // cria grafo com 5 vértices (0 a 4)

    // Inserindo arcos direcionados
    insereArcoNoGrafo(g, 0, 1);
    insereArcoNoGrafo(g, 0, 2);
    insereArcoNoGrafo(g, 1, 2);
    insereArcoNoGrafo(g, 2, 3);
    insereArcoNoGrafo(g, 3, 4);
    insereArcoNoGrafo(g, 4, 0);

    // Tentando inserir arco já existente (não deve duplicar)
    insereArcoNoGrafo(g, 0, 1);

    // Imprime a lista de adjacência
    imprimeGrafo(g);

    return 0;
}
