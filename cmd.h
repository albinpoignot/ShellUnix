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
  int attendreRetour; // booleen indiquant sur il faut reprendre la main de suite
  
} Cmd;

void aff_args( Cmd* c ); // ToDo
void free_args( Cmd* c ); // ToDo
void parse_args( Cmd* c );
void parse_membres( char* chaine, Cmd* ma_cmd ); 
void aff_membres( Cmd* ma_cmd ); // ToDo
void free_membres( Cmd* ma_cmd ); // ToDo
int parse_redir( unsigned int i, Cmd* cmd ); 
void free_redir( Cmd* c );
void aff_redir( Cmd *c, unsigned int i ); // ToDo
