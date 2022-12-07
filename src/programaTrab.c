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
            funcionalidade11();
            break;
        case 12: // 
            funcionalidade12();
            break;
        case 13: // 
            funcionalidade13();
            break;
        case 14: // 
            funcionalidade14();
            break;
        default:
            msg_funcionalidade_inexistente();
            break;
    }    
}