#include "string.h"
#include <stdio.h>

typedef struct 
{
  char *initial_cmd;
  char **membres_cmd;
  unsigned int nb_membres;
  char ***cmd_args;
  unsigned int *nb_args_membres;
  char ***redir;
  int **type_redir;
} cmd;

void parse_args( cmd* c );