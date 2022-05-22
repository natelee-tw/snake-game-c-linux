#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <curses.h> //linux replacement for conio.h
#include <ctype.h>
#include <termios.h>
#include <fcntl.h>

#define N 20
#define M 40

int i, j, Field[N][M], x, y, Gy, Head, Tail, Game, Frogs, a, b, var, dir, score, HighScore;
float Speed;

FILE *f;

void snakeInitialization(){
    f=fopen("highscore.txt", "r");
    fscanf(f, "%d", &HighScore);
    fclose(f);

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
    Game = 1; //game ends when Game = 0
    Frogs = 0;
    dir = 'd';
    score = 0;
    Speed = 0.1;

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
    printf("Snake in C, Linux\n\n");

    printf("Movement - Up: W, Down: S, Left: A, Right: D\n");

    // draw top lime
    for (i=0; i<=M+1; i++){
        if (i==0){
            printf("%c", 'X');
        }
        else if (i==M+1){
            printf("%c", 'X');
        }
        else {
            printf("%c", '-');
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
            printf("%c", 'X');
        }
        else if (i==M+1){
            printf("%c", 'X');
        }
        else {
            printf("%c", '-');
        }
    }
    printf("\nCurrent Score: %d", score);
    printf("\nHigh Score: %d", HighScore);

    printf("\n\nMengyong Lee, May 2022\n");
}

void resetScreenPosition(){
    system("clear");
    printf("%c[%d;%df",0x1B,0,0);
}

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

void fracSleep(float sec) {
    struct timespec ts;
    ts.tv_sec = (int) sec;
    ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
    nanosleep(&ts,NULL);
}

void gameOver(){
    printf("\a");
    Game = 0;
    if (score > HighScore) {
        system("pause");
        f=fopen("highscore.txt", "w");
        fprintf(f, "%d", score);
        fclose(f);
    }

}

void movement(){
    char var;
    var = getechNoBlock();
    var = tolower(var);

    if (((var == 'd' || var == 'a') || (var == 'w' || var == 's'))
        && (abs(dir-var) > 5)){
        dir = var;
    }
    if (dir == 'd') {
        y++;
        if (y==M-1) {
            y=0;
        }
        Head++;
    }
    if (dir == 'a') {
        y--;
        if (y==0) {
            y=M-1;
        }
        Head++;
    }
    if (dir == 'w') {
        x--;
        if (x==0) {
            x=N-1;
        }
        Head++;
    }
    if (dir == 's') {
        x++;
        if (x==N-1) {
            x=0;
        }
        Head++;
    }
    // ate a frog
    if(Field[x][y] == -1) {
        printf("\a");
        Frogs = 0;
        Tail -= 2;
        score += 5;
        Speed *= 0.90;
    }
    // game over
    if (Field[x][y] != 0 && Field[x][y] != -1) {
        gameOver();
    }
    Field[x][y] = Head;
}

void tailRemove(){
    for(i=0; i<N; i++){
        for(j=0; j<M; j++) {
            if (Field[i][j] == Tail) {
                Field[i][j] = 0;
            }
        }
    }
    Tail ++;
}

int main(){
    snakeInitialization();

    while (Game == 1){
        print();
        generateFrog();
        movement();
        tailRemove();
        fracSleep(Speed); //Half second delay
        resetScreenPosition();
    }
    print();
    printf("\n\n----------Game Over!!!!----------\n\n");
    if (score > HighScore) {
        printf("\nNew High Score %d!!!\n\n", score);
    }

}