#ifndef MAZEENV_H
#define MAZEENV_H

#include <stdio.h>
#include <stdlib.h>

char** mazeEnv;
int** visited;
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

enum terrain{
    unknown,
    wall,
    known,
    goal,
    crumb
};

enum action{
     up,
     down,
     left,
     right,
     number_actions 
};
 
typedef enum action action ;

struct envOutput{
  int new_col;
  int new_row;
  int reward;
  int done;

};

typedef struct envOutput envOutput;

void alloc_mazeEnv();

void mazeEnv_make(char* );

void mazeEnv_render();

void mazeEnv_render_pos();

void mazeEnv_reset();

envOutput mazeEnv_step(action a); 

action env_action_sample();

void alloc_visited();

void init_visited();

void add_crumbs();

#endif /* MAZEENV_H */
