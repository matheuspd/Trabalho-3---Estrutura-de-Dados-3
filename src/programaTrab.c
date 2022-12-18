/*  Grupo 23
	Matheus Pereira Dias - 11207752 - 100%
	Gabriel Cazzini Cardoso - 12547771 - 100%
*/

#include "funcionalidades.h"
#include "mensagens.h"

int main() {
    
    int funcionalidade;
    scanf("%d", &funcionalidade);

    switch (funcionalidade) {
        case 11: // Cria grafo e imprime os vertices
            funcionalidade11();
            break;
        case 12: // Verifica a quantidade de ciclos presentes no grafo
            funcionalidade12();
            break;
        case 13: // Verifica a maior taxa de transmissao possivel entre 2 vertices
            funcionalidade13();
            break;
        case 14: // Verifica o comprimento do caminho entre 2 vertices, passando por outro vertice especifico
            funcionalidade14();
            break;
        default:
            msg_funcionalidade_inexistente();
            break;
    }    
}