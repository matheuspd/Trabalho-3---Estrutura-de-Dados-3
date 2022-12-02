#ifndef __REGISTROS__
#define __REGISTROS__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cabecalho.h"

#define TAM_MAX_NOME 25
#define LIXO "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"

struct _registro{
    int idConecta;
    char nomePoPs[TAM_MAX_NOME];
    char nomePais[TAM_MAX_NOME];
    char siglaPais[3];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char removido;  // 0 ou 1
    int encadeamento;
};

typedef struct _registro REGISTRO;

void escrever_arquivo_bin(CABECALHO *cab, REGISTRO *reg, FILE *csv, FILE *entrada);

void escrever_registro_bin(REGISTRO *reg, FILE *entrada);

void printa_registro(REGISTRO *reg);

int ler_registro_csv(CABECALHO *cab, REGISTRO *reg, FILE *csv);

int ler_registro_bin(REGISTRO *reg, FILE *bin);

void ler_registro_input(REGISTRO *reg);

int compara_campo(REGISTRO *reg, char campo[TAM_MAX_NOME], char nomeCampo[TAM_MAX_NOME]);

#endif