#ifndef QLEARNING_TICTACTOE_H
#define QLEARNING_TICTACTOE_H

#include <math.h>
#include <time.h>
#include <tictactoe.h>

extern float alpha_value; 
extern float gamma_value; 
extern int nb_episodes;

typedef struct similitudes {
    int mirroir ;
    int rotation_90 ; 
    int rotation_180 ;
    int rotation_270 ;
} similitudes ;

extern double** q;

void q_alloc();

void q_init();

void q_destroy();

void r_alloc();

void reset_reward();

int checkForWin(int* grid, int player, int move);

int couldHaveBlockedWin(int* grid, int player, int chosenMove);

void get_rewards(int *grid);

void r_destroy();

int gridTotern(int *grid);

int convertToDecimal(int t);

int get_state(int *grille);

int invert_digits(int ternary);

int invert_first_last(int ternary);

similitudes recherche_similitude(int* grid);

int best_action(int state, double *max_val);

int random_action();

int q_update(int action, int state, int new_state, int* grid);

int choose_action_epsillon_greedy(int state, double epsillon);

void extract_q_values();


#endif
