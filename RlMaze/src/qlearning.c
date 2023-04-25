#include "qlearning.h"

float alpha_value = 0.1 ; // learning rate 
float gamma_value = 0.9 ; // discount factor (importance given to future rewards compared to immediate rewards)
int nb_episodes = 500;

double** q;
double** r;

//Table Q for state-action values
void q_alloc(){
        q = malloc(rows * cols  * sizeof(double*));
        action a = number_actions ;
        for (int i = 0; i < rows * cols ; ++i){
                q[i] = malloc((int)a * sizeof(double));
        }
}

//We choose to initialize Q as a zero-filled array
void q_init(){
        action a = number_actions ;
        q_alloc();
        for (int i = 0; i < rows * cols ; ++i) {
                for (int j = 0; j < (int)a; ++j) {
                        q[i][j]= 0 ; 
                }
        } 
}

//Free the memory allocated for q 
void q_destroy(){
        for (int i = 0; i < rows * cols ; ++i){
                free(q[i]);
        }
        free(q);
}

//Return the current position of the agent using the global variables state_row and state_col
int get_state(){
        return (state_row*(cols)+state_col);
}

//Return the best action and its value in Q for a given state
action best_action(int state, double *max_val){
        int action_index = 3 ;
        *max_val = q[state][3]; //Passed by reference

        for (int i = 0; i < number_actions; i++) {
                if (q[state][i] > *max_val) {
                *max_val = q[state][i];
                action_index = i ;
                }
        }
        return (enum action) action_index;
}

//Update the Q-table
action q_update(action a, int state, int reward, int new_state){
        // return the action that maximize Q
        double max_val;
        action b_action=best_action(new_state, &max_val);

        q[state][a] = q[state][a] + alpha_value * (reward + gamma_value * max_val - q[state][a]);
        return b_action;
}

// Choose the next action to take using an epsilon-greedy policy
action choose_action_epsillon_greedy(int state, double epsilon){
        //Generate a random number between 0 and 1
        double random_number = (double)rand() / RAND_MAX;

        if (random_number > epsilon) {
        // Exploitation: Choose the action with the highest Q-value for the current state
        double unused;
        action b_action=best_action(state, &unused);
        return b_action;
        } else {
        // Exploration: Choose a random action
        return env_action_sample();
        }
}

// Initialisation of the table that groups rewards based on the elements of the maze
void r_init(){
        r = malloc(rows * sizeof(int*));
        for (int i = 0; i < rows; ++i){
                r[i] = malloc(cols * sizeof(int*));
        }

        for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                        //For a wall
                        if (mazeEnv[i][j] == '+') {
                                r[i][j] = -100;
                        } 
                        //For the goal
                        else if (mazeEnv[i][j] == 'g') {
                                r[i][j] = 10000;
                        } 
                        //For the start
                        else if (mazeEnv[i][j] == 's') {
                                r[i][j] = -50;
                        } 
                        else {
                                r[i][j] = 5;
                        } 
                }
        }
}

int get_reward(int i, int j){
        return (r[i][j]);
}

//Free the memory allocated for r
void r_destroy(){
    for (int i = 0; i < rows; ++i){
                free(r[i]);
        }
    free(r);
}

//Display the maze with the action that has the maximum reward for each reachable cell in the environment
void mazeEnv_render_preferential_action(){
        int state;
        int b_action;
        double unused;
        for (int i=0; i<rows; i++) {
                for (int j=0; j< cols; j++){
                        if (mazeEnv[i][j] == '+'){
                                printf("%c ", mazeEnv[i][j]);
                        } else {
                                state=i*cols+j;
                                b_action=(int)best_action(state, &unused);
                                if (b_action==0){
                                        printf("ᴧ ");
                                } else if (b_action==1) {
                                        printf("v ");
                                } else if (b_action==2) {
                                        printf("< ");
                                } else {
                                        printf("> ");
                                }
                        }
                }
                printf("\n");
        }
        printf("\n");
}

//Saving the q-values to q_values.txt
void extract_q_values(){
        FILE* fp;
        fp = fopen("../data/q_values.txt", "w");
        if (fp == NULL) {
                printf("Erreur : Impossible d'ouvrir le fichier.\n");
                return ;
        }

        fprintf(fp, "Case |    up    |   down   |  left  |  right\n");
        for (int i = 0; i < rows * cols ; ++i) {
                fprintf(fp, "%4d : ", i);
                for (int j = 0; j < number_actions; ++j) {
                        fprintf(fp, "%8.2f, ", q[i][j]) ; 
                }
                fprintf(fp, "\n");
        }
        fclose(fp);
}

int main(){
        //Initialize the random number generator
        srand(time(0));

        mazeEnv_make("../data/maze.txt");
        //init_visited(); -> Non-functional

        printf("rows=%d, cols=%d \n", rows, cols);
        printf("number of actions :  %d \n", number_actions); 
        mazeEnv_render();

        q_init();
        r_init();
        
        action state_action ;
        action new_action ;
        int state;
        int new_state;

        float epsilon = 0.9;
        float epsilon_decay = 0.01;
        float epsilon_end=0.01;
        
        for (int episode = 0 ; episode < nb_episodes ; ++episode){

        // Maze reset
        mazeEnv_reset();
        state = get_state();
        
        // Chosing action
        state_action = choose_action_epsillon_greedy(state, epsilon);
        
        // Get reward & new state
        envOutput new_state_env ; 
        new_state_env=mazeEnv_step(state_action);
        new_state = get_state();

        new_action = q_update(state_action, state, new_state_env.reward, new_state);
       
        // Update state and action
        state = new_state ;
        state_action = new_action ;

        //update_visited(state_col,state_row);
        
        while(new_state_env.done != 1){
                state = get_state();
                state_action = choose_action_epsillon_greedy(state, epsilon);

                new_state_env = mazeEnv_step(state_action);

                new_state = get_state();
                new_action = q_update(state_action, state, new_state_env.reward, new_state);

                state = new_state ;
                state_action = new_action ;

                //update_visited(state_col,state_row); -> segmentation fault
        }
        // reduce the exploration rate epsilon over time & ensure that the exploration rate does not go below the final rate
        epsilon=(epsilon>epsilon-epsilon_decay) ? epsilon : epsilon_end;

        //add_crumbs();
        }

        //Saving the q-values to q_values.txt
        extract_q_values();

        //Display the maze with the action that has the maximum reward for each reachable cell in the environment
        mazeEnv_render_preferential_action();

        //Free the memory
        q_destroy();
        r_destroy();

        mazeEnv_destroy();
        //visited_destroy();

        return 0 ;
}