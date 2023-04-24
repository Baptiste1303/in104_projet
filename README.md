# IN104_Projet - Apprentissage par renforcement en C

## README

Ce projet a été réalisé par :
* MARTEL Baptiste [@Baptiste_1303](https://github.com/Baptiste1303)
* CHEN Marc [@Kemar8](https://github.com/Kemar8)

### Présentation du projet

Ce projet a pour objectif principal d'implémenter plusieurs algorithmes d'apprentissage par renforcement. 
Ces algorithmes sont :
* Q-Learning, code disponible dans qlearning.c
* SARSA, code disponible prochainement.

Dans un premier temps l'objectif est de résoudre le déplacement dans un labyrinthe. Ce dernier est donné dans le fichier [maze.txt](https://github.com/Baptiste1303/in104_projet/blob/main/RlMaze/data/maze.txt) comportant un départ, un objectif, des cases murs et des cases vides sur lesquelles l'agent peut se déplacer.

Dans un second temps, l'objectif est d'étendre ces algorithmes à d'autres types d'environnements.

Nous avons travaillé à partir d'une base fournie par [@nguyensaomai](https://github.com/nguyensaomai) comportant l'aquisition du labyrinthe ainsi qu'une fonction [dfs.c](https://github.com/Baptiste1303/in104_projet/blob/main/RlMaze/src/dfs.c) de recherche en profondeur.

### Comment exécuter le projet ?

Le projet comporte deux Makefile permettant à l'agent de 

### Difficultés rencontrées et état d'avancement

