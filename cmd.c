#include "cmd.h"

/**
 * Affiche les arguments de chacun des membres
 */
void aff_args( cmd* c )
{
  
  int i, j;

  // Parcours des membres
  for(i=0; i <= c->nb_membres; i++ )
  {
    // Parcours des args
    for(j=0; j <= c->nb_args_membres[i]; j++)
    {
      printf("%s\n", c->cmd_args[i][j]);
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
  for(i=0; i <= c->nb_membres; i++ )
  {
    // Parcours des args
    for(j=0; j <= c->nb_args_membres[i]; j++)
    {
      free(c->cmd_args[i][j]);
    }
  }
  
}

void parse_args( cmd * c )
{
  char * pch;
  int i;
   
  c->cmd_args = (char***)malloc( c->nb_membres * sizeof( char** ) );
   
  for( i = 0; i < c->nb_membres; i++ )
  {
    int j = 0;
    
    c->cmd_args[i] = (char**)malloc( 1 * sizeof( char* ) );
    pch = strtok ( c->membres_cmd[i]," ");
    
    while (pch != NULL)
    {
      c->cmd_args[i][j] = (char*)malloc( 250 * sizeof( char ) );
      strcpy( c->cmd_args[i][j], pch );
      
      printf ("%s\n",pch);
      pch = strtok (NULL, " ");
      j++;
      
      if( pch != NULL )
      {
	c->cmd_args[i] = (char**)realloc( c->cmd_args[i], j * sizeof( char* ) );
      }
    }
    c->nb_args_membres[i] = j;
    
  }

}

