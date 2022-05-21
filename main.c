#include <stdio.h>
#define N 20
#define M 40

int i, j, Field[N][M], x, y, Gy, Head, Tail;
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

    for (i=0; i<Head; i++){
        Gy++;
        Field[x][Gy-Head] = i+1;
    }
}

void print(){
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
            if (j==M-1) {
                printf("%c\n", '|');}
        }
    }

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

int main(){
    snakeInitialization();
    print();
}