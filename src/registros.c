/*
	Matheus Pereira Dias - 11207752 - 100%
	Gabriel Cazzini Cardoso - 12547771 - 100%
*/

#include "registros.h"

void ler_registro_input(REGISTRO *reg) {
	reg->removido = '0';
	reg->encadeamento = -1;

	scanf("%d", &reg->idConecta);

	char nomePoPs[TAM_MAX_NOME];
	scan_quote_string(nomePoPs);
	strcpy(reg->nomePoPs, nomePoPs);

	char nomePais[TAM_MAX_NOME];
	scan_quote_string(nomePais);
	strcpy(reg->nomePais, nomePais);

	char siglaPais[3];
	scan_quote_string(siglaPais);
	if (siglaPais[0] == '\0') {
		strcpy(reg->siglaPais, "$$");
	} else {
		strcpy(reg->siglaPais, siglaPais);
	}

	char idPoPsConectado[5];
	scan_quote_string(idPoPsConectado);
	if (idPoPsConectado[0] == '\0') {
		reg->idPoPsConectado = -1;
	} else {
		reg->idPoPsConectado = atoi(idPoPsConectado);
	}

	char unidadeMedida[2];
	scan_quote_string(unidadeMedida);
	if (unidadeMedida[0] == '\0') {
		reg->unidadeMedida = '$';
	} else {
		reg->unidadeMedida = unidadeMedida[0];
	}

	char velocidade[TAM_MAX_NOME];
	scanf("%s", velocidade); // usando scanf aqui pois scan_quote_string não funciona para ler strings fora de aspas de 1 caractere
	if (!strcmp(velocidade, "NULO")) {
		reg->velocidade = -1;
	} else {
		reg->velocidade = atoi(velocidade);
	}
}

int ler_registro_bin(REGISTRO *reg, FILE *bin) {
    if(feof(bin)) {
        return 0;
    }

    fread(&reg->removido, sizeof(char), 1, bin);
    fread(&reg->encadeamento, sizeof(int), 1, bin);
    fread(&reg->idConecta, sizeof(int), 1, bin);
    fread(reg->siglaPais, 2*sizeof(char), 1, bin);
    fread(&reg->idPoPsConectado, sizeof(int), 1, bin);
    fread(&reg->unidadeMedida, sizeof(char), 1, bin);
    fread(&reg->velocidade, sizeof(int), 1, bin);

    char* nomePoPs = malloc(sizeof(char) * TAM_MAX_NOME);
    char* nomePais = malloc(sizeof(char) * TAM_MAX_NOME);

    int eh_PoPs = 1;
    int strPtr = 0;

    // Os outros campos somam a 20 bits dos 64 totais do registro
    // Iterar por todos os 44 restantes para se livrar de todo o lixo
    for (int i = 0; i < 44; i++) {
        char c = getc(bin);

        if (c != '$' && c != '|') {
            if (eh_PoPs) {
                nomePoPs[strPtr] = c;
            } else {
                nomePais[strPtr] = c;
            }

            strPtr++;

        } else if (c == '|') {
            if (eh_PoPs) {
                nomePoPs[strPtr] = '\0';
            } else {
                nomePais[strPtr] = '\0';
            }

            eh_PoPs = 1 - eh_PoPs;
            strPtr = 0;

        }
    }

	if (reg->removido == '1') {
		strcpy(reg->nomePoPs, "\0");
		strcpy(reg->nomePais, "\0");

	} else {
		strcpy(reg->nomePoPs, nomePoPs);
		strcpy(reg->nomePais, nomePais);
	}

    free(nomePoPs);
    free(nomePais);

    return 1;
}

int ler_registro_csv(CABECALHO *cab, REGISTRO *reg, FILE *csv) {

    char linha[100];
    readline(linha,csv);    // Guarda a linha inteira do csv

    if(feof(csv)) {
        return 0;
    }

    if(!strcmp(linha, "\0")) {
        return 0;
    }
  
    int i = 0, pos = 0, j = 0;
    char *aux;
    while(i < 100) {
        aux = malloc(sizeof(char)*TAM_MAX_NOME);
        switch (pos) {            
            case 0: // Le o idConecta
                if(linha[0] == ',') return -1;
                j = 0;
                do{
                    aux[j] = linha[i];
                    j++;
                    i++;
                }while(linha[i] != ',');
                aux[j] = '\0';
                reg->idConecta = atoi(aux);
                i++;
                pos++;
                free(aux);
                break;
            case 1: // Le o nomePoPs
                j = 0;
                if(linha[i] == ',') {
                    strcpy(reg->nomePoPs, "|");
                }                
                else {
                    if(linha[i] == ' ') i++; 
                    do{
                        aux[j] = linha[i];
                        j++;
                        i++;
                    }while(linha[i] != ',');
                    if(aux[j-1] == ' ') aux[j-1] = '\0';
                    else aux[j] = '\0';
                    strcpy(reg->nomePoPs, aux);
                }
                i++;
                pos++;
                free(aux);
                break;
            case 2: // Le o nomePais
                j = 0;
                if(linha[i] == ',') {
                    strcpy(reg->nomePais, "|");
                }                
                else { 
                    if(linha[i] == ' ') i++;
                    do{
                        aux[j] = linha[i];
                        j++;
                        i++;
                    }while(linha[i] != ',');
                    if(aux[j-1] == ' ') aux[j-1] = '\0';
                    else aux[j] = '\0';
                    strcpy(reg->nomePais, aux);
                }
                i++;
                pos++;
                free(aux);
                break;
            case 3: // Le a siglaPais
                j = 0;
                if(linha[i] == ',') {
                    strcpy(reg->siglaPais, "$$");
                }                
                else { 
                    do{
                        aux[j] = linha[i];
                        j++;
                        i++;
                    }while(linha[i] != ',');
                    aux[j] = '\0';
                    strcpy(reg->siglaPais, aux);
                }
                i++;
                pos++;
                free(aux);
                break;
            case 4: // Le o idPoPsConectado
                if(linha[i] == ',') {
                    reg->idPoPsConectado = -1;
                }
                else {
                    j = 0;
                    do{
                        aux[j] = linha[i];
                        j++;
                        i++;
                    }while(linha[i] != ',');
                    aux[j] = '\0';
                    reg->idPoPsConectado = atoi(aux);
                }
                i++;
                pos++;
                free(aux);
                break;
            case 5: // Le a unidadeMedida
                if(linha[i] == ',') {
                    reg->unidadeMedida = '$';
                }
                else {
                    reg->unidadeMedida = linha[i];
                    i++;
                }
                i++;
                pos++;
                free(aux);
                break;
            case 6: // Le a velocidade
                if(linha[i] == '\0') {
                    reg->velocidade = -1;
                }
                else {
                    j = 0;
                    do{
                        aux[j] = linha[i];
                        j++;
                        i++;
                    }while(linha[i] != '\0');
                    aux[j] = '\0';
                    reg->velocidade = atoi(aux);
                }
                i++;
                pos++;
                free(aux);
                break;
            default:
                i=100;
                free(aux);
                break;
        }
    }
    cab->proxRRN++;
    return 1;
}

void escrever_arquivo_bin(CABECALHO *cab, REGISTRO *reg, FILE *csv, FILE *entrada) {
    
    reg->removido = '0';
    reg->encadeamento = -1;

    // Ler csv e escrever registros
    do {
        int x = ler_registro_csv(cab, reg, csv);
        if(x == 1) {
            // Escrever registros
			escrever_registro_bin(reg, entrada);
            
        }
        else if (x == 0){   // Final do arquivo
            break;
        }
        else {  // Erro ao ler o idConecta
            printf("Falha no processamento do arquivo.");
            fclose(csv);
            fclose(entrada);
            exit(0);
        }
    } while(!feof(csv));
}

void escrever_registro_bin(REGISTRO *reg, FILE *entrada) {
	fwrite(&reg->removido, sizeof(char), 1, entrada);
	fwrite(&reg->encadeamento, sizeof(int), 1, entrada);
	fwrite(&reg->idConecta, sizeof(int), 1, entrada);
	fwrite(reg->siglaPais, 2*sizeof(char), 1, entrada);
	fwrite(&reg->idPoPsConectado, sizeof(int), 1, entrada);
	fwrite(&reg->unidadeMedida, sizeof(char), 1, entrada);
	fwrite(&reg->velocidade, sizeof(int), 1, entrada);
	fwrite(reg->nomePoPs, strlen(reg->nomePoPs)*sizeof(char), 1, entrada);
	if(strcmp(reg->nomePoPs, "|")) {
		putc('|', entrada);
	}
	fwrite(reg->nomePais, strlen(reg->nomePais)*sizeof(char), 1, entrada);
	if(strcmp(reg->nomePais, "|")) {
		putc('|', entrada);
	}
	// Printa o lixo apos campos variaveis
	if(!strcmp(reg->nomePoPs, "|") && !strcmp(reg->nomePais, "|")) {
		fwrite(LIXO, (44 - strlen(reg->nomePais) - strlen(reg->nomePoPs))*sizeof(char), 1, entrada);
	}
	else if(strcmp(reg->nomePoPs, "|") && strcmp(reg->nomePais, "|")) {
		fwrite(LIXO, (42 - strlen(reg->nomePais) - strlen(reg->nomePoPs))*sizeof(char), 1, entrada);
	}
	else {
		fwrite(LIXO, (43 - strlen(reg->nomePais) - strlen(reg->nomePoPs))*sizeof(char), 1, entrada);
	}
}

void printa_registro(REGISTRO *reg) {
    if (reg->idConecta != -1) {
        printf("Identificador do ponto: %d\n", reg->idConecta);
    }
    
    if (reg->nomePoPs[0] != '\0') {
        printf("Nome do ponto: %s\n", reg->nomePoPs);
    }
    
    if (reg->nomePais[0] != '\0') {
        printf("Pais de localizacao: %s\n", reg->nomePais);
    }
    
    if (reg->siglaPais[0] != '$') {
        printf("Sigla do pais: %s\n", reg->siglaPais);
    }
    
    if (reg->idPoPsConectado != -1) {
        printf("Identificador do ponto conectado: %d\n", reg->idPoPsConectado);
    }
    
    if (reg->velocidade != -1) {
        printf("Velocidade de transmissao: %d %cbps\n", reg->velocidade, reg->unidadeMedida);
    }
    
    printf("\n");
}

int compara_campo(REGISTRO *reg, char campo[TAM_MAX_NOME], char nomeCampo[TAM_MAX_NOME]) {
    if (!strcmp(campo, "idConecta")) {
        if(reg->idConecta == atoi(nomeCampo)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(!strcmp(campo, "siglaPais")) {
        if(!strcmp(reg->siglaPais, nomeCampo)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(!strcmp(campo, "idPoPsConectado")) {
        if(reg->idPoPsConectado == atoi(nomeCampo)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(!strcmp(campo, "unidadeMedida")) {
        if(reg->unidadeMedida == nomeCampo[0]) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(!strcmp(campo, "velocidade")) {
        if(reg->velocidade == atoi(nomeCampo)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(!strcmp(campo, "nomePoPs")) {
        if(!strcmp(reg->nomePoPs, nomeCampo)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if(!strcmp(campo, "nomePais")) {
        if(!strcmp(reg->nomePais, nomeCampo)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        printf("Falha no processamento do arquivo.");
        return -1;
    }
}
