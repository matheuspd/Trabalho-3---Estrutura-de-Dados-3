#include "grafo.h"

Grafo *criaGrafo() {    // Cria grafo vazio
    Grafo *gr = (Grafo*)malloc(sizeof(Grafo));
    if(gr != NULL) {
        gr->totalArestas = 0;
        gr->totalVertices = 0;
        gr->sizeGrafo = 100;
        gr->vertices = malloc(sizeof(Vertice)*gr->sizeGrafo);
        if(gr->vertices == NULL) {
            free(gr);
            return NULL;
        }
    }
    return gr;
}

void liberaGrafo(Grafo *gr) {
    if(gr != NULL) {
        
    }
}

int insereGrafo(Grafo *gr, REGISTRO reg) {
    if(gr != NULL) {
        if(gr->totalVertices == 0) {  // Grafo vazio
            
        }
        else {            
            
        }
    }
    return 0;
}

int insereElementoOrdenado(Grafo *gr, Vertice *vertice, int pos, REGISTRO reg) {
    

}

int existeVertice(Grafo *gr, int id) {

}

int existeAresta(Grafo *gr, int id1, int id2) {

}