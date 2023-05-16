#include "qlearning-tictactoe.h"

float alpha_value = 0.2 ; // learning rate 
float gamma_value = 0.990 ; // discount factor (importance given to future rewards compared to immediate rewards)
int nb_episodes = 1000;

double** q; //Table q for state-action values

//Table q for state-action values
void q_alloc(){
        q = malloc(pow(3,9) * sizeof(double*));
        for (int i = 0; i < pow(3,9) ; ++i){
                q[i] = malloc(9 * sizeof(double));
        }
}

//We choose to initialize q as a zero-filled array
void q_init(){
        q_alloc();
        for (int i = 0; i < pow(3,9) ; ++i) {
                for (int j = 0; j < 9; ++j) {
                        q[i][j]= 0 ; 
                }
        } 
}

//Free the memory allocated for q 
void q_destroy(){
        for (int i = 0; i < pow(3,9) ; ++i){
                free(q[i]);
        }
        free(q);
}

// cette fonction intialise actions en meme temps 
actions_possible recherche_actions_possible(int* grille){

        actions_possible results ;
        int number_actions = 0 ;
        int cmpt = 0 ;

        for (int i = 0 ; i < 9 ; ++i){
                if(grille[i] == 0){
                ++number_actions;
                }
        }

        int *actions = malloc(sizeof(int) * number_actions);

        for (int i = 0 ; i < 9 ; ++i){
                if(grille[i] == 0){
                actions[cmpt] = i ;
                ++cmpt;
                }
        }

        results.number_actions = number_actions ;
        results.list_actions = actions ; 

    return results;
}

void free_actions(int *actions){
    free(actions);
}

int gridTotern(int *grid){
    int tern = 0 ;

    for (int i = 0; i < 9; i++) {
        tern += grid[8 - i] * pow(10, i);
    }


    return tern;
}

int convertToDecimal(int t) {
    int decimalNumber = 0, i = 0, remainder;
    while (t != 0) {
        remainder = t % 10;
        t /= 10;
        decimalNumber += remainder * pow(3, i);
        ++i;
    }
    return decimalNumber;
}

int get_state(int *grille){
        int tern = gridTotern(grille);
        int state = convertToDecimal(tern);
        return state;
}


int inversionchiffre(int tern){
    int resultat = 0;
    int position = 1;

    while (tern != 0) {
        int chiffre = tern % 10;
        if (chiffre == 1) {
            chiffre = 2;
        } else if (chiffre == 2) {
            chiffre = 1;
        }
        resultat = resultat + chiffre * position;
        position *= 10;
        tern /= 10;
    }

    return resultat;
}

similitudes recherche_similitude(int tern){
    // A compléter pour les rotations 

    similitudes results ;
    // Inversion joueur & adversaire 
    results.mirroir = inversionchiffre(tern);


    return results; 
}

//Return the best action and its value in Q for a given state
int best_action(int state, double *max_val, actions_possible actions){
        int action_index = 0 ;
        *max_val = q[state][0]; //Passed by reference

        for (int i = 0; i < actions.number_actions; i++) {
                if (q[state][i] > *max_val) {
                *max_val = q[state][i];
                action_index = i ;
                }
        }
        return action_index;
}

int random_action(actions_possible actions){

        srand(time(NULL)); 
        int chiffre = rand() % (actions.number_actions + 1); 
        return actions.list_actions[chiffre];
}

//Update the q-table
int q_update(int action, int state, int reward, int new_state, actions_possible actions){
        // return the action that maximize q
        double max_val;
        int b_action = best_action(new_state, &max_val, actions);

        q[state][action] = q[state][action] + alpha_value * (reward + gamma_value * max_val - q[state][action]);
        return b_action;
}

// Choose the next action to take using an epsilon-greedy policy
int choose_action_epsillon_greedy(int state, double epsilon, actions_possible actions){
        //Generate a random number between 0 and 1
        double random_number = (double)rand() / RAND_MAX;

        if (random_number > epsilon) {
                // Exploitation: Choose the action with the highest Q-value for the current state
                double unused;
                int b_action=best_action(state, &unused, actions);
                return b_action;
        } else {
                // Exploration: Choose a random action
                return random_action(actions);
        }
}


//Take the reward based on the agent's current state
int* get_rewards(int *grid, actions_possible actions){
        int *rewards = malloc(sizeof(int) * 9) ;



        // DANS LA FONCTION OU ON UTILE REWARDS, PENSER A FREE REWARDS
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
        for (int i = 0; i < pow(3,9) ; ++i) {
                fprintf(fp, "%4d : ", i);
                for (int j = 0; j < 9; ++j) {
                        fprintf(fp, "%7.1f, ", q[i][j]) ; 
                }
                fprintf(fp, "\n");
        }
        fclose(fp);
}

int main(){
        //Initialize the time for the random number generator
        srand(time(0));

        

        q_init(); //Table q for state-action values
        
        int state; 
        int new_state;
        int reward;
        int state_action;
        int new_action;

        double epsilon = 0.9;
        double epsilon_end=0.01;
        
        srand(time(0));
        int *pgrille = creer_grille();

        for (int episode = 0 ; episode < nb_episodes ; ++episode){

        // grid_reset();
        reset_grid(pgrille);
        state = get_state(pgrille);
        
        // Chosing action
        actions_possible actions = recherche_actions_possible(pgrille);
        state_action = choose_action_epsillon_greedy(state, epsilon,actions);
        
        // Get reward & new state

        new_state = get_state(pgrille);
        reward = get_reward(pgrille , actions);

        new_action = q_update(state_action, state,reward, new_state, actions);
       
        // Update state and action
        state = new_state ;
        state_action = new_action ;

        // Update the grid

        placer(pgrille, state_action, 1);
        placer_alea(pgrille, 2);
        
        while(a_gagne(pgrille,1) == -1){
                state = get_state(pgrille);
        
                // Chosing action
                actions_possible actions = recherche_actions_possible(pgrille);
                state_action = choose_action_epsillon_greedy(state, epsilon,actions);
        
                // Get reward & new state

                new_state = get_state(pgrille);
                reward = get_reward(pgrille , actions);

                new_action = q_update(state_action, state,reward, new_state, actions);
       
                // Update state and action
                state = new_state ;
                state_action = new_action ;

                // Update the grid

                placer(pgrille, state_action, 1);
                placer_alea(pgrille, 2);

        }

        // reduce the exploration rate epsilon over time 
        epsilon=epsilon - exp(-8.9*epsilon);
        // ensure that the exploration rate does not go below the final rate
        epsilon=(epsilon<epsilon_end) ? epsilon_end : epsilon;

        free_actions(actions.list_actions);
        }

        //Saving the q-values to q_values.txt
        //extract_q_values();




        //Free the memory
        q_destroy();

        return 0 ;
}