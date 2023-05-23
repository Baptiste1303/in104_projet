#include "tictactoe.h"

// Allocate memory and create a blank tic-tac-toe grid
int *creer_grille() {
  int *grille = malloc(sizeof(int) * 9);
  for (int i = 0; i < 9; ++i) {
    grille[i] = 0;
  }
  return grille;
};

void reset_grid(int *grille){
    for (int i = 0; i < 9; ++i) {
    grille[i] = 0;
  }
}

// Free the mémory
void free_grille(int* grille){
    free(grille);
}

// Display the current grid
void afficher(int*grille){
    for (int i=0;i<9;++i){
        if (i==3 || i==6){
            printf("\n");
        }
        if (grille[i]==0){
            printf(".");
        }
        else if (grille[i]==1){
            printf("x"); // Human
        }
        else {
            printf("o"); // Bot
        }
    }
    printf("\n");
}

// Place the player's number (1 for human, 2 for bot) on the grid
void placer(int *grille, int chiffre, int joueur){
    grille[chiffre]=joueur;
}

// Randomly place a player's number on the grid
void placer_alea(int* grille, int joueur){
    int chiffre = rand()%9 ;
    while (grille[chiffre] !=0){
        chiffre = rand()%9;
    }
    grille[chiffre] = joueur;
}

// Detect and return the winner of the game
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



void play() {
    int *pgrille = creer_grille();
    srand(time(0));
    // Number of the box (between 0 and 8) entered by the human
    int chiffre_entre = 0;

    while (a_gagne(pgrille,1) == -1){
        
        afficher(pgrille);
        // Retrieve the number of the box where the player wants to play
        printf("Donnez la case (chiffre): ");
        scanf("%d", &chiffre_entre);

        // If the number is not valid
        while (chiffre_entre < 0 || chiffre_entre > 8 || pgrille[chiffre_entre] != 0){
            printf("Donnez une case valide: ");
            scanf("%d", &chiffre_entre);
        }
        
        // Place the player's token
        placer(pgrille, chiffre_entre, 1);

        if(a_gagne(pgrille,1) != -1)
            break;
        
        //place the robot's token
        placer_alea(pgrille, 2);
    }

    afficher(pgrille);

    // Display the winner
    int resultat = a_gagne(pgrille,1);
    if (resultat== 1 ){
        printf("Le gagnant est le joueur humain \n");
    } else if (resultat == 2){
        printf("Le gagnant est le robot \n");
    } else {
        printf("Match nul\n");
}


// TEST min-max

/*  
int *pgrille2 = creer_grille();

pgrille2[0] = 2 ; 
pgrille2[1] = 2 ; 
pgrille2[2] = 2 ; 
pgrille2[3] = 1 ; 
pgrille2[4] = 1 ; 

int a = gridTotern(pgrille2);
int s = convertToDecimal(a);

printf("La base 10 est %9.d et le chiffre est %d", a,s);

*/

    free(pgrille);
}

