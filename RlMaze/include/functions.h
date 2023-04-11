#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include <mazeEnv.h>

extern float alpha_value;
extern float gamma_value;

void q_alloc();

void q_init();

void q_destroy();

void r_init();

void r_destroy();

extern int min(int a, int b);

extern int max(int a, int b);

#endif
