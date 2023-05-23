#include "qlearning-tictactoe.h"

float alpha_value = 0.2 ; // learning rate 
float gamma_value = 0.99 ; // discount factor (importance given to future rewards compared to immediate rewards)
int nb_episodes = 10;

double** q; //Table q for state-action values
int* reward;

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

void r_alloc(){
        reward = malloc(sizeof(int) * 9);

        if (reward == NULL) {
        // La mémoire n'a pas pu être allouée, afficher un message d'erreur
        printf("Erreur : échec de l'allocation de mémoire pour le tableau.\n");
        exit(EXIT_FAILURE);  // Quitter le programme avec un code d'erreur
    }

}

void reset_reward(){
        for (int i = 0 ; i < 10 ; ++i){
                reward[i] = 0 ;
        }
}

int checkForWin(int* grid, int player, int move) {
    // On ajoute le mouvement du joueur à la simulation du plateau
    grid[move] = player;

    // Toutes les combinaisons gagnantes possibles dans un jeu de morpion
    int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // lignes
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // colonnes
        {0, 4, 8}, {2, 4, 6}  // diagonales
    };

    // On parcourt toutes les combinaisons pour voir si le joueur a gagné
    for (int i = 0; i < 8; ++i) {
        if (grid[wins[i][0]] == player && grid[wins[i][1]] == player && grid[wins[i][2]] == player) {
            // On retire le mouvement du joueur de la simulation du plateau
            grid[move] = 0;
            return 1;
        }
    }

    // On retire le mouvement du joueur de la simulation du plateau
    grid[move] = 0;
    return 0;
}

int couldHaveBlockedWin(int* grid, int player, int chosenMove) {
    // On détermine qui est l'adversaire
    int opponent = player == 1 ? 2 : 1;

    // On ajoute le mouvement du joueur à la simulation du plateau
    grid[chosenMove] = player;

    // On va vérifier chaque position vide sur le plateau
    for (int i = 0; i < 9; ++i) {
        if (grid[i] == 0) {
            // On ajoute le mouvement de l'adversaire à la simulation du plateau
            grid[i] = opponent;

            // On vérifie si ce mouvement pourrait mener à une victoire pour l'adversaire
            if (checkForWin(grid, opponent, i)) {
                // On retire les mouvements du joueur et de l'adversaire de la simulation du plateau
                grid[i] = 0;
                grid[chosenMove] = 0;
                return 1;
            }

            // On retire le mouvement de l'adversaire de la simulation du plateau
            grid[i] = 0;
        }
    }

    // On retire le mouvement du joueur de la simulation du plateau
    grid[chosenMove] = 0;
    return 0;
}



//Take the reward based on the agent's current state
void get_rewards(int *grid){
        for (int i = 0 ; i < 10 ; ++i){
                if (grid[i] == 2 || grid[i] == 1){
                        reward[i] = -5;
                }
                else if (i == 4 && grid[i] == 0){
                        // center of the tictactoe
                        reward[i] = 50;
                }
                else if (checkForWin(grid,1,i) == 1){
                        reward[i] = 1000;
                }
                else if(couldHaveBlockedWin(grid,1,i) == 1){
                        reward[i] = -500;
                }
        }
        
}

void r_destroy(){
        free(reward);
}

// Return the ternary value representing the grid (x=1, o=2, and empty=0)
int gridTotern(int *grid){
    int tern = 0 ;
    for (int i = 0; i < 9; i++) {
        tern += grid[8 - i] * pow(10, i);
    }
    return tern;
}

// Function to convert a ternary number to decimal
int convertToDecimal(int t) {
    int decimalNumber = 0, i = 0, remainder;
    while (t != 0) {
        remainder = t % 10; // Get the rightmost digit of the ternary number
        t /= 10; // Remove the rightmost digit
        decimalNumber += remainder * pow(3, i);
        ++i;
    }
    return decimalNumber;
}

// Get the state representation of the grid
int get_state(int *grille){
        int tern = gridTotern(grille);
        int state = convertToDecimal(tern);
        return state;
}

// Invert the digits 1 and 2 in a ternary number
int invert_digits(int ternary) {
    int result = 0;
    int position = 1;

    while (ternary != 0) {
        int digit = ternary % 10;
        if (digit == 1) {
            digit = 2;
        } else if (digit == 2) {
            digit = 1;
        }
        result = result + digit * position;
        position *= 10;
        ternary /= 10;
    }

    return result;
}

// Invert the first and last digits of a ternary number
int invert_first_last(int ternary) {
    // Extract individual digits
    int digit1 = ternary / 100;
    int digit2 = (ternary / 10) % 10;
    int digit3 = ternary % 10;

    // Invert the first and last digits
    int inverted = digit3 * 100 + digit2 * 10 + digit1;

    return inverted;
}

// Find similarities in tic-tac-toe states
similitudes recherche_similitude(int* grid){
    similitudes results ;
    int tern = gridTotern(grid);

    // Extract the digit blocks from the ternary number
    int bloc1 = tern % 1000; // Last 3 digits
    int bloc2 = (tern / 1000) % 1000; // Middle 3 digits
    int bloc3 = tern / 1000000; // First 3 digits

    // Calculate the inverse of each block
    int bloc1inv = invert_first_last(bloc1);
    int bloc2inv = invert_first_last(bloc2);
    int bloc3inv = invert_first_last(bloc3);

    // Perform rotations on the ternary number
    results.rotation_90 =  convertToDecimal(bloc1 * 1000000 + bloc2 * 1000 + bloc3) ;
    results.rotation_180 = convertToDecimal(bloc1inv * 1000000 + bloc2inv * 1000 + bloc3inv);
    results.rotation_270 = convertToDecimal(bloc3inv * 1000000 + bloc2inv * 1000 + bloc1inv);

    // Perform rotations on the ternary number
    int mirroir = invert_digits(tern);
    results.mirroir = convertToDecimal(mirroir);

    return results; 
}

//Return the best action and its value in Q for a given state
int best_action(int state, double *max_val){
        int action_index = 0 ;
        *max_val = q[state][0]; //Passed by reference

        for (int i = 0; i < 9; i++) {
                if (q[state][i] > *max_val) {
                *max_val = q[state][i];
                action_index = i ;
                }
        }
        return action_index;
}

int random_action(){
        // Generate a random number within the range of available actions
        int chiffre = rand() % (9 + 1); 
        return chiffre;
}

//Update the q-table
int q_update(int action, int state, int new_state, int* grid){
        // return the action that maximize q
        double max_val;
        int b_action = best_action(new_state, &max_val);

        similitudes other_state = recherche_similitude(grid);

        q[state][action] = q[state][action] + alpha_value * ( reward[action] + gamma_value * max_val - q[state][action]);
        q[other_state.mirroir][action] = q[other_state.mirroir][action] + alpha_value * ( reward[action] + gamma_value * max_val - q[other_state.mirroir][action]);
        q[other_state.rotation_90][action] = q[other_state.rotation_90][action] + alpha_value * ( reward[action] + gamma_value * max_val - q[other_state.rotation_90][action]);
        q[other_state.rotation_180][action] = q[other_state.rotation_180][action] + alpha_value * ( reward[action] + gamma_value * max_val - q[other_state.rotation_180][action]);
        q[other_state.rotation_270][action] = q[other_state.rotation_270][action] + alpha_value * ( reward[action] + gamma_value * max_val - q[other_state.rotation_270][action]);

        return b_action;
}

// Choose the next action to take using an epsilon-greedy policy
int choose_action_epsillon_greedy(int state, double epsilon){
        //Generate a random number between 0 and 1
        double random_number = (double)rand() / RAND_MAX;

        if (random_number > epsilon) {
                // Exploitation: Choose the action with the highest Q-value for the current state
                double unused;
                int b_action=best_action(state, &unused);
                return b_action;
        } else {
                // Exploration: Choose a random action
                return random_action();
        }
}

//Saving the q-values to q_values.txt
void extract_q_values(){
        FILE* fp;
        fp = fopen("../data/q_values_tictactoe.txt", "w");
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
        r_alloc();


        int state; 
        int new_state;
        int state_action;
        int new_action;

        double epsilon = 0.9;
        double epsilon_end=0.01;

        //Create an empty tic-tac-toe grid
        int *pgrille = creer_grille();
        
        for (int episode = 0 ; episode < nb_episodes ; ++episode){

        reset_grid(pgrille);
        state = get_state(pgrille);
        
        // Chosing action
        state_action = choose_action_epsillon_greedy(state, epsilon);
        placer(pgrille, state_action, 1);

        // Get reward & new state
        new_state = get_state(pgrille);    
        get_rewards(pgrille );

        new_action = q_update(state_action, state, new_state, pgrille);
       
        // Update state and action
        state = new_state ;
        state_action = new_action ;

        // Update the grid

        
        placer_alea(pgrille, 2);
        
        while(a_gagne(pgrille,1) == -1){
                state = get_state(pgrille);
        
                // Chosing action
                state_action = choose_action_epsillon_greedy(state, epsilon);
                placer(pgrille, state_action, 1);
                afficher(pgrille);
                printf(" \n");

                // Get reward & new state

                new_state = get_state(pgrille);
                get_rewards(pgrille);

                new_action = q_update(state_action, state, new_state, pgrille);
       
                // Update state and action
                state = new_state ;
                state_action = new_action ;

                // Update the grid

                placer_alea(pgrille, 2);
                afficher(pgrille);
                printf(" \n");

        }

        // reduce the exploration rate epsilon over time 
        epsilon=epsilon - exp(-8.9*epsilon);
        // ensure that the exploration rate does not go below the final rate
        epsilon=(epsilon<epsilon_end) ? epsilon_end : epsilon;

        
        }

        //Saving the q-values to q_values.txt
        extract_q_values();

        //Free the memory
        free_grille(pgrille); 
        r_destroy();
        //q_destroy();

        return 0 ;
}