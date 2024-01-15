#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>


char *commande;
int x1;
int y1;
int x2;
int y2;


void empty_buffer(void){
    int c;
    while((c=getchar()) != EOF && c != '\n');
};

void color(int t,int f) {
    /*
    0 : noir
    1 : bleu foncé
    2 : vert
    3 : bleu-gris
    4 : marron
    5 : pourpre
    6 : kaki
    7 : gris clair
    8 : gris
    9 : bleu
    10 : vert fluo
    11 : turquoise
    12 : rouge
    13 : rose fluo
    14 : jaune fluo
    15 : blanc
     */
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
};
typedef struct{
    int x;
    int y;
    int state; //0 = chaine, 1 = libre, 2 =occupe
    int value; // -1 = NULL, 0 = X, 1 = 1 ...
    int scope;
    int back; // 1 = Haut ,2 = Droite ,3 = Bas ,4 = Gauche
    int color; // Quelle couleur
}CELL;

void display(CELL *cell){
    if (cell->scope == 1){
        color(12,15);
            if (cell->value == 0){
                printf(" X ");
            }else{
                printf(" %d ", cell->value);
            }
    }else if(cell->scope == 0 && cell->state != 2){
        if (cell->value == 0){
            color(12,0);
            printf(" X ");
        }
        else if (cell->value == 11){
            color(11,0);
            printf(" X ");
        }
        else if (cell->value == 12){
            color(2,0);
            printf(" X ");
        }
        else{
            color(15,0);
            printf(" %d ", cell->value);
        }
    }
    else if(cell->scope == 0 && cell->state == 2) {
        color(12, 0);
        if (cell->value == 0) {
            if (cell->color ==3){
                color(2,0);
                printf(" X ");
            }
            else if (cell->color == 4){
                color(11,0);
                printf(" X ");
            }
            else {
                printf(" X ");
            }
        }else {
            if (cell->color == 3 && cell->value != 11){
                color(2,0);
                printf(" %d ", cell->value);
            }
            else if (cell->value == 11){
                color(2,0);
                printf(" X ");
            }
            else if (cell->color == 4 && cell->value != 12){
                color(11,0);
                printf(" %d ", cell->value);
            }
            else if (cell->value == 12){
                color(11,0);
                printf(" X ");
            }
            else {
                printf(" %d ", cell->value);
            }
        }
    }
};

/*
void swap(int row, int column, CELL grille[row][column]){
    for(int i=0; i<row; i++){
        for(int j=0; j<column; j++){
            if(grille[i][j].color  != 0){
                printf("Chaine numero : %d\n",grille[i][j].color);
            }
        }
    }
}
*/

void menu(){
    printf("(Z) HAUT\n");
    printf("(S) BAS\n");
    printf("(D) DROITE\n");
    printf("(Q) GAUCHE\n");
    printf("(C) EXIT\n");
    printf("(B) RESET\n");
    printf("(X) SWITCH CHAINES\n");
    printf("Direction :");
}

/*
bool possible(CELL *cell, CELL *cell2){
    if (cell->value <= cell2->value){
        return TRUE;
    }else{
        return FALSE;
    }
}
*/

/*
void win(int row, int column,CELL grille[row][column]){
    int win = 0;
    int win2 = row * column;
    for(int i=0; i<row;i++){
        for(int j=0; i<column; j++){
            if (grille[i][j].state == 2){
                win += 1;
                if (win == win2){
                    printf(" VICTOIRE ");
                }
            }
            else{
                win = 0;
            }
        }
    }
}
*/


int main(){
    // def des variables coordonées pour les chaînes
    int cord1;
    int cord2;
    int cord1c1;
    int cord2c1;
    int cord1c2;
    int cord2c2;
    int reset1;
    int reset2;
    char commande;
    int color = 0;

    // ______________________Partie à remplacer pour le changement de niveau_______________________

    //Niveau 5

    // Niveau 1
    int row = 1;
    int column = 4;
    int tableau[2][4]={
            {0,1,2,3},
            {1,1,11,12},

    };
    cord1 = 0;
    cord2 = 0;

    cord1c1 = 1;
    cord2c1 = 2;

    cord1c2 = 1;
    cord2c2 = 3;

    reset1 = 0;
    reset2 = 0;

    // _________________________________________________________
    CELL grille[row][column];
    int win = 0;
    int win2 = row * column +1;

    for(int i=0; i<row; i++){ // Création de la grille par une boucle
        for(int j=0; j<column; j++){
            grille[i][j].value = tableau[i][j];
            grille[i][j].back = 0;
            if(tableau[i][j] == 0 ){ // Pour chaîne 1
                grille[i][j].state = 2;
                grille[i][j].scope = 1;
                grille[i][j].color = 1;
            }else if(tableau[i][j] == 11 || tableau[i][j] == 12){ // Pour chaîne 2 et 3
                grille[i][j].state = 2;
                grille[i][j].scope = 0;
            }else{ // Le reste des cases libres
                grille[i][j].scope = 0;
                grille[i][j].state = 1;
                grille[i][j].color = 0;
            }
        }
    }
    for(int i=0; i<row;i++){ // Affichage de la grille via la fonction display
        for(int j=0; j<column; j++){
            display(&grille[i][j]);
            if (grille[i][j].value == 0){
                x1 = i;
                y1 = j;
            }
        }
        printf("\n");
    }
    while (commande != 'C'){ // Jeu lancé
        menu(); // Menu de touches
        scanf(" %c", &commande); // Quelle touche on rentre ?
        empty_buffer(); // On vide le cache pour ne pas faire de boucle infini via scanf
        if (commande == 'D' && grille[cord1][cord2].scope == 1){ // Si D pressé
            if (grille[cord1][cord2+1].state == 1 && grille[cord1][cord2+1].value >= grille[cord1][cord2].value){
                if (color == 3){ // Si la couleur est verte
                    grille[cord1][cord2+1].color = 3; // La prochaine case devient verte
                }
                else if (color == 4){ // Si la couleur est cyan
                    grille[cord1][cord2+1].color = 4; // La prochaine case devient cyan
                }
                else if (grille[cord1][cord2].color == 1){ // Si la valeur color de la case n'a pas été modifiée
                    grille[cord1][cord2+1].color = 1; // La prochaine case devient rouge
                }
                grille[cord1][cord2+1].scope = 1; // La prochaine case prend l'affichage curseur
                grille[cord1][cord2].scope = 0; // Cette case perd l'affichage curseur
                grille[cord1][cord2+1].state = 2; // La prochaine case prend la valeur 2 (occupée)
                grille[cord1][cord2].back = 2; // La case prend la valeur 2 pour rollback
                cord2 += 1; // la coord est incrémentée de 1 (elle suit le curseur)
            }
            else if(grille[cord1][cord2+1].state == 2 && grille[cord1][cord2+1].back == 4){ // Si la prochaine case est
                // occupée et que cette prochaine case à la valeur 4 en rollback (elle vient de la direction opposée)
                grille[cord1][cord2+1].scope = 1;
                grille[cord1][cord2].scope = 0;
                grille[cord1][cord2].state = 1; // La case prend la valeur 1 (libre)
                cord2 += 1;
            }
        }
        else if (commande == 'S' && grille[cord1][cord2].scope == 1) {
            if (grille[cord1+1][cord2].state == 1 && grille[cord1+1][cord2].value >= grille[cord1][cord2].value){
                if (color == 3){
                    grille[cord1+1][cord2].color = 3;
                }
                else if (color == 4){
                    grille[cord1+1][cord2].color = 4;
                }
                else if (grille[cord1][cord2].color == 1){
                    grille[cord1+1][cord2].color = 1;
                }
                grille[cord1+1][cord2].scope = 1;
                grille[cord1][cord2].scope = 0;
                grille[cord1+1][cord2].state = 2;
                grille[cord1][cord2].back = 3;
                cord1 += 1;
            }
            else if(grille[cord1+1][cord2].state == 2 && grille[cord1+1][cord2].back == 1){
                grille[cord1+1][cord2].scope = 1;
                grille[cord1][cord2].scope = 0;
                grille[cord1][cord2].state = 1;
                cord1 += 1;
            }
        }
        else if (commande == 'Q' && grille[cord1][cord2].scope == 1) {
            if (grille[cord1][cord2-1].state == 1 && grille[cord1][cord2-1].value >= grille[cord1][cord2].value){
                if (color == 3){
                    grille[cord1][cord2-1].color = 3;
                }
                else if (color == 4){
                    grille[cord1][cord2-1].color = 4;
                }
                else if (grille[cord1][cord2].color == 1){
                    grille[cord1][cord2-1].color = 1;
                }
                grille[cord1][cord2-1].scope = 1;
                grille[cord1][cord2].scope = 0;
                grille[cord1][cord2-1].state = 2;
                grille[cord1][cord2].back = 4;
                cord2 -= 1;
            }
            else if(grille[cord1][cord2-1].state == 2 && grille[cord1][cord2-1].back == 2){
                grille[cord1][cord2-1].scope = 1;
                grille[cord1][cord2].scope = 0;
                grille[cord1][cord2].state = 1;
                cord2 -= 1;
            }
        }
        else if (commande == 'Z' && grille[cord1][cord2].scope == 1) {
            if (grille[cord1-1][cord2].state == 1 && grille[cord1-1][cord2].value >= grille[cord1][cord2].value){
                if (color == 3){
                    grille[cord1-1][cord2].color = 3;
                }
                else if (color == 4){
                    grille[cord1-1][cord2].color = 4;
                }
                else if (grille[cord1][cord2].color == 1){
                    grille[cord1-1][cord2].color = 1;
                }
                grille[cord1-1][cord2].scope = 1;
                grille[cord1][cord2].scope = 0;
                grille[cord1-1][cord2].state = 2;
                grille[cord1][cord2].back = 1;
                cord1 -= 1;
            }
            else if(grille[cord1-1][cord2].state == 2 && grille[cord1-1][cord2].back == 3){
                grille[cord1-1][cord2].scope = 1;
                grille[cord1][cord2].scope = 0;
                grille[cord1][cord2].state = 1;
                cord1 -= 1;
            }
        }
        else if (commande == 'X'){
            for(int i=0; i<row; i++){
                for(int j=0; j<column; j++){
                    grille[i][j].scope = 0;
                }
            }
            printf("U pour 2eme chaine // I pour 3eme chaine\n");
            scanf(" %c", &commande);
            if (commande == 'U'){
                for(int i=0; i<row; i++){
                    for(int j=0; j<column; j++){
                        if(grille[i][j].value  == 11){
                            grille[i][j].scope = 1;
                            grille[i][j].value = 0;
                            grille[i][j].color = 3;
                            color = 3;
                            cord1 = cord1c1;
                            cord2 = cord2c1;
                            grille[cord1c2][cord2c2].value = 12;
                        }
                        }
                    }
                }
            if (commande == 'I'){
                for(int i=0; i<row; i++){
                    for(int j=0; j<column; j++){
                        if(grille[i][j].value  == 12){
                            grille[i][j].scope = 1;
                            grille[i][j].value = 0;
                            grille[i][j].color = 4;
                            color = 4;
                            cord1 = cord1c2;
                            cord2 = cord2c2;
                            grille[cord1c1][cord2c1].value = 11;
                        }
                    }
                }
            }
            }
        else if (commande == 'B'){
            for(int i=0; i<row; i++){ // Création de la grille par une boucle
                for(int j=0; j<column; j++){
                    grille[i][j].value = tableau[i][j];
                    grille[i][j].back = 0;
                    if(tableau[i][j] == 0 ){ // Pour chaîne 1
                        grille[i][j].state = 2;
                        grille[i][j].scope = 1;
                        grille[i][j].color = 1;
                    }else if(tableau[i][j] == 11 || tableau[i][j] == 12){ // Pour chaîne 2 et 3
                        grille[i][j].state = 2;
                        grille[i][j].scope = 0;
                    }else{ // Le reste des cases libres
                        grille[i][j].scope = 0;
                        grille[i][j].state = 1;
                        grille[i][j].color = 0;
                    }
                }
            }
            cord1 = reset1;
            cord2 = reset2;
        }

        for(int i=0; i<row;i++){ // à la fin de la boucle while on affiche de nouveau la grille avec les changements
            for(int j=0; j<column; j++){
                display(&grille[i][j]);
                if (grille[i][j].value == 0){
                    x1 = i;
                    y1 = j;
                }
            }
            printf(" \n");
        }
        for(int i=0; i<row;i++){ // On check si la condition de victoire est remplie
            for(int j=0; j<column; j++){
                if (grille[i][j].color != 0){
                    win += 1;
                }
            }
        }
        if (win >= win2){ // Si toutes les cases sont colorées ! On gagne !
            printf(" !! C EST UNE VICTOIRE !!\n ");
            return 0;
        }
        else {
            win = 1;
        }
    }

};

