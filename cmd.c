#include "cmd.h"

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
    c->nb_args_membres[i] = j+1;
    
  }

}

