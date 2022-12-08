#ifndef __HEAPSORT__
#define __HEAPSORT__

#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

void cria_heap_vetice(Vertice *vetor, int i, int f);

void heap_sort_vertice(Vertice *vetor, int n);

void cria_heap_arestas(Aresta *vetor, int i, int f);

void heap_sort_arestas(Aresta *vetor, int n);

#endif