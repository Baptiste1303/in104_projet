# IN104_Projet - Apprentissage par renforcement en C

## README

Ce projet a été réalisé par :
* MARTEL Baptiste _alias_ [@Baptiste_1303](https://github.com/Baptiste1303)
* CHEN Marc _alias_ [@Kemar8](https://github.com/Kemar8)

### Présentation du projet

Ce projet a pour objectif principal d'implémenter plusieurs algorithmes d'apprentissage par renforcement. 
Ces algorithmes sont :
* Q-Learning, code disponible dans [qlearning.c](https://github.com/Baptiste1303/in104_projet/blob/main/RlMaze/src/qlearning.c)
* SARSA, code disponible prochainement.

Dans un premier temps l'objectif est de résoudre le déplacement d'un agent dans un labyrinthe.

Dans un second temps, l'objectif est d'étendre ces algorithmes à d'autres types d'environnements.

Nous avons travaillé à partir d'une base [RlMaze](https://github.com/nguyensaomai/RlMaze) fournie par [@nguyensaomai](https://github.com/nguyensaomai) comportant l'aquisition du labyrinthe ainsi qu'une fonction [dfs.c](https://github.com/Baptiste1303/in104_projet/blob/main/RlMaze/src/dfs.c) de recherche en profondeur dans le but de résoudre le labyrinthe.

### Comment exécuter le projet ?

Le projet comporte un [Makefile](https://github.com/Baptiste1303/in104_projet/blob/main/RlMaze/src/Makefile) permettant d'éxécuter le mode d'exploration souhaité pour le labyrinthe.

Pour résoudre le labyrinthe grâce à la recherche en profonceur :
Rentrer la commande ``make dfs.x`` pour générer un exécutable.
En l'excutant grâce à ``./dfs.x`` cela :
- affiche le labyrinthe
- effectue le parcours en profondeur
- affiche le labyrinthe avec les cases par lesquelles est passé l'agent

Pour résoudre le labyrinthe grâce a l'algorithme Q-Learning :
Rentrer la commande ``make`` pour générer un exécutable
En l'excutant grâce à ``./qlearning.x`` cela :
- affiche le labyrinthe
- effectue l'algorithme Q-Learning avec la règle epsilon-greedy 
- affiche l'action avec la récompense maximale pour chaque case
- enregistre dans un fichier Q_valeurs.txt les valeurs finales de Q
- affiche le dernier chemin emprunté par l'agent

La commande ``make realclean`` permet de supprimer tous les .o et .x.

### Difficultés rencontrées et état d'avancement

Les principales difficultés rencontrées sont :

* Difficultés sur l'actualisation de la position dans *mazeEnv_step*. Après une action, la nouvelle position renvoyée était incorrecte. L'erreur a été repérée et corrigée, elle était liée au fait que certaines varibles étaient déclarées et utilisées dans leur avoir assigné de valeurs. [réglé]
* Problèmes liés aux choix des coefficients de recompenses qui induisent dans certains cas des problèmes de convergence. En effet, leurs choix est compliqués car ils sont en partie aléatoires. [réglé]
* Difficultés pour faire en sorte que les algorithmes qlearning.c et dfs.c puissent compiler en même temps. En effet, la variable r (tableau regroupant les récompenses) était utiliséé dans MazeEnv.c, mais non utilisée pour dfs.c et indisensable dans qlearning.c [réglé]
* L'utilisation de la fonction *update_visited(state_col,state_row)* induit un segmentation fault. L'erreur eétait due à l'inversion des arguments entre lignes et colonnes. [réglé]

L'algorithme [qlearning.c](https://github.com/Baptiste1303/in104_projet/blob/main/RlMaze/src/qlearning.c) ainsi que le [Makefile](https://github.com/Baptiste1303/in104_projet/blob/main/RlMaze/src/Makefile) sont fonctionnels.

Les autres algorithmes d'apprentissage par renforcement n'ont pas encore été implémentés.
Nous avons pour objectif par la suite d'implémenter ces algorithmes dans d'autres environnements.