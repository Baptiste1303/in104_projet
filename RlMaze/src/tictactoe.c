/* CHEN Marc */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*

Probleme gagant machine/humain -> test
+ finir match nul 
bouffeur de carte grapohique va 


*/

int *creer_grille() {
  int *grille = malloc(sizeof(int) * 9);
  for (int i = 0; i < 10; ++i) {
    grille[i] = 0;
  }
  /*
  grille[2] =2;
  grille[1] = 1; */
  return grille;
};

void afficher(int *grille) {
  int j = 0;
  for (int i = 1; i < 4; ++i) {
    if (grille[j] == 0){
        printf(".");
    }
    else if(grille[j] == 1){
        printf("x");
    }
    else if(grille[j] == 2){
        printf("o");
    }

    if (grille[j+1] == 0){
        printf(".");
    }
    else if(grille[j+1] == 1){
        printf("x");
    }
    else if(grille[j+1] == 2){
        printf("o");
    }

    if (grille[j+2] == 0){
        printf(".");
    }
    else if(grille[j+2] == 1){
        printf("x");
    }
    else if(grille[j+2] == 2){
        printf("o");
    }

    printf("\n");

    j = j + 3;
  }
  printf("\n");
};

void test_affichage(){
    int *pgrille_test = creer_grille();
    afficher(pgrille_test);
    pgrille_test[4] = 1 ;
    pgrille_test[8] = 2 ;
    afficher(pgrille_test);
}

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
// !!!!! Probleme quand ca tombe sur la case d'un joueur ca joue pas !!!!! 

// Les differents cas : -1 -> jeu non fini | 1/2 -> gagnant | 3 -> match nul (terrain plein)
int a_gagne(int* grille, int joueur){
    
    if (grille[0] !=0 && grille[1] !=0 && grille[2] !=0 && grille[3] !=0 && grille[4] !=0 && grille[5] !=0 && 
    grille[6] !=0 && grille[7] !=0 && grille[8] !=0 )
    {
        return 3;
    } 

    if (grille[0] !=0 && grille[0]==grille[3] && grille[3]==grille[6]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[1] !=0 && grille[1]==grille[4] && grille[4]==grille[7]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[2] !=0 && grille[2]==grille[5] && grille[5]==grille[8]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[0] !=0 && grille[0]==grille[1] && grille[1]==grille[2]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[3] !=0 && grille[4]==grille[5] && grille[5]==grille[3]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[7] !=0 && grille[7]==grille[8] && grille[8]==grille[6]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[0] !=0 && grille[0]==grille[4] && grille[4]==grille[8]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[2] !=0 && grille[2]==grille[4] && grille[4]==grille[6]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    if (grille[0] !=0 && grille[0]==grille[3] && grille[3]==grille[6]){
        if (grille[0] == 1 && joueur == 1){
            return 1;
        }
        else if (grille[0] == 1 && joueur ==2){
            return 0;
        }
        else if (grille[0] == 2 && joueur == 1){
            return 0;

        }
        else{ // Cas ou le joueur est 2 et le gagnant est 2 
            return 1;
        }
    }

    return -1 ;
}

int case_restante(int *pgrille){
    int compteur = 0 ; 
    for (int i = 0; i < 9 ; ++i){
        if (pgrille[i] != 0 ){
            ++compteur;
        }
    }
    return 9 - compteur ;
}

int main() {
    int *pgrille = creer_grille();
    srand(time(0));
    int chiffre_entre = 0;
    int tours = 0 ;

    //afficher(pgrille);

    //test_affichage();

    /*
    placer(pgrille, 2, 2);
    placer(pgrille, 3, 2);
    placer(pgrille, 4, 2);
    afficher(pgrille);
    placer_alea(pgrille,1);
    placer_alea(pgrille,1);

    afficher(pgrille); */

    //int test;
    while (a_gagne(pgrille,1) == -1 && case_restante(pgrille) != 1){
        
        afficher(pgrille);
        printf("Donnez la case (chiffre): ");
        scanf("%d", &chiffre_entre);

        
        while (pgrille[chiffre_entre] != 0){
            printf("Donnez une case valide: ");
            scanf("%d", &chiffre_entre);

        }
        
        placer(pgrille, chiffre_entre, 1);

        placer_alea(pgrille, 2);
        /*test = case_restante(pgrille);
        printf("case resultat %d \n", test);*/
        ++tours;
    }

    ++tours;
    afficher(pgrille);

    // Détermination du gagnant 
    if (a_gagne(pgrille,1) == 1 ){
        printf("le gagnant est le joueur humain \n");
    }
    else if (a_gagne(pgrille,1) == 0){
        printf("le gagnant est le robot \n");
    }
    else {
        printf("Match nul en %d tours\n", tours);
    }


    free(pgrille);
    return 0;
}