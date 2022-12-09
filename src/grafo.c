#include "grafo.h"
#include "heapsort.h"

Grafo *criaGrafo() {    // Cria grafo vazio
    Grafo *gr = (Grafo*)malloc(sizeof(Grafo));
    if(gr != NULL) {
        gr->totalArestas = 0;
        gr->totalVertices = 0;
        gr->sizeGrafo = NUM_VERTICES_INICIAL;
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
        for(int i = 0; i < gr->totalVertices; i++) {
            free(gr->vertices[i].ligacoes);
        }
        free(gr->vertices);
        free(gr);
    }
}

int insereGrafo(Grafo *gr, REGISTRO *reg) {
    if(gr != NULL) {
        gr->totalVertices = inserirVertices(gr, gr->vertices, gr->totalVertices, reg);
        gr->totalArestas++;
        return 1;
    }
    return 0;
}

int inserirVertices(Grafo *gr, Vertice *v, int fimVetor, REGISTRO *reg) { /*IMPLEMENTAR REALOC*/

    if(reg->idPoPsConectado == -1) {    // Se esta lendo apenas um vertice sem estar conectado a outro
        int pos = existeVertice(gr, reg->idConecta);
        if(pos == -1) {
            v[fimVetor].id = reg->idConecta;
            strcpy(v[fimVetor].nomePais, reg->nomePais);
            strcpy(v[fimVetor].nomePoPs, reg->nomePoPs);
            strcpy(v[fimVetor].siglaPais, reg->siglaPais);
            v[fimVetor].sizeLigacoes = NUM_LIGACOES_INICIAL;
            v[fimVetor].ligacoes = malloc(sizeof(Aresta)*NUM_LIGACOES_INICIAL);
            if(v[fimVetor].ligacoes == NULL) {
                return 0;
            }

            v[fimVetor].numLigacoes = 0;

            v[fimVetor].ligacoes[0].idPoPsConectado = reg->idPoPsConectado;

            if(reg->unidadeMedida == 'G') {
                v[fimVetor].ligacoes[0].velocidade = 1024 * reg->velocidade;
            } else {
                v[fimVetor].ligacoes[0].velocidade = reg->velocidade;
            }
            
            // Nao aumenta o numero de ligacoes, o proximo sera inserido por cima do valor -1

            fimVetor++;
            // REALOC
            if(fimVetor >= gr->sizeGrafo) {
                gr->sizeGrafo *= 2;
                v = realloc(v, gr->sizeGrafo);
            }
        } else {
            if(!strcmp(v[pos].nomePais, "")) {
                strcpy(v[pos].nomePais, reg->nomePais);
                strcpy(v[pos].nomePoPs, reg->nomePoPs);
                strcpy(v[pos].siglaPais, reg->siglaPais);
            }
        }
    } else {
        // Insere o vertice do idConecta
        int pos = existeVertice(gr, reg->idConecta);
        if(pos == -1) {
            v[fimVetor].id = reg->idConecta;
            strcpy(v[fimVetor].nomePais, reg->nomePais);
            strcpy(v[fimVetor].nomePoPs, reg->nomePoPs);
            strcpy(v[fimVetor].siglaPais, reg->siglaPais);
            v[fimVetor].sizeLigacoes = NUM_LIGACOES_INICIAL;
            v[fimVetor].ligacoes = malloc(sizeof(Aresta)*NUM_LIGACOES_INICIAL);
            if(v[fimVetor].ligacoes == NULL) {
                return 0;
            }

            v[fimVetor].numLigacoes = 0;

            v[fimVetor].ligacoes[0].idPoPsConectado = reg->idPoPsConectado;

            if(reg->unidadeMedida == 'G') {
                v[fimVetor].ligacoes[0].velocidade = 1024 * reg->velocidade;
            } else {
                v[fimVetor].ligacoes[0].velocidade = reg->velocidade;
            }

            v[fimVetor].numLigacoes++;

            fimVetor++;
            // REALOC
            if(fimVetor >= gr->sizeGrafo) {
                gr->sizeGrafo *= 2;
                v = realloc(v, gr->sizeGrafo);
            }
        } else {
            if(!strcmp(v[pos].nomePais, "")) {
                strcpy(v[pos].nomePais, reg->nomePais);
                strcpy(v[pos].nomePoPs, reg->nomePoPs);
                strcpy(v[pos].siglaPais, reg->siglaPais);
            }
            v[pos].ligacoes[v[pos].numLigacoes].idPoPsConectado = reg->idPoPsConectado;

            if(reg->unidadeMedida == 'G') {
                v[pos].ligacoes[v[pos].numLigacoes].velocidade = 1024 * reg->velocidade;
            } else {
                v[pos].ligacoes[v[pos].numLigacoes].velocidade = reg->velocidade;
            }

            v[pos].numLigacoes++;
            // REALOC
            if(v[pos].numLigacoes >= v[pos].sizeLigacoes) {
                v[pos].sizeLigacoes *= 2;
                v[pos].ligacoes = realloc(v[pos].ligacoes, v[pos].sizeLigacoes);
            }
        }

        // Insere o vertice do idPoPsConectado
        pos = existeVertice(gr, reg->idPoPsConectado);
        if(pos == -1) {
            v[fimVetor].id = reg->idPoPsConectado;
            strcpy(v[fimVetor].nomePais, "");
            strcpy(v[fimVetor].nomePoPs, "");
            strcpy(v[fimVetor].siglaPais, "");
            v[fimVetor].sizeLigacoes = NUM_LIGACOES_INICIAL;
            v[fimVetor].ligacoes = malloc(sizeof(Aresta)*NUM_LIGACOES_INICIAL);
            if(v[fimVetor].ligacoes == NULL) {
                return 0;
            }

            v[fimVetor].numLigacoes = 0;

            v[fimVetor].ligacoes[0].idPoPsConectado = reg->idConecta;

            if(reg->unidadeMedida == 'G') {
                v[fimVetor].ligacoes[0].velocidade = 1024 * reg->velocidade;
            } else {
                v[fimVetor].ligacoes[0].velocidade = reg->velocidade;
            }

            v[fimVetor].numLigacoes++;

            fimVetor++;
            // REALOC
            if(fimVetor >= gr->sizeGrafo) {
                gr->sizeGrafo *= 2;
                v = realloc(v, gr->sizeGrafo);
            }
        } else {
            v[pos].ligacoes[v[pos].numLigacoes].idPoPsConectado = reg->idConecta;

            if(reg->unidadeMedida == 'G') {
                v[pos].ligacoes[v[pos].numLigacoes].velocidade = 1024 * reg->velocidade;
            } else {
                v[pos].ligacoes[v[pos].numLigacoes].velocidade = reg->velocidade;
            }

            v[pos].numLigacoes++;
            // REALOC
            if(v[pos].numLigacoes >= v[pos].sizeLigacoes) {
                v[pos].sizeLigacoes *= 2;
                v[pos].ligacoes = realloc(v[pos].ligacoes, v[pos].sizeLigacoes);
            }
        }
    }
    return fimVetor;
}

int existeVertice(Grafo *gr, int id) {
    // Retorna posicao do vertice se encontrado e -1 caso contrario
    for(int i = 0; i < gr->totalVertices; i++) {
        if(gr->vertices[i].id == id) {
            return i;
        }
    }
    return -1;
}

void ordenarGrafo(Grafo *gr) {
    heap_sort_vertice(gr->vertices, gr->totalVertices);
    for(int i = 0; i < gr->totalVertices; i++) {
        heap_sort_arestas(gr->vertices[i].ligacoes, gr->vertices[i].numLigacoes);
    }
}

void imprimeGrafo(Grafo *gr) {
    for(int i = 0; i < gr->totalVertices; i++) {
        for(int j = 0; j < gr->vertices[i].numLigacoes; j++) {
            printf("%d %s %s %s ", gr->vertices[i].id, gr->vertices[i].nomePoPs, gr->vertices[i].nomePais, gr->vertices[i].siglaPais);
            printf("%d %dMbps\n", gr->vertices[i].ligacoes[j].idPoPsConectado, gr->vertices[i].ligacoes[j].velocidade);
        }
    }
}