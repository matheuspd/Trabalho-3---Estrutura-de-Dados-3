/*
	Matheus Pereira Dias - 11207752 - 100%
	Gabriel Cazzini Cardoso - 12547771 - 100%
*/

#include "funcionalidades.h"

#define TAM_PAGINA_DISCO 960

char *remove_aspas(char *nomeCampo) { // Remove as aspas de uma string
	char *str = malloc(sizeof(char) * strlen(nomeCampo));
	for (int i = 0; i < strlen(nomeCampo); i++)
	{
		if (nomeCampo[i + 1] == '"')
		{
			str[i] = '\0';
			break;
		}
		str[i] = nomeCampo[i + 1];
	}
	strcpy(nomeCampo, str);
	free(str);
	return nomeCampo;
}

void funcionalidade11() { // Cria grafo e imprime os vertices
	char arqBin[TAM_MAX_NOME];
	scanf("%s", arqBin);

	FILE *bin = fopen(arqBin, "rb");

	if (bin == NULL)
	{
		msg_falha_processamento();
		exit(0);
	}

	CABECALHO *cab = malloc(sizeof(CABECALHO));
	REGISTRO *reg = malloc(sizeof(REGISTRO));
	Grafo *gr = criaGrafo();

	int existe_cabecalho = ler_cabecalho_bin(cab, bin);

	if (existe_cabecalho)
	{
		if (cab->proxRRN != 0)
		{
			for (int i = 0; i < cab->proxRRN; i++)
			{
				int existe_registro = ler_registro_bin(reg, bin);

				if (existe_registro)
				{
					if (reg->removido == '0')
					{
						insereGrafo(gr, reg);	// Imprime os registros nao removidos do arquivo binario
					}
				}
			}
		}
		else
		{
			msg_registro_inexistente();
		}
	}
	else
	{
		msg_falha_processamento();
	}

	ordenarGrafo(gr);
	imprimeGrafo(gr);	
	liberaGrafo(gr);
	free(reg);
	free(cab);
	fclose(bin);
	
}

void funcionalidade12() { // Verifica a quantidade de ciclos presentes no grafo
	char arqBin[TAM_MAX_NOME];
	scanf("%s", arqBin);

	FILE *bin = fopen(arqBin, "rb");

	if (bin == NULL)
	{
		msg_falha_processamento();
		exit(0);
	}

	CABECALHO *cab = malloc(sizeof(CABECALHO));
	REGISTRO *reg = malloc(sizeof(REGISTRO));
	Grafo *gr = criaGrafo();

	int existe_cabecalho = ler_cabecalho_bin(cab, bin);

	if (existe_cabecalho)
	{
		if (cab->proxRRN != 0)
		{
			for (int i = 0; i < cab->proxRRN; i++)
			{
				int existe_registro = ler_registro_bin(reg, bin);

				if (existe_registro)
				{
					if (reg->removido == '0')
					{
						insereGrafo(gr, reg);	// Imprime os registros nao removidos do arquivo binario
					}
				}
			}
		}
		else
		{
			msg_registro_inexistente();
		}
	}
	else
	{
		msg_falha_processamento();
	}

	ordenarGrafo(gr);
	buscaEmProfundidade(gr);
	liberaGrafo(gr);
	free(reg);
	free(cab);
	fclose(bin);
}

void funcionalidade13() { // Verifica a maior taxa de transmissao possivel entre 2 vertices
	char arqBin[TAM_MAX_NOME];
	int n;
	scanf("%s %d", arqBin, &n);

	FILE *bin = fopen(arqBin, "rb");

	if (bin == NULL)
	{
		msg_falha_processamento();
		exit(0);
	}

	CABECALHO *cab = malloc(sizeof(CABECALHO));
	REGISTRO *reg = malloc(sizeof(REGISTRO));
	Grafo *gr = criaGrafo();

	int existe_cabecalho = ler_cabecalho_bin(cab, bin);

	if (existe_cabecalho)
	{
		if (cab->proxRRN != 0)
		{
			for (int i = 0; i < cab->proxRRN; i++)
			{
				int existe_registro = ler_registro_bin(reg, bin);

				if (existe_registro)
				{
					if (reg->removido == '0')
					{
						insereGrafo(gr, reg);	// Imprime os registros nao removidos do arquivo binario
					}
				}
			}
		}
		else
		{
			msg_registro_inexistente();
		}
	}
	else
	{
		msg_falha_processamento();
	}

	ordenarGrafo(gr);

	int PoPsOrigem, PoPsDestino;

	// Grafo especial pra armazenar o resíduo de velocidade nas arestas, não a velocidade em si
	Grafo *residuo = criaGrafo();
	
	for(int i = 0; i < n; i++) {
		*(residuo) = *(gr);

		scanf("%d %d", &PoPsOrigem, &PoPsDestino);

		int visitados[gr->totalVertices]; // Criar uma lista de "vértices visitados" para armazenar caminhos sem ciclos durante a recursão
		int n_visitados = 0; // Índice do fim atual da lista de vértices visitados

		int fluxo_maximo = fluxoBFS(residuo, PoPsOrigem, PoPsDestino, visitados, n_visitados);

		if (!fluxo_maximo) { // Em caso de fluxo nulo entre os dois vértices
			printf("Fluxo máximo entre %d e %d: -1\n", PoPsOrigem, PoPsDestino);

		} else {
			printf("Fluxo máximo entre %d e %d: %dMbps\n", PoPsOrigem, PoPsDestino, fluxo_maximo);
		}
			
	}
	liberaGrafo(gr);
	free(reg);
	free(cab);
	fclose(bin);
}

void funcionalidade14() { // Verifica o comprimento do caminho entre 2 vertices, passando por outro vetice especifico
	char arqBin[TAM_MAX_NOME];
	int n;
	scanf("%s %d", arqBin, &n);

	FILE *bin = fopen(arqBin, "rb");

	if (bin == NULL)
	{
		msg_falha_processamento();
		exit(0);
	}

	CABECALHO *cab = malloc(sizeof(CABECALHO));
	REGISTRO *reg = malloc(sizeof(REGISTRO));
	Grafo *gr = criaGrafo();

	int existe_cabecalho = ler_cabecalho_bin(cab, bin);

	if (existe_cabecalho)
	{
		if (cab->proxRRN != 0)
		{
			for (int i = 0; i < cab->proxRRN; i++)
			{
				int existe_registro = ler_registro_bin(reg, bin);

				if (existe_registro)
				{
					if (reg->removido == '0')
					{
						insereGrafo(gr, reg);	// Imprime os registros nao removidos do arquivo binario
					}
				}
			}
		}
		else
		{
			msg_registro_inexistente();
		}
	}
	else
	{
		msg_falha_processamento();
	}

	ordenarGrafo(gr);

	int  PoPsOrigem, PoPsDestino, PoPsParada;

	for(int i = 0; i < n; i++) {
		scanf("%d %d %d", &PoPsOrigem, &PoPsDestino, &PoPsParada);
		int dist1 = dijkstra(gr, PoPsOrigem, PoPsParada);
		int dist2 = dijkstra(gr, PoPsParada, PoPsDestino);

		if(dist1 == INT_MAX || dist2 == INT_MAX) {
			printf("Comprimento do caminho entre %d e %d parando em %d: -1\n", PoPsOrigem, PoPsDestino, PoPsParada);
		} else if (dist1 == -1 || dist2 == -1){
			msg_falha_processamento();
			liberaGrafo(gr);
			free(reg);
			free(cab);
			fclose(bin);
			exit(0);
		} else {
			printf("Comprimento do caminho entre %d e %d parando em %d: %dMbps\n", PoPsOrigem, PoPsDestino, PoPsParada, dist1+dist2);
		}	
	}
	liberaGrafo(gr);
	free(reg);
	free(cab);
	fclose(bin);	
}
