#include "qlearning.h"

float alpha_value = 0.1 ; 
float gamma_value = 0.7 ; 
float epsilon = 0.9;
int nb_episodes = 1;


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

void q_init(){
        action a = number_actions ;
        q_alloc();
        for (int i = 0; i < rows * cols ; ++i) {
                for (int j = 0; j < (int)a; ++j) {
                        q[i][j]= 0 ; 
                }
        } 
}

void q_destroy(){
    for (int i = 0; i < rows * cols ; ++i){
                free(q[i]);
        }
    free(q);
}

int get_state(){
        return (state_row*(cols)+state_col);
}

action q_update(action a, int state, int reward, int new_state){
        // return the action that maximize Q

        int action_index = 3 ;
        double max_val = q[new_state][3];

        for (int i = 0; i < number_actions; i++) {
                if (q[new_state][i] > max_val) {
                max_val = q[new_state][i];
                action_index = i ;
                }
        }
        q[state][a] = q[state][a] + alpha_value * (reward + gamma_value * max_val - q[state][a]);
        return (enum action) action_index;
}

action choose_action_epsillon_greedy(int state, double epsilon){
        double random_number = (double)rand() / RAND_MAX;

    if (random_number > epsilon) {
        // Exploitation: Choose the action with the highest Q-value for the current state
        action best_action = 0;
        double max_q_value = q[state][0];
        for (int a = 0 ; a < (int)number_actions; a++) {
            if (q[state][a] > max_q_value) {
                max_q_value = q[state][a];
                best_action = a;
            }
        }
        //printf("L'action choisi est celui qui maximise Q \n");
        return best_action;
    } else {
        // Exploration: Choose a random action
        //printf("L'action choisi est au hasard\n");
        return env_action_sample();
    }

}

void r_init(){
    r = malloc(rows * sizeof(int*));
        for (int i = 0; i < rows; ++i){
                r[i] = malloc(cols * sizeof(int*));
        }
        for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                        //Pour un mur
                        if (mazeEnv[i][j] == '+') {
                                r[i][j] = -100;
                        } 
                        //Pour le goal
                        else if (mazeEnv[i][j] == 'g') {
                                r[i][j] = 1000;
                        } 
                        //Pour le départ
                        else if (mazeEnv[i][j] == 's') {
                                r[i][j] = -50;
                        } 
                        else {
                                r[i][j] = 5;
                        } 
                }
        }
}

void r_destroy(){
    int i;
    for (i = 0; i < rows; ++i){
                free(r[i]);
        }
    free(r);
}

int main(){
    srand(time(NULL));
    mazeEnv_make("../data/maze.txt");
    init_visited();

    printf("%d, %d \n", rows, cols);
    printf("number of actions :  %d \n", number_actions); 
    mazeEnv_render();

    q_init();
    r_init();
    
    action state_action ;
    action new_action ;
    int state;
    int new_state;
int i=0;
        
    for (int episode = 0 ; episode < nb_episodes ; ++episode){

        // Maze reset & initialisation
        mazeEnv_reset();
        state = get_state();
        //printf("State1 : %d\n", state);
        
        // Chosing action
        
        state_action = choose_action_epsillon_greedy(state, epsilon);
        //printf("Action choisie : %d\n",(int)state_action);
        
        envOutput new_state_env ; 
        new_state_env=mazeEnv_step(state_action);

        new_state = get_state();
        //printf("State2 : %d\n", new_state);

        new_action = q_update(state_action, state, new_state_env.reward, new_state);
       
        // Update state and action
        state = new_state ;
        state_action = new_action ;

        update_visited(state_col,state_row);

        //Show current position of the agent
        mazeEnvepisode_render_pos();
        
        while(new_state_env.done != 1){
            //Compteur 
            i=i+1;

            state = get_state();
            state_action = choose_action_epsillon_greedy(state, epsilon);
            //printf("Action choisie : %d\n",(int)state_action);

            new_state_env = mazeEnv_step(state_action);

            new_state = get_state();
            //printf("State3 : %d\n", new_state);
            new_action = q_update(state_action, state, new_state_env.reward, new_state);

            state = new_state ;
            state_action = new_action ;

            //update_visited(state_col,state_row); -> segmentation fault
            //mazeEnvepisode_render_pos();
        
        }
        
        
        //add_crumbs();
   
    }
    

    mazeEnv_destroy();
    visited_destroy();
        
        //Affichage des valeurs de Q : en faire une fonction qui exporte en .txt
        for (int i = 0; i < rows * cols ; ++i) {
                printf("%d : ",i);
                for (int j = 0; j < number_actions; ++j) {
                        printf("%.2f, ", q[i][j]) ; 
                }
                printf("\n");
        }

    mazeEnvepisode_render_pos();

    printf("Nombre d'itérations=%d\n",i);

    q_destroy();
    r_destroy();
    mazeEnvepisode_destroy();
        

    return 0 ;
}