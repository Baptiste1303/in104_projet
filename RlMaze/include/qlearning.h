#ifndef QLEARNING_H
#define QLEARNING_H

#include <math.h>
#include <time.h>
#include <mazeEnv.h>

extern float alpha_value; // learning rate 
extern float gamma_value; // discount factor (importance given to future rewards compared to immediate rewards)

extern int** q;
extern int** r;

void q_alloc();

void q_init();

void q_destroy();

int get_state();

action q_update(action a, int state, int reward, int new_state);

action choose_action_epsillon_greedy(int state, double epsillon);

void r_init();

void r_destroy();


#endif
