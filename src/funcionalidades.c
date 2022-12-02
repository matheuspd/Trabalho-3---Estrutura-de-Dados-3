/*
	Matheus Pereira Dias - 11207752 - 100%
	Gabriel Cazzini Cardoso - 12547771 - 100%
*/

#include "funcionalidades.h"
#include "funcoesFornecidas.h"
#include "cabecalho.h"
#include "registros.h"
#include "mensagens.h"

#define TAM_PAGINA_DISCO 960

char *remove_aspas(char *nomeCampo)
{
	// Remove as aspas de uma string
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

void funcionalidade11()
{ // 
	
}

void funcionalidade2()
{ // 
	
}

void funcionalidade3()
{ // 
	
}

void funcionalidade4()
{ //
	
}
