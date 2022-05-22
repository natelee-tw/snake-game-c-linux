#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 20
#define M 40

int i, j, Field[N][M], x, y, Gy, Head, Tail, Game, Frogs;

void snakeInitialization(){
    for (i=0; i<N; i++){
        for(j=0; j<M; j++){
            Field[i][j] = 0;
        }
    }
    x = N/2;
    y = M/2;
    Head = 5;
    Tail = 1;
    Gy = y;
    Game = 0; //game ends when Game = 1
    Frogs = 0;

    for (i=0; i<Head; i++){
        Gy++;
        Field[x][Gy-Head] = i+1;
    }
}

void generateFrog(){
    srand(time(0));
    int a = 1 + rand() % (N-2); // from 1 to 19
    int b = 1 + rand() % (M-2); // from 1 to 39

    if (Frogs == 0 && Field[a][b] == 0) {
        Field[a][b] = -1;
        Frogs = 1;
    }
}

void print(){
    // draw top lime
    for (i=0; i<=M+1; i++){
        if (i==0){
            printf("%c", 'T');
        }
        else if (i==M+1){
            printf("%c", 'T');
        }
        else {
            printf("%c", '=');
        }
    }
    printf("\n");

    // draw body
    for (i=0; i<N; i++){
        printf("%c", '|');
        for (j=0; j<M; j++){
            if (Field[i][j] == 0) {
                printf(" ");
            }
            if (Field[i][j] > 0 && Field[i][j] != Head){
                printf("%c", '*');
            } // body part of snake
            if (Field[i][j] == Head) {
                printf("%c", 'X');
            }
            if (Field[i][j] == -1) {
                printf("%c", 'F');
            }
            if (j==M-1) {
                printf("%c\n", '|');}


        }
    }

    // draw bottom line
    for (i=0; i<=M+1; i++){
        if (i==0){
            printf("%c", 'T');
        }
        else if (i==M+1){
            printf("%c", 'T');
        }
        else {
            printf("%c", '=');
        }
    }
    printf("\n");
}

void ResetScreenPosition(){
    system("clear");
    printf("%c[%d;%df",0x1B,0,0);
}

int main(){
    snakeInitialization();

    while (Game == 0){
        generateFrog();
        print();
        sleep(1);
        ResetScreenPosition();
    }
}