#include "cmd.h"

/**
 * Affiche les membres 
 */
void aff_membres( Cmd* c )
{
  int i;

  // Parcours des membres
  for( i=0; i < c->nb_membres; i++ )
  {
    printf("membres_cmd[%d] = %s\n", i, c->membres_cmd[i]);
  }
}


/**
 * Affiche les redirections
 */
void aff_redir( Cmd* c, unsigned int i )
{
     printf( "redir[%d][STDIN] = %s\n", i, c->redir[i][0] );
     printf( "redir[%d][STDOUT] = %s\n", i, c->redir[i][1] );
     printf( "redir[%d][STDERR] = %s\n", i, c->redir[i][2] );
     
     printf( "type_redir[%d][STDIN] = %d\n", i, c->type_redir[i][0] );
     printf( "type_redir[%d][STDOUT] = %d\n", i, c->type_redir[i][1] );
     printf( "type_redir[%d][STDERR] = %d\n", i, c->type_redir[i][2] );
}

/**
 * Affiche les arguments de chacun des membres
 */
void aff_args( Cmd* c )
{
  
  int i, j;

  // Parcours des membres
  for( i=0; i < c->nb_membres; i++ )
  {
    // Parcours des args
    for( j=0; j < c->nb_args_membres[i]; j++ )
    {
      printf("cmd_args[%d][%d]= %s\n", i, j, c->cmd_args[i][j]);
    }
  }
  
  for( i=0; i < c->nb_membres; i++ )
  {
    printf("nb_args_membres[%d] = %d\n", i, c->nb_args_membres[i] );
  }
  
}


/**
 * Désalloue l'espace allouée pour les arguments
 */
void free_args( Cmd* c )
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

void parse_args( Cmd * c )
{
  char * pch;
  int i;
   
  c->cmd_args = (char***)malloc( c->nb_membres * sizeof( char** ) );
   
  for( i = 0; i < c->nb_membres; i++ )
  {
    int j = 0;

    char* copie = (char*)malloc( (strlen(c->membres_cmd[i])+1) * sizeof( char ) );
    strcpy( copie, c->membres_cmd[i] );
  
    c->cmd_args[i] = (char**)malloc( 1 * sizeof( char* ) );
    pch = strtok ( copie," ");
  
    while (pch != NULL )
    {
      if( strcmp( pch, ">") != 0 && strcmp( pch, "<") != 0 && strcmp( pch, ">>") != 0 && strcmp( pch, "2>>") != 0 && strcmp( pch, "2>") != 0 )  // on analyse pas si redirection cela sera fait dans            parse redirection
      {
	c->cmd_args[i][j] = (char*)malloc( (strlen( pch) + 1 ) * sizeof( char ) );
	strcpy( c->cmd_args[i][j], pch );
     
	pch = strtok (NULL, " ");
	j++;
  
	if( pch != NULL )
	{
	  c->cmd_args[i] = (char**)realloc( c->cmd_args[i], (j+1) * sizeof( char* ) );
	}
      }
      else
      {
	pch = strtok (NULL, " ");
	pch = strtok (NULL, " ");
      }
    }
    c->nb_args_membres[i] = j;
    free( copie );
  }

}

void parse_membres( char* chaine, Cmd* cmd )  // Attention la fonction detruit l'argument chaine
{
    char* pch;
    int i = 0;
    
    cmd->initial_cmd = (char*)malloc( (strlen(chaine)+1) * sizeof( char ) ); //Allocation de la chaine initial_cmd de la structure CMD    
    strcpy( cmd->initial_cmd, chaine ) ;                                 //Copie de la commande initial dans la structure
   
    pch = strtok ( chaine, "|" );

    cmd->membres_cmd = (char**)malloc( sizeof( char* )) ;
    
    while (pch != NULL)
    {
	i++;

	cmd->membres_cmd = (char**)realloc( cmd->membres_cmd, i * sizeof( char* ));
	cmd->membres_cmd[i-1] = (char*)malloc( (strlen( pch )+1) * sizeof( char ));
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
	
	cmd->redir[i][STDIN] = (char*)malloc( 5 * sizeof( char ) );
	cmd->redir[i][STDOUT] = (char*)malloc( 5 * sizeof( char ) );
	cmd->redir[i][STDERR] = (char*)malloc( 5 * sizeof( char ) );
	
	cmd->redir[i][STDIN] = "NULL";
	cmd->redir[i][STDOUT] = "NULL";
	cmd->redir[i][STDERR] = "NULL";
	
	cmd->type_redir[i] = (int*)malloc( 3 * sizeof( int ));
	
	cmd->type_redir[i][STDIN] = -1;
	cmd->type_redir[i][STDOUT] = -1;
	cmd->type_redir[i][STDERR] = -1;
    }
}

int parse_redir( unsigned int i, Cmd* cmd )
{
    char* pch = NULL; 
    int cas = 0;
  
    char* copie = (char*)malloc( (strlen(cmd->membres_cmd[i])+1) * sizeof( char ) );
    strcpy( copie, cmd->membres_cmd[i] );
    
    pch = strtok( copie, " " );
    
    while( pch != NULL ) // au besoin mettre une valeur special dans les autres case de la redirection
    {
      if( cas == 1)
      {
	cmd->redir[i][STDOUT] = (char*)malloc( (strlen( pch )+1) * sizeof( char ) );
	strcpy( cmd->redir[i][STDOUT], pch );
	//printf( "Redirection sortie standard .%s.\n", cmd->redir[i][STDOUT] );
      }
      else if( cas == 2 )
      {
	cmd->redir[i][STDIN] = (char*)malloc( (strlen(pch)+1) * sizeof( char ) );
	strcpy( cmd->redir[i][STDIN], pch );
	//printf( "Redirection entrée standard .%s.\n", cmd->redir[i][STDIN] );
      }
      else if( cas == 3 )
      {
	cmd->redir[i][STDOUT] = (char*)malloc( (strlen( pch )+1) * sizeof( char ) );
	strcpy( cmd->redir[i][STDOUT], pch );
	cmd->type_redir[i][STDOUT] = RAPPEND;
	//printf( "Redirection et append sortie standard .%s.\n", cmd->redir[i][STDOUT] );
	//printf( "%d\n", cmd->type_redir[i][STDOUT] );
      }
      else if( cas == 4 )
      {
	cmd->redir[i][STDERR] = (char*)malloc( (strlen( pch )+1) * sizeof( char ) );
	strcpy( cmd->redir[i][STDERR], pch );
	//printf( "Redirection erreur standard .%s.\n", cmd->redir[i][STDERR] );
      }
      else if( cas == 5 )
      {
	cmd->redir[i][STDERR] = (char*)malloc( (strlen( pch )+1) * sizeof( char ) );
	strcpy( cmd->redir[i][STDERR], pch );
	cmd->type_redir[i][STDERR] = RAPPEND;
	//printf( "Redirection et append erreur standard .%s.\n", cmd->redir[i][STDERR] );
	//printf( "%d\n", cmd->type_redir[i][STDERR] );
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
      else if( strcmp( pch, "2>") == 0 )
      {
	 cas = 4;
      }
      else if( strcmp( pch, "2>>") == 0 )
      {
	  cas = 5;
      }
      
      pch = strtok( NULL, " " );
      
    }
    
}








