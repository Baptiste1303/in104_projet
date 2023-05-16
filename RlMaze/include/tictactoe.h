#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *creer_grille();

void afficher(int *grille);

void placer(int *grille, int chiffre, int joueur);

void placer_alea(int* grille, int joueur);

int a_gagne(int* grille, int joueur);

#endif