#ifndef __FUNCIONALIDADES__
#define __FUNCIONALIDADES__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "funcoesFornecidas.h"
#include "cabecalho.h"
#include "registros.h"
#include "mensagens.h"
#include "grafo.h"

char *remove_aspas(char *nomeCampo);

void funcionalidade11(); // Cria grafo e imprime os vertices

void funcionalidade12(); // Verifica a quantidade de ciclos presentes no grafo

void funcionalidade13(); // Verifica a maior taxa de transmissao possivel entre 2 vertices

void funcionalidade14(); // Verifica o comprimento do caminho entre 2 vertices, passando por outro vetice especifico


#endif