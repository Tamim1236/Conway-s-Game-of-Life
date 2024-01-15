#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define WIDTH 30 
#define HEIGHT 60
#define PAUSE 5

#define BACKGROUND '-'
#define CELL 'O' 

typedef enum{
  DEAD,
  ALIVE,
} State;

typedef struct{
  State state;
} Cell;

Cell grid[WIDTH][HEIGHT] = {0}; // an array of cells

void create_grid(){
  for(size_t i = 0; i < WIDTH; i++){
    for(size_t j = 0; j < HEIGHT; j++){
      if(rand() % 2 == 0 && rand() % 6 == 0){ // random cells are set to be alive at the beginning
        grid[i][j].state = ALIVE;
      }
      else{
        grid[i][j].state = DEAD; 
      }
    }
  }
}

void generate_next(){
  for(size_t i = 0; i < WIDTH; i++){
    for(size_t j = 0; j < HEIGHT; j++){
      
      // need to iterate over all 8 neightbors of the cell
      int num_alive = 0;
      for(int k = -1; k <= 1; k++){
        for(int l = -1; l <= 1; l++){
          if(k == 0 && l == 0) continue;

          // let elements wrap around
          int row = (i+k) % WIDTH; //HEIGHT;
          int col = (j+l) % HEIGHT;
          if(grid[row][col].state == ALIVE){
            num_alive++;
          }
        }
      }

      //state changes based on number of alive neighbors
      switch(num_alive){
        case 0:
        case 1:
          grid[i][j].state = DEAD;
          break;
        case 2:
          break;
        case 3:
          if(grid[i][j].state == DEAD){
            grid[i][j].state = ALIVE;
          }
          break;
        default:
          grid[i][j].state = DEAD; // any cell with more than 3 live neighbors dies by overpopulation
          break;
      }
    }
  }
}

int print_grid(){
  int num_alive = 0;
  
  for(size_t i = 0; i < WIDTH; i++){
    for(size_t j = 0; j < HEIGHT; j++){
      if(grid[i][j].state == ALIVE){
        num_alive++;
        printf("%c", CELL);
      } else{
        printf("%c", BACKGROUND);
      }
    }
    printf("\n");
  }

  return num_alive;
}

int main(){
  srand(time(NULL)); // randomize seed
  create_grid();
  
  while(print_grid() != 0){
    Sleep(PAUSE * 5); //100);
    generate_next();
    system("cls");
  }

  return 0;
}