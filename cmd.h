#include "string.h"
#include <stdio.h>

typedef struct 
{
  char *initial_cmd; // Chaine initiale tapee par l'utilisateur
  char **membres_cmd; // Chaine initiale decoupee en membres ([i] = membre i)
  unsigned int nb_membres; // Nombre de membres
  char ***cmd_args; // cmd_args[i][j] contient le jieme arguement du ieme membre
  unsigned int *nb_args_membres; // Nombre d'argements par membre
  char ***redir; // Stocke les chemins vers les fichiers de redirection
  int **type_redir; // Stocke le sens des redirections
} cmd;

void parse_args( cmd* c );