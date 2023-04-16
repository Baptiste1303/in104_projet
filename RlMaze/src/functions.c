#include "functions.h"

float alpha_value = 0.5 ; 
float gamma_value = 0.5 ; 


int** q;
int** r;

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

int get_state(int col, int row){
        return (col * row + col);
}

action q_update(action a, int state, int reward, int new_state){
        // return the action that maximize Q

        action n = number_actions ;
        int action_index = 0 ;
        double max_val = q[new_state][0];

        for (int i = 1; i < (int)n; i++) {
                if (q[new_state][i] > max_val) {
                max_val = q[new_state][i];
                action_index = i ;
                }
        }
    q[state][a] = q[state][a] + alpha_value * (reward + gamma_value * max_val - q[state][a]);
    return (enum action) action_index;
}

action choose_action_epsillon_greedy(int state, double epsilon){
        srand(time(NULL));
        double random_number = (double)rand() / RAND_MAX;
        action n = number_actions ;

    if (random_number > epsilon) {
        // Exploitation: Choose the action with the highest Q-value for the current state
        action best_action = 0;
        double max_q_value = q[state][0];
        for (int a = 1; a < (int)n; a++) {
            if (q[state][a] > max_q_value) {
                max_q_value = q[state][a];
                best_action = a;
            }
        }
        return best_action;
    } else {
        // Exploration: Choose a random action
        return env_action_sample();
    }

}

void q_destroy(){
    for (int i = 0; i < rows * cols ; ++i){
                free(q[i]);
        }
    free(q);
}

void r_init(){
    r = malloc(rows * sizeof(int*));
        for (int i = 0; i < rows; ++i){
                r[i] = malloc(cols * sizeof(int));
        }
        printf("Le nombre de col %d \n", cols);
        for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                        if (mazeEnv[i][j] == '+') {
                                r[i][j] = -2;
                        } 
                        else if (mazeEnv[i][j] == 'g') {
                                r[i][j] = 100;
                        } 
                        else if (mazeEnv[i][j] == 's') {
                                r[i][j] = -1;
                        } 
                        else {
                                r[i][j] = 5;
                        }
                // pas de segmentation fault ?
                // printf("La récompense de la case (%d,%d) est : %d \n" ,i,j,r[0][21]); 
                }
        }
}

void r_destroy(){
    for (int i = 0; i < rows; ++i){
                free(r[i]);
        }
    free(r);
}


int min(int a, int b){
    return (a>b) ? b : a;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

