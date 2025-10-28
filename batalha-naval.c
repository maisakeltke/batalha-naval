#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5 // tamanho do tabuleiro

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(char tabuleiro[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            tabuleiro[i][j] = '~';
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(char tabuleiro[SIZE][SIZE], int ocultarNavios) {
    printf("  ");
    for(int i = 0; i < SIZE; i++)
        printf("%d ", i);
    printf("\n");

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for(int j = 0; j < SIZE; j++) {
            if(ocultarNavios && tabuleiro[i][j] == 'N') {
                printf("~ ");
            } else {
                printf("%c ", tabuleiro[i][j]);
            }
        }
        printf("\n");
    }
}

// Função para colocar navios no tabuleiro
void colocarNavios(char tabuleiro[SIZE][SIZE], int numNavios) {
    int x, y;
    printf("Colocando %d navios no tabuleiro (coordenadas de 0 a %d)\n", numNavios, SIZE-1);
    for(int i = 0; i < numNavios; i++) {
        do {
            printf("Digite a linha e coluna do navio %d: ", i+1);
            scanf("%d %d", &x, &y);
            if(x < 0 || x >= SIZE || y < 0 || y >= SIZE || tabuleiro[x][y] == 'N') {
                printf("Coordenadas inválidas ou já ocupadas. Tente novamente.\n");
            } else {
                tabuleiro[x][y] = 'N';
                break;
            }
        } while(1);
    }
}

// Função para atacar o tabuleiro do inimigo
int atacar(char tabuleiro[SIZE][SIZE], int x, int y) {
    if(tabuleiro[x][y] == 'N') {
        printf("Acertou!\n");
        tabuleiro[x][y] = 'X'; // navio atingido
        return 1;
    } else if(tabuleiro[x][y] == '~') {
        printf("Água!\n");
        tabuleiro[x][y] = 'O'; // tiro na água
        return 0;
    } else {
        printf("Você já atacou essa posição. Tente outra.\n");
        return -1;
    }
}

// Função principal
int main() {
    char tabuleiro1[SIZE][SIZE];
    char tabuleiro2[SIZE][SIZE];
    int numNavios = 3;
    int acertos1 = 0, acertos2 = 0;
    int x, y;

    inicializarTabuleiro(tabuleiro1);
    inicializarTabuleiro(tabuleiro2);

    printf("Jogador 1, coloque seus navios:\n");
    colocarNavios(tabuleiro1, numNavios);
    system("clear"); // ou "cls" no Windows

    printf("Jogador 2, coloque seus navios:\n");
    colocarNavios(tabuleiro2, numNavios);
    system("clear");

    // Loop do jogo
    while(acertos1 < numNavios && acertos2 < numNavios) {
        // Turno do jogador 1
        printf("Tabuleiro do jogador 2:\n");
        imprimirTabuleiro(tabuleiro2, 1);
        do {
            printf("Jogador 1, ataque (linha coluna): ");
            scanf("%d %d", &x, &y);
        } while(atacar(tabuleiro2, x, y) == -1);
        acertos1++;
        if(acertos1 == numNavios) break;

        // Turno do jogador 2
        printf("Tabuleiro do jogador 1:\n");
        imprimirTabuleiro(tabuleiro1, 1);
        do {
            printf("Jogador 2, ataque (linha coluna): ");
            scanf("%d %d", &x, &y);
        } while(atacar(tabuleiro1, x, y) == -1);
        acertos2++;
    }

    if(acertos1 == numNavios) {
        printf("Jogador 1 venceu!\n");
    } else {
        printf("Jogador 2 venceu!\n");
    }

    return 0;
}
