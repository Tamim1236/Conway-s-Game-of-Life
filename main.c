#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define WIDTH 25
#define HEIGHT 50
#define PAUSE 5//500 * 1000 

#define BACKGROUND '-'
#define CELL '#'

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
      grid[i][j].state = DEAD; // initially cell is dead
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
          if(((i + k >= 0 && i + k <= WIDTH) && (j + l >= 0 && j + l <= HEIGHT)) && (grid[i+k][j+l].state == ALIVE)){
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
          grid[i][j].state = DEAD;
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
  create_grid();
  
  for(size_t i = 0; i < WIDTH/5; i++){
    for(size_t j = 0; j < HEIGHT/5; j++){
      grid[i][j].state = ALIVE;
    }
  }
  
  while(print_grid() != 0){
    Sleep(PAUSE * 50); //100);
    generate_next();
    system("cls");
    // printf("NEW\n\n");
  }

  return 0;
}