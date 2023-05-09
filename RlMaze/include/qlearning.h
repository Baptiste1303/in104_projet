#ifndef QLEARNING_H
#define QLEARNING_H

#include <math.h>
#include <time.h>
#include <mazeEnv.h>

extern float alpha_value; 
extern float gamma_value; 
extern int nb_episodes;


extern double** q;
extern double** r;

void q_alloc();

void q_init();

void q_destroy();

int get_state();

action best_action(int state, double *max_val);

void q_update(action a, int state, int reward, int new_state);

action choose_action_epsillon_greedy(int state, double epsillon);

void r_init();

int get_reward(int wall);

void r_destroy();

void mazeEnv_render_preferential_action();

void extract_q_values();


#endif
