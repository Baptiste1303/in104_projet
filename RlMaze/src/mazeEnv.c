#include "mazeEnv.h"
#include "functions.h"
#include "qlearning.h"

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

//Remet l'agent au départ
void mazeEnv_reset(){
    state_row = start_row;
    state_col = start_col;
}

/*Mise à jour du struct envOutput en fonction d'une action donnée*/
envOutput mazeEnv_step(action a){
    int wall = 0;
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

    //Si on atteint l'objectif
    if((temp_row == goal_row) && (temp_col == goal_col)){
        done = 1 ;
    }

    // L'algorithme a été construit de manière a ce qu'on puisse compiler dfs et qlearning
    // Nous avons donc trouvé une solution alternative pour ne pas faire appel à la variable r qui empechait la compilation de dfs
    if (mazeEnv[temp_row][temp_col] != '+'){
        //Si on ne rencontre pas de mur
        state_col = temp_col ;
        state_row = temp_row ;
    } else {
        //Si on recontre un mur, l'agent ne bouge pas
        wall = 1;  
    }

    stepOut.wall = wall;
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

//Actuelise le tableau visited en laissant des "miettes"
void update_visited(){
    visited[state_row][state_col] = crumb ;
}

//Ajoute les "miettes" dans le labyrinthe
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

//Libérer la mémoire de mazeEnv
void mazeEnv_destroy(){
    int i;
    for (i = 0; i < rows; ++i){
                free(mazeEnv[i]);
        }
    free(mazeEnv);
}

//Libérer la mémoire de visited
void visited_destroy(){
    int i ;
    for (i = 0; i < rows; ++i){
                free(visited[i]);
        }
    free(visited);
}