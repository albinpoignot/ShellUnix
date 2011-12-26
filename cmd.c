#include "cmd.h"

/**
 * Affiche les arguments de chacun des membres
 */
void aff_args( cmd* c )
{
  
  int i, j;

  // Parcours des membres
  for( i=0; i < c->nb_membres; i++ )
  {
    // Parcours des args
    for( j=0; j < c->nb_args_membres[i]; j++ )
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
  for(i=0; i < c->nb_membres; i++ )
  {
    // Parcours des args
    for(j=0; j < c->nb_args_membres[i]; j++)
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
    
    char* copie = (char*)malloc( strlen( (c->membres_cmd[i] )+1) * sizeof( char ) );
    strcpy( copie, c->membres_cmd[i] );
    
    c->cmd_args[i] = (char**)malloc( 1 * sizeof( char* ) );
    pch = strtok ( copie," ");
    
    while (pch != NULL )
    {
      if( strcmp( pch, ">") != 0 && strcmp( pch, "<") != 0 && strcmp( pch, ">>") != 0)  // on analyse pas si redirection cela sera fait dans            parse redirection
      {
	c->cmd_args[i][j] = (char*)malloc( 250 * sizeof( char ) );
	strcpy( c->cmd_args[i][j], pch );
      
      //printf ("%s\n",pch);
      pch = strtok (NULL, " ");
      j++;

      
	if( pch != NULL )
	{
	  c->cmd_args[i] = (char**)realloc( c->cmd_args[i], j * sizeof( char* ) );
	}
      }
      else
      {
	pch = NULL;
      }
    }
    c->nb_args_membres[i] = j;

    free( copie );
  }

}

void parse_membres( char* chaine, cmd* cmd )  // Attention la fonction detruit l'argument chaine
{
    char* pch;
    unsigned int i = 0;
    
    cmd->initial_cmd = (char*)malloc( strlen(chaine) * sizeof( char ) ); //Allocation de la chaine initial_cmd de la structure CMD
    strcpy( cmd->initial_cmd, chaine ) ;                                 //Copie de la commande initial dans la structure
   
    pch = strtok ( chaine, "|" );
    
    while (pch != NULL)
    {
	i++;
	cmd->membres_cmd = realloc( cmd->membres_cmd, i * sizeof( char* ));
	cmd->membres_cmd[i-1] = (char*)malloc( strlen( pch ) * sizeof( char ));
	strcpy( cmd->membres_cmd[i-1], pch );
	
	pch = strtok ( NULL, "|" );
    }
    
    cmd->nb_membres = i;
    cmd->nb_args_membres = (int*)malloc( cmd->nb_membres * sizeof( int ) );  // initialisation du tableau d'entier nb_args_membres
    
    cmd->redir = (char***)malloc( cmd->nb_membres * sizeof( char** ) );
    cmd->type_redir = (int**)malloc( cmd->nb_membres * sizeof( int* ));
    
    for( i = 0; i < cmd->nb_membres; i++ )
    {
	cmd->redir[i] = (char**)malloc( 3 * sizeof( char* ) );
	
	cmd->redir[i][STDIN] = (char*)malloc( 250 * sizeof( char ) );
	cmd->redir[i][STDOUT] = (char*)malloc( 250 * sizeof( char ) );
	cmd->redir[i][STDERR] = (char*)malloc( 250 * sizeof( char ) );
	
	cmd->type_redir[i] = (int*)malloc( 3 * sizeof( int ));
	
	cmd->type_redir[i][STDIN] = -1;
	cmd->type_redir[i][STDOUT] = -1;
	cmd->type_redir[i][STDERR] = -1;
    }
}

int parse_redir( unsigned int i, cmd* cmd )
{
    char* pch = NULL; 
    int cas = 0;
  
    char* copie = (char*)malloc( strlen( (cmd->membres_cmd[i] )+1) * sizeof( char ) );
    strcpy( copie, cmd->membres_cmd[i] );
    
    pch = strtok( copie, " " );
    
    while( pch != NULL ) // au besin mettre un NULL ou valeur special dans les autres case de la redirection
    {
      if( cas == 1)
      {
	strcpy( cmd->redir[i][STDOUT], pch );
	printf( "Redirection sortie standard .%s.\n", cmd->redir[i][STDOUT] );
      }
      else if( cas == 2 )
      {
	strcpy( cmd->redir[i][STDIN], pch );
	printf( "Redirection entrée standard .%s.\n", cmd->redir[i][STDIN] );
      }
      else if( cas == 3 )
      {
	strcpy( cmd->redir[i][STDOUT], pch );
	cmd->type_redir[i][STDOUT] = RAPPEND;
	printf( "Redirection et append sortie standard .%s.\n", cmd->redir[i][STDOUT] );
	printf( "%d\n", cmd->type_redir[i][STDOUT] );
      }
      
      if( strcmp( pch, ">") == 0 )
      {
	cas = 1;
      }
      else if( strcmp( pch, "<") == 0 )
      {
	  cas = 2;
      }
      else if( strcmp( pch, ">>") == 0 )
      {
	 cas = 3;
      }
      
      pch = strtok( NULL, " " );
      
    }
    
    free( copie );
}








