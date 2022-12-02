#ifndef __CABECALHO__
#define __CABECALHO__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct _cabecalho{
    char status;    // 0 ou 1
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
};

typedef struct _cabecalho CABECALHO;

void alocar_cabecalho(CABECALHO *cab, FILE *arq);

void escrever_cabecalho_bin(CABECALHO *cab, FILE *arq);

int ler_cabecalho_bin(CABECALHO *cab, FILE *arq);

#endif