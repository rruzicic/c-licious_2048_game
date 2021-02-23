#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// defining output colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define X 4 // width
#define Y 4 // height 

void initGame(int game[X][Y]);                      //sets values of the matrix to 0 and ads 2 blocks in random coordinates
void addRandom(int game[X][Y]);                     //adds one random number(2 or 4) to the matrix
void init(int game[X][Y]);                          //sets all the values of matrix to 0 - NOT USED
int checkValidGame(int game[X][Y]);                 //used for checking if the game is finished
void print(int game[X][Y]);                         //prints out the matrix
// the folowing sum and move functions are used for controling the game
// I've separated them because one command needs to triger move function sum function and another move function because sum function can leave zeroes on the wrong places
// example 2 2 2 2 (moveRight) -> 2 2 2 2 (sumRight) -> 0 4 0 4 (moveRight) -> 0 0 4 4
void moveLeft(int game[X][Y]);
void sumLeft(int game[X][Y]);
void moveRight(int game[X][Y]);
void sumRight(int game[X][Y]);
void moveUp(int game[X][Y]);
void sumUp(int game[X][Y]);
void moveDown(int game[X][Y]);
void sumDown(int game[X][Y]);
// checks if the matrix is blocked in one direction
int isBlockedUp(int game[X][Y]);
int isBlockedDown(int game[X][Y]);
int isBlockedLeft(int game[X][Y]);
int isBlockedRight(int game[X][Y]);

int isEqual(int game[X][Y], int copy[X][Y]);        //checks if 2 matrices are the same


// TODO: 
// 1. scoring system
// 2. move all functions below main -- DONE
// 3. GUI - yup this will take a while
// 4. DO NOT add new number when moving is blocked -- DONE
// 5. make the game scalable 

int main()
{
    /*int game[X][Y] = {
    {2, 0, 0, 4},
    {8, 0, 0, 4},
    {0, 0, 0, 0},
    {0, 0, 2, 0}*/
    srand(time(NULL));
    system("clear");
    int game[X][Y];
    initGame(game);
    print(game);
    
    do{
        char c;
        printf("Enter a character: ");
        scanf(" %c",&c);  
        
        if (c == 'w'){
            if(isBlockedUp(game) == 1){ continue; }
            moveUp(game);
            sumUp(game);
            moveUp(game);
            addRandom(game);
            system("clear");
            print(game);
        } else if(c == 'a'){
            if(isBlockedLeft(game) == 1){ continue; }
            moveLeft(game);
            sumLeft(game);
            moveLeft(game);
            addRandom(game);
            system("clear");

            print(game);
        } else if(c == 's'){
            if(isBlockedDown(game) == 1){ continue; }
            moveDown(game);
            sumDown(game);
            moveDown(game); 
            addRandom(game);
            system("clear");
            
            print(game);
        } else if(c == 'd'){
            if(isBlockedRight(game) == 1){ continue; }
            moveRight(game);
            sumRight(game);
            moveRight(game);
            addRandom(game);
            system("clear");
            
            print(game);
        } else{
            printf("Invalid character!\n");
        }
        
    }while(checkValidGame(game));
    printf(ANSI_COLOR_RED "GAME OVER!" ANSI_COLOR_RESET);
    return(0);
}

void initGame(int game[X][Y]){
    for(int i = 0; i < X; i++){                             // initialising matrix with the value of 0
        for(int j = 0; j < Y; j++){
            game[i][j] = 0;
        }
    } 
    srand(time(NULL));
    int x_rand1 = rand() % 4;                               // finding a random coordinate
    int y_rand1 = rand() % 4;
    game[x_rand1][y_rand1] = 2 * ((rand()%2) + 1);          // setting a value of random coordinate to 2 or 4
    int x_rand2, y_rand2;
    do{
        x_rand2 = rand() % 4;
        y_rand2 = rand() % 4;
    }while(x_rand1 == x_rand2 && y_rand1 == y_rand2);       // finding a second random coordinate that can't be the same as the first one, hence the do while loop
    game[x_rand2][y_rand2] = 2 * ((rand()%2) + 1);
}
void addRandom(int game[X][Y]){    
    srand(time(NULL));
    int x_rand = 0, y_rand = 0;
    do{
        x_rand = rand() % 4;
        y_rand = rand() % 4;
    }while(game[x_rand][y_rand] != 0);
    game[x_rand][y_rand] = 2 * ((rand()%2) + 1);

}
void init(int game[X][Y]){
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            game[i][j] = 0;
        }
    }  
}
int isBlockedUp(int game[X][Y]){ //
    int copy[X][Y];

    memcpy(copy, game, X*Y*sizeof(int));
    moveUp(copy);
    sumUp(copy);
    moveUp(copy);
    if(isEqual(game, copy)){ return 1; }
    return 0;
}
int isBlockedDown(int game[X][Y]){ //
    int copy[X][Y];

    memcpy(copy, game, X*Y*sizeof(int));
    moveDown(copy);
    sumDown(copy);
    moveDown(copy);

    if(isEqual(game, copy)){ return 1; }
    return 0;
}
int isBlockedLeft(int game[X][Y]){ //
    int copy[X][Y];

    memcpy(copy, game, X*Y*sizeof(int));
    moveLeft(copy);
    sumLeft(copy);
    moveLeft(copy);
    
    if(isEqual(game, copy)){ return 1; }
    return 0;
}
int isBlockedRight(int game[X][Y]){ //
    int copy[X][Y];

    memcpy(copy, game, X*Y*sizeof(int));
    moveRight(copy);
    sumRight(copy);
    moveRight(copy);
    
    if(isEqual(game, copy)){ return 1; }
    return 0;
}
int isEqual(int game[X][Y], int copy[X][Y]){ // 0 - not equal, 1 - equal
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            if(game[i][j] != copy[i][j]){
                return 0;
            }
        }
    }
    return 1;
}
int checkValidGame(int game[X][Y]){

    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            if(game[i][j] == 0){
                return 1;
            }
        }
    }

    int copy[X][Y];
    memcpy(copy, game, X*Y*sizeof(int));

    moveUp(copy);
    sumUp(copy);
    moveUp(copy);

    moveDown(copy);
    sumDown(copy);
    moveDown(copy); 

    moveLeft(copy);
    sumLeft(copy);
    moveLeft(copy);

    moveRight(copy);
    sumRight(copy);
    moveRight(copy);
    /* program does all 4 operations(UP, DOWN, LEFT, RIGHT) on a copy of the original matrix 
       an if the outcome is the same then the game is over
    */
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            if(game[i][j] != copy[i][j]){
                return 1;
            }
        }
    }
    return 0;
}
void print(int game[X][Y]){
    for(int i = 0; i < X; i++){
        printf(ANSI_COLOR_GREEN "+-------+-------+-------+-------+\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "|" ANSI_COLOR_RESET);
        for(int j = 0; j < Y; j++){
            if(game[i][j] == 0){
                printf("%d\t", game[i][j]); printf(ANSI_COLOR_GREEN "|" ANSI_COLOR_RESET);
            }else{
                 printf(ANSI_COLOR_RED "%d\t" ANSI_COLOR_RESET, game[i][j]); printf(ANSI_COLOR_GREEN "|" ANSI_COLOR_RESET);
            }
        }
        printf("\n");
    }
    printf(ANSI_COLOR_GREEN "+-------+-------+-------+-------+\n" ANSI_COLOR_RESET);
}
void moveLeft(int game[X][Y]){
    for(int i = 0; i < X; i++){

        for(int j = 0; j < Y; j++){
            if(game[i][j] == 0){
                for(int k = j; k < Y; k++){
                    if(game[i][k] != 0){
                        game[i][j] = game[i][k];
                        game[i][k] = 0;
                        break;
                    }
                    
                }
            }
        }

    }
}
void sumLeft(int game[X][Y]){
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y-1; j++){
            if(game[i][j] != 0 && game[i][j+1] == game[i][j]){
                game[i][j] = 2 * game[i][j];
                game[i][j+1] = 0;
                
            }
        }
    }
}
void moveRight(int game[X][Y]){
    for(int i = 0; i < X; i++){

        for(int j = Y-1; j >= 0; j--){
            if(game[i][j] == 0){
                for(int k = j; k >= 0; k--){
                    if(game[i][k] != 0){
                        game[i][j] = game[i][k];
                        game[i][k] = 0;
                        break;
                    }
                    
                }
            }
        }

    }
}

void sumRight(int game[X][Y]){
    for(int i = 0; i < X; i++){
        for(int j = Y-1; j >= 1; j--){
            if(game[i][j] != 0 && game[i][j-1] == game[i][j]){
                game[i][j] = 2 * game[i][j];
                game[i][j-1] = 0;
            }
        }
    }
}
void moveUp(int game[X][Y]){
    for(int i = 0; i < X; i++){

        for(int j = 0; j < Y; j++){
            if(game[j][i] == 0){
                for(int k = j; k < Y; k++){
                    if(game[k][i] != 0){
                        game[j][i] = game[k][i];
                        game[k][i] = 0;
                        break;
                    }
                    
                }
            }
        }

    }
}

void sumUp(int game[X][Y]){
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y-1; j++){
            if(game[j][i] != 0 && game[j+1][i] == game[j][i]){
                game[j][i] = 2 * game[j][i];
                game[j+1][i] = 0;
            }
        }
    }
}

void moveDown(int game[X][Y]){
    for(int i = 0; i < X; i++){

        for(int j = Y-1; j >= 0; j--){
            if(game[j][i] == 0){
                for(int k = j; k >= 0; k--){
                    if(game[k][i] != 0){
                        game[j][i] = game[k][i];
                        game[k][i] = 0;
                        break;
                    }
                    
                }
            }
        }

    }
}
void sumDown(int game[X][Y]){
    for(int i = 0; i < X; i++){
        for(int j = Y-1; j >= 1; j--){
            if(game[j][i] != 0 && game[j-1][i] == game[j][i]){
                game[j][i] = 2 * game[j][i];
                game[j-1][i] = 0;
            }
        }
    }
}
