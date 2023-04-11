#include "functions.h"

float alpha_value = 0.5 ; 
float gamma_value = 0.5 ; 


int** q;
int** r;
int** rewards;

void q_alloc(){
    q = malloc(rows * sizeof(int));
        int i;
        for (i = 0; i < rows; ++i){
                q[i] = malloc(cols * sizeof(int));
        }
}

void q_init(){
    q_alloc();
    int i,j;
    for (i = 0; i < rows; ++i) {
                for (j = 0; j < cols; ++j) {
                        q[i][j]= 0 ; 
                }
        }
}

void q_destroy(){
    int i;
    for (i = 0; i < rows; ++i){
                free(q[i]);
        }
    free(q);
}

void r_init(){
    r = malloc(rows * sizeof(int));
        int i;
        for (i = 0; i < rows; ++i){
                r[i] = malloc(cols * sizeof(int));
        }

        int j;
        for (i = 0; i < rows; ++i) {
                for (j = 0; j < cols; ++j) {
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
                }
        }
}

void r_destroy(){
    int i;
    for (i = 0; i < rows; ++i){
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

// Ajout de Q init, Q add, Q delete, free Q 
