#include "mazeEnv.h"
#include "functions.h"
#include "qlearning.h"

char** mazeEnv;
//char** mazeEnvepisode;
int** visited;
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

//Allocation de la mémoire pour le labyrinthe implémenté sous la forme d'un tableau de caractères
void alloc_mazeEnv(){
     mazeEnv = malloc(rows * sizeof(char*));

     for(int i=0; i<rows; i++) {
         mazeEnv[i] = malloc(cols * sizeof(char*));
     }
}

//Extraction des données du .txt et construction du labyrinthe
void mazeEnv_make(char* file_name){
     char c;
     char rows_s[3] ={'\0'};
     char cols_s[3] ={'\0'};
     int rows_i = 0;
     int cols_i = 0;
     int swap = 0;

     FILE* file = fopen(file_name, "r");
     if (file == NULL){
        printf("Pointeur nul");
     }

     //Récupération du nombre de lignes et colonnes
     if (file) {
         /* lire la premiere ligne avant EOF */
         while( (c=getc(file)) != EOF) {
               if(c== '\n'){
                      break; // Pourquoi pas boucler sur la fin de la ligne ?
               } else if (c==',') {
                      swap = 1;
               } else if (!swap) {
                      rows_s[rows_i]=c;
                      rows_i++;
               } else { // swap = 1 
                      cols_s[cols_i]= c;
                      cols_i++;
               }
         }
     }

     if (c == EOF){
        printf("Error. data is not in the correct format \n");
        return;
     }

     //convertir le string en nombre
     rows = atoi(rows_s);
     cols = atoi(cols_s);

     alloc_mazeEnv();

     //Construction du labyrinthe
     for (int i=0; i<rows; i++){
         for (int j=0; j < cols; j++){
             c = getc(file);

             if (c=='\n'){ // saut de ligne
                c = getc(file); 
             } else if (c == 's'){
               start_row = i;
               start_col = j;
             } else if ( c == 'g'){
               goal_row = i;
               goal_col = j;
             }

             mazeEnv[i][j] = c;
         }
     }
     fclose(file);
}

//Affichage du labyrinthe
void mazeEnv_render(){
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf("%c ", mazeEnv[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}

//Affiche le labyrinthe avec la position actuelle de l'agent sans le modifier 
void mazeEnv_render_pos(){
    char c = mazeEnv[state_row][state_col];
    mazeEnv[state_row][state_col] = 'o'; 
    for (int i=0; i<rows; i++) {
        for (int j=0; j< cols; j++){
            printf("%c ", mazeEnv[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    mazeEnv[state_row][state_col] = c;
}

/*
//Copie de l'original mazeEnv dans une autre variable mazeEnvepisode sur laquelle on va travailler à chaque épisode
void alloc_mazeEnvepisode(){
        mazeEnvepisode = malloc(rows * sizeof(char*));

     for(int i=0; i<rows; i++) {
        mazeEnvepisode[i] = malloc(cols * sizeof(char*));
     }
}

void mazeEnvepisode_init(){
    alloc_mazeEnvepisode();
     for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < cols ; j++){
            mazeEnvepisode[i][j] = mazeEnv[i][j];
        }
     }
}

void mazeEnvepisode_render_pos(){
     mazeEnvepisode[state_row][state_col] = 'o'; 
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf("%c ", mazeEnvepisode[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}
*/

void mazeEnv_reset(){
    state_row = start_row;
    state_col = start_col;

    //Recreate original maze because crumbs can replace wall 
    //mazeEnvepisode_init();
}

/*Mise à jour du struct envOutput en fonction d'une action donnée*/
envOutput mazeEnv_step(action a){
    int reward = 0;
    int done = 0;
    envOutput stepOut;

    int temp_row; 
    int temp_col;

    // cette partie traite les cas de bords 
    if (a==up){
       temp_row = max(0,state_row -1);
       temp_col= state_col;
    }else if (a==down){
       temp_row = min(rows,state_row +1);
       temp_col= state_col;
    }else if (a==right){
       temp_col = min(cols,state_col +1);
       temp_row = state_row;
    }else if (a==left){
       temp_col = max(0,state_col -1);
       temp_row = state_row;
    }

    //SEULEMENT AVEC DFS
    /* 
    if((temp_row == goal_row) && (temp_col == goal_col)){
       reward = 10000;
       done   = 1;
    }
    */

    //AVEC Q-LEARNING
    //Si on atteint l'objectif
    if((temp_row == goal_row) && (temp_col == goal_col)){
       reward = r[goal_row][goal_col];
       done   = 1;
    }

    //Si on recontre un mur, l'agent ne bouge pas
    if (mazeEnv[temp_row][temp_col] == '+'){
        reward = r[temp_row][temp_col];
    } else { //Si on ne rencontre pas de mur
        state_col = temp_col ;
        state_row = temp_row ;
        reward = r[temp_row][temp_col];
    }
    
    stepOut.reward = reward;
    stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; 

   return stepOut;
}

//Choisi une action au hasard 
action env_action_sample(){
  return (enum action)(rand() % number_actions);
}

//Allocation de la mémoire pour un tableau des lieux visités
void alloc_visited(){
        visited = malloc(rows * sizeof(int*));

        for (int i = 0; i < rows; ++i){
                visited[i] = malloc(cols * sizeof(int*));
        }
}

void init_visited() {
    alloc_visited();

    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            if (mazeEnv[i][j] == '+') {
                    visited[i][j] = wall;
            } else if (mazeEnv[i][j] == 'g') {
                    visited[i][j] = goal;
            } else {
                    visited[i][j] = unknown;
            }
        }
    }
}

//A REVOIR
void update_visited(int col, int row){
    visited[col][row] = crumb ;
}

void add_crumbs(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] == crumb){
                  mazeEnv[i][j] ='.';
              }
          }
     }
     mazeEnv[start_row][start_col]= 's';
}


/*
//Enregistre le chemin choisi par l'agent dans mazeEnvepisode.
void add_crumbs(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  mazeEnvepisode[i][j] ='.';
              }
          }
     }
     mazeEnvepisode[start_row][start_col]= 's';
}
*/

/*
void mazeEnvepisode_destroy(){
    int i;
    for (i = 0; i < rows; ++i){
                free(mazeEnvepisode[i]);
        }
    free(mazeEnvepisode);
}
*/

void mazeEnv_destroy(){
    int i;
    for (i = 0; i < rows; ++i){
                free(mazeEnv[i]);
        }
    free(mazeEnv);
}

void visited_destroy(){
    int i ;
    for (i = 0; i < rows; ++i){
                free(visited[i]);
        }
    free(visited);
}