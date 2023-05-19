#include "qlearning.h"

float alpha_value = 0.2 ; // learning rate 
float gamma_value = 0.99 ; // discount factor (importance given to future rewards compared to immediate rewards)
int nb_episodes = 1000;

double** q; //Table q for state-action values
double** r; //Table that groups rewards

//Table q for state-action values
void q_alloc(){
        q = malloc(rows * cols  * sizeof(double*));
        action a = number_actions ;
        for (int i = 0; i < rows * cols ; ++i){
                q[i] = malloc((int)a * sizeof(double));
        }
}

//We choose to initialize q as a zero-filled array
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

//Update the q-table
action q_update(action a, int state, int reward, int new_state){
        // return the action that maximize q
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
                                r[i][j] = -400;
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

//Take the reward based on the agent's current position
int get_reward(int wall){
        if (wall == 1){
                //if the agent hits a wall
                return(r[0][0]);
        }
        else{
                return (r[state_row][state_col]);
        }
        
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
                        } 
                        else if (mazeEnv[i][j] == 's'){
                                printf("\033[34ms\033[0m ");
                        }
                        else if (i == goal_row && j == goal_col){
                                printf("\033[34mg\033[0m ");
                        }
                        else {
                                state=i*cols+j;
                                b_action=(int)best_action(state, &unused);
                                if (b_action==0){
                                        printf("\033[1;31mᴧ\033[0m ");
                                } else if (b_action==1) {
                                        printf("\033[1;31mv\033[0m ");
                                } else if (b_action==2) {
                                        printf("\033[1;31m<\033[0m ");
                                } else {
                                        printf("\033[1;31m>\033[0m ");
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
                        fprintf(fp, "%7.1f, ", q[i][j]) ; 
                }
                fprintf(fp, "\n");
        }
        fclose(fp);
}

int main(){
        //Initialize the time for the random number generator
        srand(time(0));

        // For the timer
        clock_t start, end;
        double cpu_time_used;
        start = clock(); // Start measuring execution time

        mazeEnv_make("../data/maze3.txt");
        init_visited();

        printf("rows=%d, cols=%d \n", rows, cols);
        printf("number of actions :  %d \n\n", number_actions);
        
        //Display the maze
        printf("The Maze:\n");
        mazeEnv_render();

        q_init(); //Table q for state-action values
        r_init(); //Table that groups rewards
        
        action state_action ;
        action new_action ;
        int state; //Position of the agent
        int new_state;
        int reward;
        int wall; //Integer to know if there is a wall.
        int goal_state = goal_row*(cols)+goal_col;

        double epsilon = 0.9;
        double epsilon_end=0.01;
        
        for (int episode = 0 ; episode < nb_episodes ; ++episode){

        // Maze reset
        mazeEnv_reset();
        state = get_state();
        
        // Chosing action
        state_action = choose_action_epsillon_greedy(state, epsilon);
        
        // Get reward & new state
        envOutput new_state_env ; 
        new_state_env = mazeEnv_step(state_action);
        wall = new_state_env.wall ;
        new_state = get_state();
        reward = get_reward(wall);
        new_action = q_update(state_action, state,reward, new_state);
       
        // Update state and action
        state = new_state ;
        state_action = new_action ;

        update_visited(state_row,state_col);
        
        while(new_state_env.done != 1){
                
                state = get_state();
                state_action = choose_action_epsillon_greedy(state, epsilon);

                new_state_env = mazeEnv_step(state_action);

                new_state = get_state();
                wall = new_state_env.wall ;
                reward = get_reward(wall);
                new_action = q_update(state_action, state, reward, new_state);

                state = new_state ;
                state_action = new_action ;

                if (episode == nb_episodes-1 && state != goal_state){
                        //Save the last path taken by the agent
                        update_visited();
                }
        }
        // reduce the exploration rate epsilon over time 
        epsilon=epsilon - exp(-9*epsilon);
        // ensure that the exploration rate does not go below the final rate
        epsilon=(epsilon<epsilon_end) ? epsilon_end : epsilon;

        add_crumbs();
        }

        //Saving the q-values to q_values.txt
        extract_q_values();

        //Display the maze with the action that has the maximum reward for each reachable cell in the environment
        printf("Actions with the maximum reward:\n");
        mazeEnv_render_preferential_action();
        //Display the last path taken by the agent
        printf("Last path taken by the agent:\n");
        mazeEnv_render();

        //Free the memory
        q_destroy();
        r_destroy();

        mazeEnv_destroy();
        visited_destroy();

        end = clock(); // Stop measuring execution time

        // Calculate the elapsed time in seconds and display 
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Temps d'execution : %f secondes\n", cpu_time_used);

        return 0 ;
}