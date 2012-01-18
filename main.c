#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cmd.h"

#define ET 0
#define OU 1

void redirection( Cmd** tabCmd, int** tabEtOu, char* pointeurET, char** depart, int *j, int mode);

int main( int argc, const char* argv[] )
{
  //while(1)
  //{
    char* commande = NULL; 
	char* copieCommande = NULL;
    int i = 0, j = 0, exited = -1;;
    
    commande = readline( "Veuillez entrer votre commande\n" );
	
	if( commande != NULL )
	{
		add_history( commande );
	}
	
	copieCommande = (char*)malloc( (strlen( commande ) + 1) * sizeof( char ) );
	strcpy( copieCommande, commande );
		
	//analyser commande pour les && et || 
	if( (strstr( copieCommande, "&&") != NULL) || (strstr( copieCommande, "||") != NULL) )
	{
		int* tabEtOu = (int*)malloc( 1* sizeof( int ) );	
		char* depart = copieCommande;
		char* pointeurET =  strstr( copieCommande, "&&");
		char* pointeurOU =  strstr( copieCommande, "||");
		char* chaine = NULL;
		int etOuDone = 1;
		char* saveET = NULL;
		char* saveOU = NULL;
		
		Cmd** tabCmd = NULL;//(Cmd**)malloc( 1 * sizeof( Cmd* ) ); //sinon glibc pointer invalid au realloc
		
		while( pointeurET != NULL || pointeurOU != NULL )
		{
			etOuDone = 0;

			if( pointeurET != NULL && pointeurOU != NULL )
			{
				//printf("ET et OU present\n");
				if( pointeurET < pointeurOU )
				{
					redirection( tabCmd, &tabEtOu, pointeurET, &depart, &j, ET );
					redirection( tabCmd, &tabEtOu, pointeurOU, &depart, &j, OU );
				}
				else if( pointeurET > pointeurOU )
				{
					redirection( tabCmd, &tabEtOu, pointeurOU, &depart, &j, OU );
					redirection( tabCmd, &tabEtOu, pointeurET, &depart, &j, ET );
				} 
			}
			else if( pointeurET != NULL )
			{
				//printf("ET seul\n");
				redirection( tabCmd, &tabEtOu, pointeurET, &depart, &j, ET );
			}
			else if( pointeurOU != NULL )
			{
				//printf("OU seul\n");
				redirection( tabCmd, &tabEtOu, pointeurOU, &depart, &j, OU );
			}
			
			if( pointeurET != NULL )
			{
				saveET = pointeurET+3;
			}
			if( pointeurOU != NULL )
			{
				saveOU = pointeurOU+3;
				//printf(" depart :%s. - saveOU :%s\n", depart, saveOU );
			}
			
			pointeurET = strstr( depart, "&&");
			pointeurOU = strstr( depart, "||");
		}
		
		if( !etOuDone )
		{
			char* pointeurDernier = NULL;
			
			if( saveET != NULL )
			{
				//printf(" Et <- fait en dernier : %s\n", saveET );
				pointeurDernier = saveET;
			}
			else if( saveOU != NULL )
			{
				//printf(" Ou <- fait en dernier : %s\n", saveOU );
				pointeurDernier = saveOU;
			}
			
			int i = 0;
			tabCmd = (Cmd**)realloc( tabCmd, (j+1) * sizeof( Cmd* ) );
			tabCmd[j] = (Cmd*)malloc( 1 * sizeof( Cmd ) );
			
			char* chaine = (char*)malloc( (strlen(depart)+1) * sizeof( char ) );
			strcpy( chaine, depart );
			//printf("derniere commande = %s\n", chaine );
			parse_membres( chaine, tabCmd[j] );
			parse_args( tabCmd[j] ); 
			
			for( i = 0; i < tabCmd[j]->nb_membres; i++ )
			{
				parse_redir( i, tabCmd[j] );
			}
			
			j++;
			free( chaine );
		}

		i = 0;
		
		while( i < j )
		{
			printf(" %s\n", tabCmd[i]->initial_cmd );
			int correctementExe = exec_cmd( tabCmd[i] );
			printf( "retour : %d  special : %d\n", correctementExe, tabEtOu[i] );
			if( (correctementExe == 1 && tabEtOu[i] == ET) || ( correctementExe == -1 && tabEtOu[i] == OU) )
			{
				i++;   //On passe au suivant
			}
			else 
			{
				i = j;
			}
		}
		
		for( i = 0; i < j; i++ )
		{
			free_redir( tabCmd[i] );
			free_args( tabCmd[i] );
			free_membres( tabCmd[i] );
			free( tabCmd[i] );
		}
		
		free( tabCmd );
		free( tabEtOu );
	}
	else // Execution d'une commande sans && et || 
	{
		Cmd* cmd = (Cmd*)malloc( 1 * sizeof( Cmd ) );
		
		parse_membres( commande, cmd );
		parse_args( cmd ); 
		
		for( i = 0; i < cmd->nb_membres; i++ )
		{
			parse_redir( i, cmd );
		}
		
		exited = exec_cmd( cmd );
		
		free_redir( cmd );
		free_args( cmd );
		free_membres( cmd );

		free( cmd );
	}
	
	free( commande );
	free( copieCommande );
	
  //}                                      
}

void redirection( Cmd** tabCmd, int** tabEtOu, char* pointeurET, char** depart, int* j, int mode)
{
	int i = 0;
	char* chaine = NULL;

	tabCmd = (Cmd**)realloc( tabCmd, ((*j)+1) * sizeof( Cmd* ) );
	tabCmd[(*j)] = (Cmd*)malloc( 1 * sizeof( Cmd ) );
	
	*tabEtOu = (int*)realloc( *tabEtOu, ((*j)+1) * sizeof( int ) );
	*tabEtOu[(*j)] = mode;
	 
	chaine = (char*)malloc( (pointeurET - *depart + 1 ) * sizeof( char ) );
	strncpy( chaine, *depart, (pointeurET - *depart) );

	parse_membres( chaine, tabCmd[*j] );
	parse_args( tabCmd[*j] ); 
	
	for( i = 0; i < (tabCmd[*j])->nb_membres; i++ )
	{
		parse_redir( i, tabCmd[*j] );
	}
	
	(*j)++;
	pointeurET += 3;
	*depart = pointeurET;  
	free( chaine );
}
