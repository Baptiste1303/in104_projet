#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include <time.h>
#include <mazeEnv.h>

extern float alpha_value; // learning rate 
extern float gamma_value; // discount factor (importance given to future rewards compared to immediate rewards)

extern int** q;
extern int** r;

void q_alloc();

void q_init();

int get_state(int col, int row);

action q_update(action a, int state, int reward, int new_state);

action choose_action_epsillon_greedy(int state, double epsillon);

void q_destroy();

void r_init();

void r_destroy();

extern int min(int a, int b);

extern int max(int a, int b);

#endif
