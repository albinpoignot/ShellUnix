#include "cmd.h"

/**
 * Affiche les arguments de chacun des membres
 */
void aff_args( cmd* c )
{
  
  int i, j;

  // Parcours des membres
  for(i=0; i <= cmd->nb_membres; i++ )
  {
    // Parcours des args
    for(j=0; j <= cmd->nb_args_membres[i]; j++)
    {
      printf("%d\n", cmd->cmd_args[i][j]);
    }
  }
  
}


/**
 * Désalloue l'espace allouée pour les arguments
 */
void free_args( cmd* c )
{
  
  int i, j;

  // Parcours des membres
  for(i=0; i <= cmd->nb_membres; i++ )
  {
    // Parcours des args
    for(j=0; j <= cmd->nb_args_membres[i]; j++)
    {
      free(cmd->cmd_args[i][j]);
    }
  }
  
}

void parse_args( cmd * c )
{
  char str[] ="ls -l";
  char * pch;

  pch = strtok (str," |");

  while (pch != NULL)
  {
    printf ("%s\n",pch);

    pch = strtok (NULL, " |");
  }

}

