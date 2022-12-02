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
        case 11: // 
            funcionalidade1();
            break;
        case 12: // 
            funcionalidade2();
            break;
        case 13: // 
            funcionalidade3();
            break;
        case 14: // 
            funcionalidade4();
            break;
        default:
            msg_funcionalidade_inexistente();
            break;
    }
}