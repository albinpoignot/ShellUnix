#include "string.h"
#include <stdio.h>
#include <stdlib.h>

enum{ STDIN = 0, STDOUT = 1, STDERR = 2 };
enum{ RAPPEND = 3 };

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

void aff_args( cmd* c ); // ToDo
void free_args( cmd* c ); // ToDo
void parse_args( cmd* c );
void parse_membres( char* chaine, cmd* ma_cmd ); 
void aff_membres( cmd* ma_cmd ); // ToDo
void free_membres( cmd* ma_cmd ); // ToDo
int parse_redir( unsigned int i, cmd* cmd ); 
void free_redir( cmd* c );
void aff_redir( cmd c, int i ); // ToDo
