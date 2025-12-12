#include <stdio.h>
#include <stdlib.h>
//conio para kbhit e getch
#include <conio.h>
//gotoxy e esconder cursor
#include <windows.h>

#define ALTURA 20
#define LARGURA 40

char tela[ALTURA][LARGURA];
int x, y;            // posição do cursor
char pincel = '#';   // caractere que desenha
int desenhando = 0;

// Prototipos
void iniciar();
void desenharTudo();
void lerEntrada();
void gotoxy(int cx, int cy);
void esconderCursor();
void menuInicial(); 

int main() {
    esconderCursor(); 
    menuInicial();    
    iniciar();

    while (1) {
        desenharTudo();
        lerEntrada();
        //Sleep(30); adicione essa linha se o cpu estiver sobrecarregado mas sem ela mto menos delay
    }

    return 0;
}


void menuInicial() {
    system("cls");

    printf("   +------------------------------------------+\n");
    printf("   |              _        _                   |\n");
    printf("   |             (_)      | |                  |\n");
    printf("   |   _ __   __ _ _ _ __ | | _                |\n");
    printf("   |  | '_ \\/ _` | | '_ \\| __|               |\n");
    printf("   |  | |_) | (_| | | | | | | _                |\n");
    printf("   |  | .__/ \\__,_|_|_| |_|\\__|               |\n");
    printf("   |  | |                                     |\n");
    printf("   |  |_|                                     |\n");
    printf("   +------------------------------------------+\n\n");

    printf("                    [  P A I N T  ]\n\n");

    printf("   +------------------------------------------+\n");
    printf("   |   WASD -> mover cursor                   |\n");
    printf("   |   Espaco -> desenhar                     |\n");
    printf("   |   M -> trocar pincel                     |\n");
    printf("   |   B -> borracha                          |\n");
    printf("   +------------------------------------------+\n\n");

    printf("     >> Pressione qualquer tecla para iniciar... <<");

    getch();
    system("cls");
}



void iniciar() {
    // Começa no centro
    x = LARGURA / 2;
    y = ALTURA / 2;

    // Deixa a tela vazia
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            tela[i][j] = ' ';
        }
    }
}
//gotoxy porque o cls fazia com que tudo piscasse
void gotoxy(int cx, int cy) {
    COORD c;
    c.X = cx;
    c.Y = cy;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//funcao para esconder o cursor do console
void esconderCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void desenharTudo() {
    gotoxy(0, 0);

    printf("C-PAINT (Simples)  | Pincel: %c\n", pincel);
    printf("[WASD] mover | [ESPACO] desenhar | [M] trocar | [B] apagar | [L] limpar | [ESC] sair\n\n");

    // Desenho
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {

            if (i == y && j == x) {
                // Mostra o cursor com um símbolo diferente
                putchar(desenhando ? 'X' : '+');
            } else {
                putchar(tela[i][j]);
            }

        }
        putchar('\n');
    }

    printf("\nModo: %s     ", desenhando ? "Desenhando" : "Movendo");

}
//funcao para ler a entrada do teclado
void lerEntrada() {
    if (!kbhit()) return;

    char t = getch();
// Analisa a tecla pressionada
    switch (t) {
        case 'w': if (y > 0) y--; break;
        case 's': if (y < ALTURA - 1) y++; break;
        case 'a': if (x > 0) x--; break;
        case 'd': if (x < LARGURA - 1) x++; break;

        case ' ': 
            desenhando = !desenhando; 
            break;

        case 'm':
            gotoxy(0, ALTURA + 5);
            printf("Novo caractere do pincel: ");
            pincel = getche();
            break;

        case 'b':
            pincel = ' ';
            break;

        case 'l':
            iniciar();
            break;

        case 27: // ESC
            exit(0);
    }

    // Se estiver desenhando, marca na tela
    if (desenhando) {
        tela[y][x] = pincel;
    }
}