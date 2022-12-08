//Heap: vetor que simula uma arvore binaria completa(exceto o ultimo nivel)
//Todo elemento "pai" do vetor possui dois "filhos"
//pai(i) -> filhos: (2*i+1) e (2*i+2)

#include "heapsort.h"

void cria_heap_vertice(Vertice *vetor, int i, int f) {
    Vertice aux = vetor[i];
    int j = i*2 + 1;
    while (j <= f) {
        if(j < f) {
            if(vetor[j].id < vetor[j+1].id) j++;  //Pai tem 2 filhos? Qual o maior?
        }
        if(aux.id < vetor[j].id) {    //Filho maior que o pai? Filho se torna o pai. Repetir o processo.
            vetor[i] = vetor[j];
            i = j;
            j = 2*i + 1;
        } else {
            j = f + 1;
        }
    }
    vetor[i] = aux;     //Antigo pai ocupa o lugar do ultimo filho analisado
}

void heap_sort_vertice(Vertice *vetor, int n) {
    int i;
    Vertice aux;
    for(i = (n-1)/2; i >= 0; i--) {     //Cria heap a partir dos dados
        cria_heap_vertice(vetor, i, n-1);
    }
    for(i = n-1; i >= 1; i--) {
        aux = vetor[0];
        vetor[0] = vetor[i];        //Pegar o maior elemento da heap e coloca na sua posicao correspondente no array
        vetor[i] = aux;
        cria_heap_vertice(vetor, 0, i-1);       //Reconstruir heap
    }
}

void cria_heap_arestas(Aresta *vetor, int i, int f) {
    Aresta aux = vetor[i];
    int j = i*2 + 1;
    while (j <= f) {
        if(j < f) {
            if(vetor[j].idPoPsConectado < vetor[j+1].idPoPsConectado) j++;  //Pai tem 2 filhos? Qual o maior?
        }
        if(aux.idPoPsConectado < vetor[j].idPoPsConectado) {    //Filho maior que o pai? Filho se torna o pai. Repetir o processo.
            vetor[i] = vetor[j];
            i = j;
            j = 2*i + 1;
        } else {
            j = f + 1;
        }
    }
    vetor[i] = aux;     //Antigo pai ocupa o lugar do ultimo filho analisado
}

void heap_sort_arestas(Aresta *vetor, int n) {
    int i;
    Aresta aux;
    for(i = (n-1)/2; i >= 0; i--) {     //Cria heap a partir dos dados
        cria_heap_arestas(vetor, i, n-1);
    }
    for(i = n-1; i >= 1; i--) {
        aux = vetor[0];
        vetor[0] = vetor[i];        //Pegar o maior elemento da heap e coloca na sua posicao correspondente no array
        vetor[i] = aux;
        cria_heap_arestas(vetor, 0, i-1);       //Reconstruir heap
    }
}