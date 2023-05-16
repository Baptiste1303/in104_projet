#include "tictactoe.h"

int *creer_grille() {
  int *grille = malloc(sizeof(int) * 9);
  for (int i = 0; i < 9; ++i) {
    grille[i] = 0;
  }
  return grille;
};

// Action vide = -1 
int* creer_actions(){
    int* actions = malloc(sizeof(int) * 9);
    for(int i = 0 ; i < 9 ; ++i){
        actions[i] = -1 ;
    }
    return actions;
}

int* actions_possible(int *actions){
    
}

void afficher(int *grille) {
  int j = 0;
  for (int i = 1; i < 4; ++i) {
    for (int k = 0; k < 3; ++k) {
      if (grille[j+k] == 0){
          printf(".");
      }
      else if(grille[j+k] == 1){
          printf("x");
      }
      else if(grille[j+k] == 2){
          printf("o");
      }
    }
    printf("\n");
    j = j + 3;
  }
  printf("\n");
};

void placer(int *grille, int chiffre, int joueur){
    grille[chiffre]=joueur;
}

void placer_alea(int* grille, int joueur){
    int chiffre = rand()%9 ;
    while (grille[chiffre] !=0){
        chiffre = rand()%9;
    }
    grille[chiffre] = joueur;
}

int a_gagne(int* grille, int joueur){
    
    int winning_combinations[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, 
        {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}
    };

    for(int i=0; i<8; i++) {
        if(grille[winning_combinations[i][0]] != 0 && 
           grille[winning_combinations[i][0]] == grille[winning_combinations[i][1]] && 
           grille[winning_combinations[i][1]] == grille[winning_combinations[i][2]]) {
            return grille[winning_combinations[i][0]];
        }
    }
    
    for(int i=0; i<9; i++) {
        if(grille[i] == 0)
            return -1;
    }
    
    return 0;
}

int main() {
    int *pgrille = creer_grille();
    srand(time(0));
    int chiffre_entre = 0;

    while (a_gagne(pgrille,1) == -1){
        
        afficher(pgrille);
        printf("Donnez la case (chiffre): ");
        scanf("%d", &chiffre_entre);

        while (chiffre_entre < 0 || chiffre_entre > 8 || pgrille[chiffre_entre] != 0){
            printf("Donnez une case valide: ");
            scanf("%d", &chiffre_entre);
        }
        
        placer(pgrille, chiffre_entre, 1);

        if(a_gagne(pgrille,1) != -1)
            break;
        
        placer_alea(pgrille, 2);
    }

    afficher(pgrille);

    int resultat = a_gagne(pgrille,1);
    if (resultat== 1 ){
printf("le gagnant est le joueur humain \n");
}
else if (resultat == 2){
printf("le gagnant est le robot \n");
}
else {
printf("Match nul\n");
}

free(pgrille);
return 0; }