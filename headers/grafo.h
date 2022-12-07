#ifndef __GRAFO__
#define __GRAFO__

#include "registros.h"

#define NUM_VERTICES_INICIAL 100
#define NUM_LIGACOES_INICIAL 10

typedef struct aresta {
    int idPoPsConectado;
    int velocidade;
} Aresta;

typedef struct vertice {
    int id;
    char nomePoPs[TAM_MAX_NOME];
    char nomePais[TAM_MAX_NOME];
    char siglaPais[3];
    Aresta *ligacoes;
    size_t sizeLigacoes;
    int numLigacoes;
} Vertice;

typedef struct grafo {
    int totalVertices;
    int totalArestas;
    Vertice *vertices;
    size_t sizeGrafo;
} Grafo;

Grafo *criaGrafo();
void liberaGrafo(Grafo *gr);
int insereGrafo(Grafo *gr, REGISTRO *reg);
int inserirVertices(Grafo *gr, Vertice *v, int fimVetor, REGISTRO *reg);
int existeVertice(Grafo *gr, int id);
void ordenarGrafo(Grafo *gr);
void imprimeGrafo(Grafo *gr);

#endif