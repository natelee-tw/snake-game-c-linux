#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curses.h> //linux replacement for conio.h
#include <ctype.h>

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

void resetScreenPosition(){
    system("clear");
    printf("%c[%d;%df",0x1B,0,0);
}


#include <termios.h>
#include <fcntl.h>
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getechNoBlock(){
    if (kbhit()){
        char c = getchar();
        ungetch(c);
        return c;
    }
    else
        return -1;
}


void movement(){
    char var;
    var = getechNoBlock();
    printf("input%c", var);
    var = tolower(var);

    if (var == 'd') {
        y++;
        Head++;
        Field[x][y] = Head;
    };
    if (var == 'a') {
        y--;
        Head++;
        Field[x][y] = Head;
    };
    if (var == 'w') {
        x--;
        Head++;
        Field[x][y] = Head;
    };
    if (var == 's') {
        x++;
        Head++;
        Field[x][y] = Head;
    };
}


int main(){

    snakeInitialization();

    while (Game == 0){
        generateFrog();
        movement();
        print();
        sleep(1);
        resetScreenPosition();
    }
}