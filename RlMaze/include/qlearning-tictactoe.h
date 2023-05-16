#ifndef QLEARNING_TICTACTOE_H
#define QLEARNING_TICTACTOE_H

#include <math.h>
#include <time.h>
#include <mazeEnv.h>

extern float alpha_value; 
extern float gamma_value; 
extern int nb_episodes;

typedef struct similitudes {
    int mirroir ;
    int rotation_90 ; 
    int rotation_180 ;
    int rotation_270 ;
} similitudes ;

typedef struct actions_possible {
    int *list_actions;
    int number_actions;
} actions_possible;

extern double** q;

void q_alloc();

void q_init();

void q_destroy();

actions_possible recherche_actions_possible(int* grille);

void free_actions(int *actions);

int gridTotern(int *grid);

int convertToDecimal(int t);

int get_state(int *grille);

int inversionchiffre(int tern);

similitudes recherche_similitude(int tern);

int best_action(int state, double *max_val,actions_possible actions);

int q_update(int action, int state, int reward, int new_state, actions_possible actions);

int choose_action_epsillon_greedy(int state, double epsillon, actions_possible actions);

int get_reward(int *grid, actions_possible actions);

void extract_q_values();


#endif
