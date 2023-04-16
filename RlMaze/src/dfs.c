#include "dfs.h"

int nb_episodes = 10;

int dfs(int row, int col){
    int* current = &visited[row][col];

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
   srand(time(NULL));
   mazeEnv_make("../data/maze.txt");
   init_visited();

   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions); 
   mazeEnv_render();

   /* Résolution du labyrinthe par dfs 

   //dfs(start_row,start_col);
   //add_crumbs();
   //mazeEnv_render();

   */

    // Training area //


    q_init(); 
    r_init();
    
    action state_action ;
    action new_action ;
    int state,new_state;
    
    for (int episode = 0 ; episode < nb_episodes ; ++episode){

        // Ini of the epsiode 
        mazeEnv_reset();
        
        state = get_state(state_col, start_row);
        state_action = choose_action_epsillon_greedy(state, 0.5);

        envOutput new_state_env ; 
        new_state_env = mazeEnv_step(state_action);
        new_state = get_state(new_state_env.new_col, new_state_env.new_row);
        new_action = q_update(state_action, state, new_state_env.reward, new_state);

        state = new_state ;
        state_action = new_action ;

        update_visited(new_state_env.new_col, new_state_env.new_row);

        while(new_state_env.done != 1){

            state = get_state(state_col, start_row);
            state_action = choose_action_epsillon_greedy(state, 0.5);

            envOutput new_state_env ; 
            new_state_env = mazeEnv_step(state_action);
            new_state = get_state(new_state_env.new_col, new_state_env.new_row);
            new_action = q_update(state_action, state, new_state_env.reward, new_state);

            state = new_state ;
            state_action = new_action ;

            update_visited(new_state_env.new_col, new_state_env.new_row);
            mazeEnvepisode_render_pos();

        }

        add_crumbs();

    }

    



    mazeEnv_destroy();
    visited_destroy();

    

    q_destroy();
    r_destroy();

   return 0;
}

