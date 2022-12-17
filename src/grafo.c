#include "grafo.h"
#include "heapsort.h"

Grafo *criaGrafo() {    // Cria grafo vazio
    Grafo *gr = (Grafo*)malloc(sizeof(Grafo));
    if(gr != NULL) {
        gr->totalArestas = 0;
        gr->totalVertices = 0;
        gr->sizeGrafo = NUM_VERTICES_MAX;
        gr->vertices = malloc(sizeof(Vertice)*gr->sizeGrafo);
        if(gr->vertices == NULL) {
            free(gr);
            return NULL;
        }
    }
    return gr;
}

void liberaGrafo(Grafo *gr) {   // Destroi o grafo
    if(gr != NULL) {
        for(int i = 0; i < gr->totalVertices; i++) {
            free(gr->vertices[i].ligacoes);
        }
        free(gr->vertices);
        free(gr);
    }
}

int insereGrafo(Grafo *gr, REGISTRO *reg) { // Insere um registro no grafo
    if(gr != NULL) {
        gr->totalVertices = inserirVertices(gr, gr->vertices, gr->totalVertices, reg);
        return 1;
    }
    return 0;
}

int inserirVertices(Grafo *gr, Vertice *v, int fimVetor, REGISTRO *reg) { // Insere no grafo um vertice e outro que esta conectado a ele (caso não exista ainda)  

    if(reg->idPoPsConectado == -1) {    // Se esta lendo apenas um vertice sem estar conectado a outro
        int pos = existeVertice(gr, reg->idConecta);
        if(pos == -1) {
            v[fimVetor].id = reg->idConecta;
            strcpy(v[fimVetor].nomePais, reg->nomePais);
            strcpy(v[fimVetor].nomePoPs, reg->nomePoPs);
            strcpy(v[fimVetor].siglaPais, reg->siglaPais);
            v[fimVetor].sizeLigacoes = NUM_LIGACOES_MAX;
            v[fimVetor].ligacoes = malloc(sizeof(Aresta)*NUM_LIGACOES_MAX);
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
            v[fimVetor].sizeLigacoes = NUM_LIGACOES_MAX;
            v[fimVetor].ligacoes = malloc(sizeof(Aresta)*NUM_LIGACOES_MAX);
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
            
        }

        // Insere o vertice do idPoPsConectado
        pos = existeVertice(gr, reg->idPoPsConectado);
        if(pos == -1) {
            v[fimVetor].id = reg->idPoPsConectado;
            strcpy(v[fimVetor].nomePais, "");
            strcpy(v[fimVetor].nomePoPs, "");
            strcpy(v[fimVetor].siglaPais, "");
            v[fimVetor].sizeLigacoes = NUM_LIGACOES_MAX;
            v[fimVetor].ligacoes = malloc(sizeof(Aresta)*NUM_LIGACOES_MAX);
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
            
        } else {
            v[pos].ligacoes[v[pos].numLigacoes].idPoPsConectado = reg->idConecta;

            if(reg->unidadeMedida == 'G') {
                v[pos].ligacoes[v[pos].numLigacoes].velocidade = 1024 * reg->velocidade;
            } else {
                v[pos].ligacoes[v[pos].numLigacoes].velocidade = reg->velocidade;
            }

            v[pos].numLigacoes++;
            
        }

        gr->totalArestas++;
    }
    return fimVetor;
}

int existeVertice(Grafo *gr, int id) {  // Verifica se existe um vertice com o valor do idConecta dado
    // Retorna posicao do vertice se encontrado e -1 caso contrario
    for(int i = 0; i < gr->totalVertices; i++) {
        if(gr->vertices[i].id == id) {
            return i;
        }
    }
    return -1;
}

int velocidadeAresta(int id1, int id2, Grafo *gr) {   // Verifica se existe uma aresta entre os 2 vertices
    int pos1 = existeVertice(gr, id1);
    if(pos1 != -1) {
        Vertice v1 = gr->vertices[pos1];
        for(int i = 0; i < v1.numLigacoes; i++) {
            if(v1.ligacoes[i].idPoPsConectado == id2) {
                return v1.ligacoes[i].velocidade;
            }
        }
    }
    return -1;
}

int fluxoBFS(Grafo* residuo, int PoPsAtual, int PoPsDestino, int* visitados, int n_visitados) {
	int fluxo_atual = 0;
	int pos_atual = existeVertice(residuo, PoPsAtual);

	if (pos_atual == -1) {
		return -1;
	}

	Vertice v_atual = residuo->vertices[pos_atual];

	for (int i = 0; i < v_atual.numLigacoes; i++) {

		int ja_visitado = 0; // Especificamente pular vértices já visitados pra evitar ciclos no caminho

		for (int j = 0; j < n_visitados; j++) {
			if (v_atual.ligacoes[i].idPoPsConectado == visitados[j]) {
				ja_visitado = 1;
				break;
			}
		}

		if (ja_visitado) {
			continue;
		}

		if (v_atual.ligacoes[i].velocidade == 0) { // Pular arestas sem resíduo remanescente
			continue;
		}

		// Mover os ponteiros referentes ao ponto atual da recursão para o próximo vértice
		PoPsAtual = v_atual.ligacoes[i].idPoPsConectado;
		visitados[n_visitados] = PoPsAtual;
		n_visitados++;

		if (PoPsAtual != PoPsDestino) { // Se o caminho ainda está incompleto...
			// Continuar procurando o fluxo deste caminho
			int resultado = fluxoBFS(residuo, PoPsAtual, PoPsDestino, visitados, n_visitados);

			if (resultado == -1) {
				continue;
			}

			fluxo_atual += resultado;

		} else { // Se este é o último vértice, calcular o fluxo máximo desse caminho e atualizar o grafo de resíduos

			int resultado = residuoCaminho(residuo, visitados, n_visitados);

			if (resultado == -1) {
				continue;
			}

			fluxo_atual += resultado;
		}

	}

	// Retornar o fluxo total deste galho da recursão
	return fluxo_atual;
}

int residuoCaminho(Grafo *residuo, int* caminho, int n_caminho) { // Encontrar o fluxo máximo (resíduo mínimo) de um caminho definido de vértices
	int min_residuo = -1;

	// Obter o vértice correspondente ao primeiro ID
	int pos_atual = existeVertice(residuo, caminho[0]);
	if (pos_atual == -1) {
		return -1;
	}
	Vertice v_atual = residuo->vertices[pos_atual];

	for (int i = 0; i < n_caminho - 1; i++) {
		for (int j = 0; j < v_atual.numLigacoes; j++) {
			if (v_atual.ligacoes[i].idPoPsConectado != caminho[i+1]) { // Procurar apenas pela ligação ao próximo vértice
				continue;
			}

			if (v_atual.ligacoes[i].velocidade < min_residuo || min_residuo == -1) { // Checar resíduo mínimo
				min_residuo = v_atual.ligacoes[i].velocidade;
			}

			// Mover para o próximo vértice da lista
			pos_atual = existeVertice(residuo, caminho[i+1]);
			if (pos_atual == -1) {
				return -1;
			}
			v_atual = residuo->vertices[pos_atual];

		}
	}

	// Recomeçar do primeiro vértice
	pos_atual = existeVertice(residuo, caminho[0]);
	if (pos_atual == -1) {
		return -1;
	}
	v_atual = residuo->vertices[pos_atual];

	// Passar o fluxo máximo (= remover o resíduo mínimo) pelo caminho inteiro
	for (int i = 0; i < n_caminho - 1; i++) {
		for (int j = 0; j < v_atual.numLigacoes; j++) {
			if (v_atual.ligacoes[i].idPoPsConectado != caminho[i+1]) { // Procurar apenas pela ligação ao próximo vértice
				continue;
			}

			v_atual.ligacoes[i].velocidade -= min_residuo; // Remover resíduo mínimo

			// Mover para o próximo vértice da lista
			pos_atual = existeVertice(residuo, caminho[i+1]);
			if (pos_atual == -1) {
				return -1;
			}
			v_atual = residuo->vertices[pos_atual];

		}
	}

	return min_residuo; // ou max_fluxo;
}

void ordenarGrafo(Grafo *gr) {  // Ordena o grafo pelos valores de idConecta(vertices) e idPoPs(listas de cada vertice)
    heap_sort_vertice(gr->vertices, gr->totalVertices);
    for(int i = 0; i < gr->totalVertices; i++) {
        heap_sort_arestas(gr->vertices[i].ligacoes, gr->vertices[i].numLigacoes);
    }
}

void imprimeGrafo(Grafo *gr) {  // Imprime o grafo em ordem
    for(int i = 0; i < gr->totalVertices; i++) {
        for(int j = 0; j < gr->vertices[i].numLigacoes; j++) {
            printf("%d %s %s %s ", gr->vertices[i].id, gr->vertices[i].nomePoPs, gr->vertices[i].nomePais, gr->vertices[i].siglaPais);
            printf("%d %dMbps\n", gr->vertices[i].ligacoes[j].idPoPsConectado, gr->vertices[i].ligacoes[j].velocidade);
        }
    }
}

void visitaDFS(int pos, Grafo *gr, int* tempo, int* d, int* t, Cor* cor, short* antecessor, int *numCiclos) {
    int aux;
    int pos_v;
    cor[pos] = cinza;
    (*tempo)++;
    d[pos] = (*tempo);
    //printf("Visita id %2d Tempo descoberta:%2d cinza\n", gr->vertices[pos].id, d[pos]);
    if (gr->vertices[pos].numLigacoes > 0) {
        aux = gr->vertices[pos].ligacoes[0].idPoPsConectado;
        int pos_lista = 0;
        while (pos_lista < gr->vertices[pos].numLigacoes) { 
            pos_v = existeVertice(gr, aux);         
            if (cor[pos_v] == branco) {
                antecessor[pos_v] = pos;
                visitaDFS(pos_v, gr, tempo, d, t, cor, antecessor, numCiclos);
            }
            if(cor[pos_v] == cinza && pos_v != antecessor[pos]){
                (*numCiclos)++;             
            }

            pos_lista++;
            aux = gr->vertices[pos].ligacoes[pos_lista].idPoPsConectado;
        }
    }
    cor[pos] = preto;
    (*tempo)++;
    t[pos] = (*tempo);
    //printf("Visita id %2d Tempo termino:%2d preto\n", gr->vertices[pos].id, t[pos]);
}

void buscaEmProfundidade(Grafo *gr) {
    int pos;
    int tempo = 0;
    int numCiclos = 0;
    int d[gr->totalVertices], t[gr->totalVertices];
    Cor cor[gr->totalVertices];
    short antecessor[gr->totalVertices];
    for (pos = 0; pos < gr->totalVertices; pos++) {
        cor[pos] = branco;
        antecessor[pos] = -1;
    }
    for (pos = 0; pos < gr->totalVertices; pos++) {
        if (cor[pos] == branco) visitaDFS(pos, gr, &tempo, d, t, cor, antecessor, &numCiclos);
    }
    printf("Quantidade de ciclos: %d\n", numCiclos);
}
 

// Encontra o vertice com a menor distancia dos vertices ainda nao inclusos na arvore de menor caminho
int minDist(Grafo *gr, int dist[], bool VerticesArvMin[]) {
    // Inicializa menor valor
    int min = INT_MAX, min_pos;
 
    for (int i = 0; i < gr->totalVertices; i++) {
        if (VerticesArvMin[i] == false && dist[i] <= min) {
            min = dist[i];
            min_pos = i;
        }
    }
 
    return min_pos;
}

int dijkstra(Grafo *gr, int id_origem, int id_destino) {
    int pos_origem = existeVertice(gr, id_origem);
    int pos_destino = existeVertice(gr, id_destino);
    if(pos_origem == -1 || pos_destino == -1) {
        return -1;
    }
    
    int dist[gr->totalVertices];
 
    bool VerticesArvMin[gr->totalVertices]; // VerticesArvMin[i] true se o vertice i esta no menor caminho da arvore
 
    // Inicializa as distancias como Infinito e o menor caminho pela arvore como falso
    for (int i = 0; i < gr->totalVertices; i++) {
        dist[i] = INT_MAX;
        VerticesArvMin[i] = false;
    }
 
    // Distancia da pos_origem ate ela mesma e zero
    dist[pos_origem] = 0;
    
    // Encontra menor caminho para todos os vertices
    for (int count = 0; count < gr->totalVertices - 1; count++) {
        // Pega a menor distancia entre os vertices ainda nao processados
        int u = minDist(gr, dist, VerticesArvMin);
 
        // Marca o vertice como processado
        VerticesArvMin[u] = true;

        // Atualiza as distancia dos vertices adjacentes do vertice selecionado
        for (int v = 0; v < gr->totalVertices; v++) {
            int vel = velocidadeAresta(gr->vertices[u].id, gr->vertices[v].id, gr);
            // Atualiza dist[v] somente se nao esta em VerticesArvMin
            if (!VerticesArvMin[v] && vel != -1 && dist[u] != INT_MAX && dist[u] + vel < dist[v]) {
                dist[v] = dist[u] + vel;
            }
        }
    }
    return dist[pos_destino];
}

