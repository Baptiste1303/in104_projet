#include "dfs.h"

int nb_episodes = 100;

int dfs(int row, int col){
    int* current = &visited[row][col]; // pas plutot ** ? 

    if(*current == goal){
        return 1;
    }else if(*current == unknown){
        *current = known;

        if (dfs(row, col-1)){
            *current = crumb;
            return 1;
        } else if (dfs(row+1, col)){
            *current = crumb;
            return 1;
        }  else if (dfs(row, col+1)){
            *current = crumb;
            return 1;
        }  else if (dfs(row-1, col)){
            *current = crumb;
            return 1;
        }

    }

    return 0;
}


int main(){
   mazeEnv_make("../data/maze.txt");
   init_visited();

   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   mazeEnv_render();
   dfs(start_row,start_col);
   add_crumbs();
   mazeEnv_render();

    // Training area //

    // Q init 

    /*
    q_init(); // bug ici a regler
    r_init();
    
    

    for (int episode = 0 ; episode < nb_episodes ; ++episode){
        mazeEnv_reset();


        while(stepOut.done != 1){


        }


    }

    


    q_destroy();
    mazeEnv_destroy();
    visited_destroy();

    */

   return 0;
}

