/*
	Matheus Pereira Dias - 11207752 - 100%
	Gabriel Cazzini Cardoso - 12547771 - 100%
*/

#include "cabecalho.h"

void alocar_cabecalho(CABECALHO *cab, FILE *arq) {
    cab->status = '0';
    cab->topo = -1;
    cab->proxRRN = 0;
    cab->nroRegRem = 0;
    cab->nroPagDisco = 0;
    cab->qttCompacta = 0;

	// Inicializar o cabeçalho apenas com o status de escrita interminada
	putc('0', arq);

	// Iterar pelos 959 bits restantes aplicando o lixo
    for (int i = 1; i < 960; i++) {
        putc('$', arq);
    }
}

void escrever_cabecalho_bin(CABECALHO *cab, FILE *arq){
    cab->status = '1';
    cab->nroPagDisco = (int) ceil((cab->proxRRN*64)/960.0) + 1;
    rewind(arq);
    fwrite(&cab->status, sizeof(char), 1, arq);
    fwrite(&cab->topo, sizeof(int), 1, arq);
    fwrite(&cab->proxRRN, sizeof(int), 1, arq);
    fwrite(&cab->nroRegRem, sizeof(int), 1, arq);
    fwrite(&cab->nroPagDisco, sizeof(int), 1, arq);
    fwrite(&cab->qttCompacta, sizeof(int), 1, arq);
}

int ler_cabecalho_bin(CABECALHO *cab, FILE *arq) {
    if(feof(arq)) {
        return 0;
    }

    fread(&cab->status, sizeof(char), 1, arq);
    if(cab->status == '0') {
        return 0;
    }
    fread(&cab->topo, sizeof(int), 1, arq);
    fread(&cab->proxRRN, sizeof(int), 1, arq);
    fread(&cab->nroRegRem, sizeof(int), 1, arq);
    fread(&cab->nroPagDisco, sizeof(int), 1, arq);
    fread(&cab->qttCompacta, sizeof(int), 1, arq);

    // Os outros campos somam a 21 bits dos 960 totais do registro
    // Iterar por todos os 939 restantes para se livrar de todo o lixo
    char c;
    for (int i = 21; i < 960; i++) {
        c = getc(arq);
    }
    return c;
}