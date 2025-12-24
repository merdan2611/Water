#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
int ROW;
int COL;
int map[20][20] = {0};
int visited[20][20] = {0};
int source_i, source_j;
int visitedFlow[20][20] = {0};


void createMap(){
    for(int i = 0; i < ROW ; i++){
        for(int j = 0; j < COL ; j++){
            if(i == 0 || j == 0 || j == COL -1 || i == ROW -1 ){
                map[i][j] = 1 ; 
            }
        }       
    }
}
void drawMap(){
    for (int i = -1; i < ROW; i++){
        if(i>-1){printf("%2d  ", i);}else if(i==-1){printf("    ");}
        
        for(int j = 0; j < COL ; j++){
            if(i<0){printf("%2d ", j);}
            if(i>-1){
                if(map[i][j]==1){
                    printf(" 0 ");
                }else if(map[i][j]==0){
                    printf(" * ");
                }else if(map[i][j]== -1){
                    printf(" # ");
                }else if(map[i][j]==9){
                    printf(" H ");
                }else if(map[i][j]==10){
                    printf(" K ");
                }else if(map[i][j]==2){
                    printf(" | ");
                }else if(map[i][j]==3){
                    printf(" - ");
                }else if(map[i][j]==4){
                    printf(" T ");    
                }else if(map[i][j]==6){
                    printf(" L ");
                }else if(map[i][j]==7){
                    printf(" J ");
                }else if(map[i][j]==8){
                    printf(" + ");
                }
            }
        
        }
        printf("\n");
    }
    
}
int checkSourceAvailable (int map[20][20], int row, int col){
    int count= 0;
    for (int x= 0; x<3; x++){
        for(int y=0; y<2; y++){
            if(map[row+y][col+x]==0){
                count +=1;
            }
        }
    }
    
    int count_1= 0;
    for (int x= 0; x<3; x++){
        for(int y=0; y<2; y++){
            if(map[row+y][col-x]==0){
                count_1 +=1;
            }
        }
    }
    if(count_1==5 || count==5 || (map[row][col-1]==0 )){
        return 1;
    }else {
        return 0;
    }
    
}
int checkAvailable (int map[20][20], int row, int col){
    int count= 0;
    for (int x= 0; x<3; x++){
        for(int y=0; y<2; y++){
            if(map[row-x][col+y]==0){
                count +=1;
            }
        }
    }
    
    int count_1= 0;
    for (int x= 0; x<3; x++){
        for(int y=0; y<2; y++){
            if(map[row-x][col-y]==0){
                count_1 +=1;
            }
        }
    }
    if(count_1==6 || count==6 || map[row-1][col]==0 ){
        return 1;
    }else {
        return 0;
    }
    
}
void placeSource (int map[20][20]){
    int rand_i = rand() % (ROW-2) + 1;
    int rand_j = rand() % (COL-2) + 1;
    if(rand_i<3 && checkSourceAvailable(map, rand_i, rand_j)==1){

        map[rand_i][rand_j] = 10;
        source_i= rand_i;
        source_j= rand_j;
        
    }else{
        placeSource(map);
    }

}
void placeEndpoint(int map[20][20]){
    int rand_i = rand() % (ROW-2) + 1;
    int rand_j = rand() % (COL-2) + 1;
    if(rand_i>(ROW-4) && checkAvailable(map, rand_i, rand_j)==1){
        map[rand_i][rand_j] = 9;
    }else{
        placeEndpoint(map);
    }

}
void placeObstacle (int map[20][20]){
    
    int obstacleCount = (ROW*COL)/5;

    for (int x =0; x<obstacleCount; x++){
        int rand_i = rand() % (ROW-2) + 1;
        int rand_j = rand() % (COL -2) + 1;
        map[rand_i][rand_j] = -1;
    }
}

void clearMap(int map[20][20]){
    for(int x=0; x<ROW; x++){
        for(int y=0; y<COL; y++){
            map[x][y] = 0;
        }
    }
}

int checkWin(int map[20][20], int i, int j){ //function checks if the map with obstacles have a path to finish a game.
    int i_pl_1= i+1;
    int i_min_1= i-1;
    int j_pl_1= j+1;
    int j_min_1= j-1;
    if(i <= 0 || i >= ROW-1 || j <= 0 || j >= COL-1){
        return 0;
    }
    if(visited[i][j]==1){
        return 0;
    }
    visited [i][j] =1;

    if (map[i_pl_1][j]==9 || map[i_min_1][j]==9 || map[i][j_pl_1]==9 || map[i][j_min_1]==9 || map[i][j]==9){
        return 1;
    }
    if(map[i_pl_1][j]==0){
        if(checkWin(map, i+1, j )==1){
            return 1;
        }
    }
    if(map[i_min_1][j]==0){
        if(checkWin(map, i-1, j )==1){
            return 1;
        }
    }
    if(map[i][j_min_1]==0){
        if(checkWin(map, i, j_min_1 )==1){
            return 1;
        }
    }
    if(map[i][j_pl_1]==0){
        if(checkWin(map, i, j_pl_1 )==1){
            return 1;
        }
    }
    return 0;
}
int openLeft(int map[20][20], int i, int j){
    if(map[i][j]==3){return 1;}
    if(map[i][j]==10){return 1;}
    if(map[i][j]==4){return 1;}
    if(map[i][j]==7){return 1;}
    if(map[i][j]==8){return 1;}
    if(map[i][j]==9){return 1;}
    return 0;
}
int openRight(int map[20][20], int i, int j){
    if(map[i][j]==3){return 1;}  
    if(map[i][j]==10){return 1;} 
    if(map[i][j]==6){return 1;}  
    if(map[i][j]==8){return 1;}  
    if(map[i][j]==9){return 1;} 
    return 0;
}
int openUp(int map[20][20], int i, int j){
    if(map[i][j]==2){return 1;}
    if(map[i][j]==10){return 1;}
    if(map[i][j]==6){return 1;}
    if(map[i][j]==7){return 1;}
    if(map[i][j]==8){return 1;}
    if(map[i][j]==9){return 1;}
    return 0;
}
int openDown(int map[20][20], int i, int j){
    if(map[i][j]==2){return 1;}  
    if(map[i][j]==10){return 1;} 
    if(map[i][j]==4){return 1;}  
    if(map[i][j]==7){return 1;}  
    if(map[i][j]==8){return 1;}  
    if(map[i][j]==9){return 1;}  
    return 0;
}

int canFlow(int map[20][20], int i, int j, int next_i, int next_j){
    if (map[next_i][next_j] == 9){return 1;}
    if(next_i < 0 || next_i >= ROW || next_j < 0 || next_j >= COL){
        return 0;
    }
    if(next_i == i -1){
        if(openUp(map, i, j)==1 && openDown(map, next_i, next_j)== 1){
            return 1;
        }
    }
    if(next_i == i +1){
        if(openDown(map, i, j)==1 && openUp(map, next_i, next_j)== 1){
            return 1;
        }
    }
    if(next_j == j -1){
        if(openLeft(map, i, j)==1 && openRight(map, next_i, next_j)== 1){
            return 1;
        }
    }
    if(next_j == j+1){
        if(openRight(map, i, j)==1 && openLeft(map, next_i, next_j)== 1){
            return 1;
        }
    }
    return 0;
}

int Flow(int map[20][20], int i, int j){
    int i_pl_1= i+1;
    int i_min_1= i-1;
    int j_pl_1= j+1;
    int j_min_1= j-1;
    if (map[i][j]==9){
        return 1;
    }
    if (visitedFlow[i][j] == 1){return 0;}

    visitedFlow[i][j] = 1;



    
    if(i>0 && canFlow(map, i,j, i_min_1, j)==1){ //Flow up
        if(Flow(map, i_min_1, j)==1){
            return 1;
        }
    }
    if(i<ROW-1 && canFlow(map, i,j, i_pl_1, j)==1){ //Flow Down
        if(Flow(map, i_pl_1, j)==1){
            return 1;
        }
    }
    if(j< COL -1 && canFlow(map, i,j, i, j_pl_1)==1){ // Flowing Right
        if(Flow(map, i, j_pl_1)==1){
            return 1;
        }
    }
    if(j>0 && canFlow(map, i,j, i, j_min_1)==1){ //FlowLeft
        if(Flow(map, i, j_min_1)==1){
            return 1;
        }
    }
    return 0;
}

void rotatePipeUp(int map[20][20], int i, int j){
    if(map[i][j]==3){
        map[i][j]= 2;
    }
    else if(map[i][j]==4){
        map[i][j]= 6;
    }
    else if(map[i][j]==8){
        map[i][j]= 8;
    }
    else if(map[i][j]==6){
        map[i][j]= 6;
    }

}
void rotatePipeDown(int map[20][20], int i, int j){
    if(map[i][j]==3){
        map[i][j]= 2;
    }
    else if(map[i][j]==6){
        map[i][j]= 4;
    }
    else if(map[i][j]==7){
        map[i][j]= 4;
    }
    else if(map[i][j]==8){
        map[i][j]= 8;
    }
    else if(map[i][j]==4){
        map[i][j]= 4;
    }
}
void rotatePipeLeft(int map[20][20], int i, int j){
    if(map[i][j]==2){
        map[i][j]= 3;
    }
    else if(map[i][j]==4){
        map[i][j]= 7;
    }
    else if(map[i][j]==6){
        map[i][j]= 7;
    }
    else if(map[i][j]==8){
        map[i][j]= 8;
    }

}
void rotatePipeRight(int map[20][20], int i, int j){
    if(map[i][j]==2){
        map[i][j]= 3;
    }
    else if(map[i][j]==4){
        map[i][j]= 6;
    }
    else if(map[i][j]==7){
        map[i][j]= 6;
    }
    else if(map[i][j]==8){
        map[i][j]= 8;
    }
}

void turnPipes(int map[20][20], int i, int j){
    char key;
    while (1) {

        drawMap();
        printf("Use WASD to ROTATE (q to exit): \n");

        key = getch();

        if (key == 'w') {
            rotatePipeUp(map, i, j);
        }
        else if (key == 'a') {
            rotatePipeLeft(map, i, j);
        }
        else if (key == 's') {
            rotatePipeDown(map, i, j);
        }
        else if (key == 'd') {
            rotatePipeRight(map, i, j);
        }
        else if (key == 'q') {
            break; 
        }      
    }
}

void norm_map(){
    clearMap(map);
    for(int x = 0; x < ROW; x++){
        for(int y = 0; y < COL; y++){
            visited[x][y] = 0;
    }
    }
    createMap();
    
    placeObstacle(map);
    placeEndpoint(map);
    placeSource(map);
    if(checkWin(map, source_i, source_j)==1){
        drawMap();

    }else{
        for(int x=0; x<ROW; x++){
            for(int y =0; y<COL; y++){
                visited[x][y]=0;
            }
        }
        norm_map();
    }    
}

void displayPipe(){
    char pipes[6]= {'|', '-', 'T', 'L', 'J', '+' };
    for(int x=0; x<6; x++){
        printf("%d. %c  ", x+1, pipes[x]);
    }
    printf("\n");
}

void displayPipeLimited(int pipeCount[6], int pipe_choice){
    char pipes[6]= {'|', '-', 'T', 'L', 'J', '+' };
    pipeCount[pipe_choice-1] -= 1;
   
    for(int x=0; x<6; x++){
        printf("%d. %c  | %dx \n", x+1, pipes[x], pipeCount[x]);
    }
    printf("\n");
}

void placePipes(int map[20][20], int i, int j, int pipe){
    if (i <= 0 || i >= ROW-1 || j <= 0 || j >= COL-1) { printf("Invalid coordinates or on border.\n"); return; }
    if (map[i][j] != 0) { printf("Cell not empty.\n"); return; }
    switch(pipe){
        case 1: map[i][j]= 2; break;
        case 2: map[i][j]= 3; break;
        case 3: map[i][j]= 4; break;
        case 4: map[i][j]= 6; break;
        case 5: map[i][j]= 7; break;
        case 6: map[i][j]= 8; break;
        default: printf("Please select correct pipe!\n");
    }
}

void playGame(){   
    int i, j;
    norm_map();

        int running = 1;
        while (running==1) {
            displayPipe();
            printf("1. Place pipe\n2. Rotate Pipe \n3. Check win\n4. Exit\n");
            printf("Your choice: ");
            int action;
            scanf(" %d", &action);

            if (action == 1) {
                printf("Select pipe to place (1-6): ");
                int pipe_choice;
                scanf(" %d", &pipe_choice);
                printf("Enter coordinates to place pipe (row col): ");
                scanf(" %d %d", &i, &j);
                placePipes(map, i, j, pipe_choice);
                drawMap();
            }
            else if(action == 2){
                int cord_i, cord_j;
                printf("Enter the coordinates(row, col): ");
                scanf("%d %d", &cord_i, &cord_j);
                if(map[cord_i][cord_j]==0){printf("The cell is empty!"); continue;}
                else if(map[cord_i][cord_j]==9 || map[cord_i][cord_j]==10 || map[cord_i][cord_j]==1 || map[cord_i][cord_j]==-1){
                    printf("There is no pipe here!");
                    continue;
                }
                
                turnPipes(map, i, j);

            } else if (action == 3) {
                for(int x=0; x<ROW; x++){
                    for(int y=0; y<COL; y++){
                        visitedFlow[x][y] = 0;
                    }
                }
                if (Flow(map, source_i, source_j) == 1) {
                    printf("YOU WIN!\n");
                    running = 0;
                } else {
                    printf("Not yet won. Keep trying!\n");
                }
            } else if (action == 4) {
                running = 0;
            } else {
                printf("Invalid choice. Try again.\n");
            }
        }
}

void playGameHard(){
    int i, j;
    int pipe_choice= 0;
    int pipeCount[6]= {12, 8, 4, 4, 4, 1};
    
    norm_map();

        int running = 1;
        while (running==1) {
            
            printf("1. Place pipe\n2. Rotate Pipe\n3. Check win\n3. Exit\n");
            printf("Your choice: ");
            int action;
            scanf(" %d", &action);

            if (action == 1) {
                
                displayPipeLimited(pipeCount, pipe_choice);
                printf("Select pipe to place (1-6): ");
                
                scanf(" %d", &pipe_choice);
                if(pipeCount[pipe_choice-1]==0){
                    printf("PIPE LIMIT REACHED!\n");
                }else{
                    printf("Enter coordinates to place pipe (row col): ");
                    scanf(" %d %d", &i, &j);
                    placePipes(map, i, j, pipe_choice);
                    drawMap();}
            }else if(action == 2){
                int cord_i, cord_j;
                printf("Enter the coordinates(row, col): ");
                scanf("%d %d", &cord_i, &cord_j);
                if(map[cord_i][cord_j]==0){printf("The cell is empty!"); continue;}
                else if(map[cord_i][cord_j]==9 || map[cord_i][cord_j]==10 || map[cord_i][cord_j]==1 || map[cord_i][cord_j]==-1){
                    printf("There is no pipe here!");
                    continue;
                }             
                turnPipes(map, i, j);

            }
            
            else if (action == 3) {
                for(int x=0; x<ROW; x++){
                    for(int y=0; y<COL; y++){
                        visitedFlow[x][y] = 0;
                    }
                }
                if (Flow(map, source_i, source_j) == 1) {
                    printf("YOU WIN!\n");
                    running = 0;
                } else {
                    printf("Not yet won. Keep trying!\n");
                }
            } else if (action == 4) {
                running = 0;
            } else {
                printf("Invalid choice. Try again.\n");
            }
        }
}

void menu(){
    printf("1. Start Game\n");
    printf("2. Exit\n");
}

void chooseLevel (){
    printf("1. Easy(10x10)\n");
    printf("2. Normal(15x15)\n");
    printf("3. Hard(20x20)\n");
    printf("4. Exit\n");
}

void main_game() {
    int choice, choice_1, win;
    
    menu();
    printf("Your choice: ");
    scanf(" %d", &choice);
    
    if (choice == 1) {
        chooseLevel();
        printf("Your choice: ");
        scanf(" %d", &choice_1);
        
        switch (choice_1) {
            case 1:
                ROW = 10; COL = 10;
                playGame();
                break;
            case 2:
                ROW = 15; COL = 15;
                playGame();
                break;
            case 3:
                ROW = 20; COL = 20;
                playGameHard();
                break;
            default:
                printf("Invalid level choice.\n");
                return;
        }      
    }
}
int main() {
    srand(time(NULL));
    main_game();
    return 0;
}