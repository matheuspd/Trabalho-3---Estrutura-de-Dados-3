#ifndef __GRAFO__
#define __GRAFO__

#include "registros.h"

typedef struct aresta {
    int idPoPsConectado;
    float velocidade;
    Aresta *prox;
    size_t size;
    size_t numLigacoes;
} Aresta;

typedef struct vertice {
    int id;
    int numVerticesLigados;
    char nomePoPs[TAM_MAX_NOME];
    char nomePais[TAM_MAX_NOME];
    char siglaPais[3];
    Aresta *primeiro;
} Vertice;

typedef struct grafo {
    int totalVertices;
    int totalArestas;
    Vertice *vertices;
    size_t sizeGrafo;
} Grafo;

Grafo *criaGrafo();
void liberaGrafo(Grafo *gr);
int insereGrafo(Grafo *gr, REGISTRO reg);
int insereElementoOrdenado(Grafo *gr, Vertice *vertice, int pos, REGISTRO reg);
int existeVertice(Grafo *gr, int id);
int existeAresta(Grafo *gr, int id1, int id2);

#endif