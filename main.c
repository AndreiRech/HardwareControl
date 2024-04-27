#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include "register.h"

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024

void menu() {
    printf("\n ---------- [ MENU ] ---------- \n");
    printf("Informe a operação a ser realizada: \n");
    printf("1 → Funções do r0\n");
    printf("2 → Funções do r3\n");
    printf("3 → Mudar cor do display\n");
    printf("4 → Mudar mensagem do display\n");
    printf("5 → Printar valores dos registradores\n");
    printf("6 → Voltar registradores ao padrão\n");
    printf("0 → Sair\n");
}

void menuR0() {
    printf("\n ---------- [ MENU - R0 ] ---------- \n");
    printf("Informe o que deseja fazer: \n");
    printf("1 → Ligar/Desligar display\n");
    printf("2 → Trocar modo do display\n");
    printf("3 → Alterar velocidade da mensagem\n");
    printf("4 → Ligar/Desligar led de operação\n");
    printf("5 → Alterar cor do led de status\n");
    printf("0 → Sair\n");
}

void menuR3() {
    printf("\n ---------- [ MENU - R3 ] ---------- \n");
    printf("Informe o que deseja fazer: \n");
    printf("1 → Mudar nível de bateria\n");
    printf("2 → Mudar temperatura\n");
    printf("3 → Verificar quantidade de repetições\n");
    printf("4 → Resetar quantidade de repetições\n");
    printf("0 → Sair\n");
}

void funcR0() {
    int opc = 0, value;


    do {
        menuR0();
        scanf("\n%d", &opc);

        switch(opc) {
            case 1: 
                printf("\nDeseja ligar [1] ou desligar [0]?\n"); 
                scanf("%d", &value);
                setDisplayOn(value);
                break;
            case 2: 
                printf("\nSelecione o modo de exibição: \n");
                printf("1 → Estático\n 2 → Deslizante\n 3 → Piscante\n 4 → Deslizante|Piscante");
                scanf("%d", &value);
                setDisplayMode(value);
                break;
            case 3: 
                
                break;
            case 4: 
                printf("Deseja ligar [1] ou desligar [0]?\n");
                scanf("%d", &value);
                setOperationLedOnOff(value);
                break;
            case 5: 
                int red, green, blue;
                printf("\nPara alterar a cor, informe [1] ou [0]:\n");
                printf(" [ Vermelho ] = ");
                scanf("%d", &red);
                printf(" [ Verde ] = ");
                scanf("%d", &green);
                printf(" [ Azul ] = ");
                scanf("%d", &blue);
                setStatusLedColor(&red, &green, &blue);

                uint16_t statusLedColor = getStatusLedColor();
                printf("Status LED Color: %u\n", statusLedColor);
                
                break;
            case 6: printf("\nSaindo...\n"); break;
            default: printf("\nInforme uma opção válida!\n"); break;
        }
    } while(opc != 0);
}

void funcR3() {
    int opc = 0, btLvl;
    
    do
    {
        menuR3();
        scanf("\n%d", &opc);

        switch (opc)
        {
        case 1:
            printf("\nInforme o nível de bateria:");
            printf("\nCrítico [00]\t Baixo [01]\t Médio [10]\t Alto[11]\n");
            scanf("%d", &btLvl);
            setBatteryLevel(btLvl);
            break;
        
        default:
            break;
        }
    } while (opc != 0);
    

}
void displayColor() {printf("Sem nada ainda");}
void changeDisplay() {printf("Sem nada ainda");}
void printReg() {printf("Sem nada ainda");}
void resetReg() {printf("Sem nada ainda");}

void opc() {
    int opc = 0;

    do {
        menu();
        scanf("\n%d", &opc);

        switch(opc) {
            case 1: funcR0(); break;
            case 2: funcR3(); break;
            case 3: displayColor(); break;
            case 4: changeDisplay(); break;
            case 5: printReg(); break;
            case 6: resetReg(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nInforme uma opção válida!\n"); break;
        }
    } while(opc != 0);
}

int main() {
    int fd;
    char* map = registers_map(FILE_PATH, FILE_SIZE, &fd);
    if (map == NULL) {
        return EXIT_FAILURE;
    }
    
    opc();

    if (registers_release(map, FILE_SIZE, fd) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
