#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#elif _linux_
    #include <unistd.h>
#elif _APPLE_
    #include <unistd.h>
#endif

// CONNECT FOUR by Umut Hastan

// PLATFORM TYPES

enum Piattaforme{ 
    WINDOWS,
    LINUX,
    MACOS
};

// GAME STATE

typedef struct {
    bool vittoria;
    char griglia[6][7];
    bool turno;
    int posizione;
} Game;

// PROTOTYPE

void menu();
void nuovaPartita();
void generazioneGriglia(Game *g);
void stampaGriglia(Game *g);
void logicaGioco(Game *g);
void piazzaPedina(Game *g);
void controlloVittoria(Game *g);
void stampaVittoria(Game *g);

// PLATFORM SPECIFIC FUNCTIONS

enum Piattaforme piattaforma;

void clearScreen(){
    if(piattaforma == WINDOWS){
        system("cls");
    }
    else{
        system("clear");
    }
}

void sleepExecution(int milliseconds){
    if(piattaforma == WINDOWS){
        Sleep(milliseconds);
    }
    else{
        usleep(milliseconds * 1000);
    }
}

// MAIN LOGIC

int main(){

menu();
return 0;

}

// FUNCTIONS

void menu(){

    // PLATFORM DETECTION 

    #ifdef _WIN32
        piattaforma = WINDOWS;
    #elif _linux_
        piattaforma = LINUX;
    #elif _APPLE_
        piattaforma = MACOS;
    #endif

    int sceltaMenu;
    
    do {
        clearScreen();
        printf("-----   MAIN MENU   -----\n");
        printf("1.\tNew Game\n");
        printf("2.\tQuit\n");
        printf("-----   MAIN MENU   -----\n");
        
        sceltaMenu = getch();
        
        if(sceltaMenu == '1'){
            clearScreen();
            printf("-----   NEW GAME LOADING   -----\n\n");
            sleepExecution(2000);
            clearScreen();
            nuovaPartita();
        }
        else if(sceltaMenu == '2'){
            clearScreen();
            printf("-----   GOOD BYE   -----\n\n");
            sleepExecution(2000);
            clearScreen();
        }
        else {
            clearScreen();
            printf("Invalid input.");
            sleepExecution(2000);
            clearScreen();
        }
    } while (sceltaMenu != '1' && sceltaMenu != '2');
}

void nuovaPartita() {

    Game game;

    game.vittoria = false;
    game.turno = true;
    game.posizione = 0;

    generazioneGriglia(&game);
    stampaGriglia(&game);
}

void generazioneGriglia(Game *g) {
    for(int i=0; i<6; i++){
        for(int l=0; l<7; l++){
            g->griglia[i][l] = ' ';
        }
    }
}

void stampaGriglia(Game *g) {
    clearScreen();
    if(g->turno) {
        printf("Player 1s turn\n\n");
    }
    else {
        printf("Player 2s turn\n\n");
    }
    
    for(int i=0;i<g->posizione;i++) {
        printf("   ");
    }
    printf(" *");

    for(int i=0; i<6; i++) {
        printf("\n");
        for(int l=0; l<7; l++){
            char c = g->griglia[i][l];
            if (c == ' ') {
                printf("[ ]");
            }
            else if (c == 'X') {
                printf("[\x1b[31mX\x1b[0m]");
            }
            else if (c == 'O') {
                printf("[\x1b[34mO\x1b[0m]");
            }
        }
    }
    printf("\n\n");
    logicaGioco(g);
}

void logicaGioco(Game *g) {
    int input;
    input = getch();
    if(input == 75) { // Freccia Sinistra
        g->posizione--;
        if(g->posizione < 0) {
            g->posizione = 6;
        }
    }
    else if(input == 77) { // Freccia Destra
        g->posizione++;    
        if(g->posizione > 6) {
            g->posizione = 0;
        }    
    }
    else if(input == 13 && g->griglia[0][g->posizione] == ' ') { // Invio
        piazzaPedina(g);
        g->turno = !g->turno;
        g->posizione = 0;
    }
    stampaGriglia(g);
}

void piazzaPedina(Game *g){
    // Determina la pedina del giocatore corrente
    char piece = g->turno ? 'X' : 'O';
    
    // Rileva e occupa la prima posizione libera nella colonna selezionata
    for(int i=5;i>=0;i--) {
        if(g->griglia[i][g->posizione] == ' ') {
            g->griglia[i][g->posizione] = piece;
            break;
        }
    }
    controlloVittoria(g);
}

void controlloVittoria(Game *g) {
    // Resetta lo stato di vittoria
    g->vittoria = false;

    // La griglia e' 6 righe x 7 colonne 
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 7; c++) {
            char p = g->griglia[r][c];
            if (p == ' ') continue; // Salta le celle vuote

            // Controlla orizzontale a destra
            if (c <= 3 &&
                g->griglia[r][c+1] == p &&
                g->griglia[r][c+2] == p &&
                g->griglia[r][c+3] == p) {
                g->vittoria = true;
                stampaVittoria(g);
                return;
            }

            // Controlla verticale verso il basso
            if (r <= 2 &&
                g->griglia[r+1][c] == p &&
                g->griglia[r+2][c] == p &&
                g->griglia[r+3][c] == p) {
                g->vittoria = true;
                stampaVittoria(g);
                return;
            }

            // Controlla diagonale verso il basso-destra
            if (r <= 2 && c <= 3 &&
                g->griglia[r+1][c+1] == p &&
                g->griglia[r+2][c+2] == p &&
                g->griglia[r+3][c+3] == p) {
                g->vittoria = true;
                stampaVittoria(g);
                return;
            }

            // Controlla diagonale verso l'alto-destra
            if (r >= 3 && c <= 3 &&
                g->griglia[r-1][c+1] == p &&
                g->griglia[r-2][c+2] == p &&
                g->griglia[r-3][c+3] == p) {
                g->vittoria = true;
                stampaVittoria(g);
                return;
            }
        }
    }
}

void stampaVittoria(Game *g) {
    if(g->vittoria) {
        clearScreen();
        if(g->turno) {
            printf("--- PLAYER 1 WON ---");
        }
        else {
            printf("--- PLAYER 2 WON ---");
        }
        g->turno = true;
        g->posizione = 0;
        sleepExecution(2000);
        menu();
    }
}
