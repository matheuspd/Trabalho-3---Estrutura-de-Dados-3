#ifndef __GRAFO__
#define __GRAFO__

#include <limits.h>

#include "registros.h"

#define NUM_VERTICES_MAX 1000
#define NUM_LIGACOES_MAX 100

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

typedef enum {
    branco, cinza, preto
} Cor;

Grafo *criaGrafo();
void liberaGrafo(Grafo *gr);
Vertice *realloc_vertices(Grafo *gr);
int insereGrafo(Grafo *gr, REGISTRO *reg);
int inserirVertices(Grafo *gr, Vertice *v, int fimVetor, REGISTRO *reg);
int existeVertice(Grafo *gr, int id);
int velocidadeAresta(int id1, int id2, Grafo *gr);
int fluxoBFS(Grafo* residuo, int id_atual, int id_d, int* visitados, int n_visitados);
int residuoCaminho(Grafo *residuo, int* caminho, int n_caminho);
void buscaEmProfundidade(Grafo *gr);
void visitaDFS(int pos, Grafo *gr, int* tempo, int* d, int* t, Cor* cor, short* antecessor, int* numciclos);
void ordenarGrafo(Grafo *gr);
void imprimeGrafo(Grafo *gr);
int minDist(Grafo *gr, int dist[], bool VerticesArvMin[]);
int dijkstra(Grafo *gr, int pos_origem, int pos_destino);

#endif