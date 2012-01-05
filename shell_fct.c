#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "cmd.h"

void process_membres( Cmd* cmd, int i );

void exec_cmd( Cmd* cmd )
{
  process_membres( cmd, 0 ); 
}

int Pipe[2]; 

void process_membres( Cmd* cmd, int i )
{
  pid_t fils;
  
  if( ( fils = fork() ) == 0 )  //fils
  {   
    //printf("Je suis %s\n", cmd->cmd_args[i][0] );
    
    //*************************** Mise en place des Pipes et Appel recursif *************************************************
    if( i != 0  ) // Ils redirigent tous leur entrée standard sauf le 1er
    {
      //printf("Je suis %s je redirige mon entrée standard\n", cmd->cmd_args[i][0] );
      close( 0 ); dup( Pipe[0] ); close( Pipe[0] ); close( Pipe[1] );
    }
    
    if( i != (cmd->nb_membres - 1) ) // Ils ont tous besoin d'un pipe sauf le dernier
    {
      //printf("Je suis %s je crée un pipe \n", cmd->cmd_args[i][0] );
      pipe( Pipe );
    }
    
    if( i < (cmd->nb_membres - 1) ) // appel recursif !!!!! Equivaut a un Fork attention au contexte !!!!!!
     {
       //printf("Je vais faire un appel recursif je suis %s\n", cmd->cmd_args[i][0]);
       int j = i + 1;
       process_membres( cmd, j );
     }
    
     if(  i != (cmd->nb_membres - 1) ) // Ils redirigent tous leur sorties sauf le dernier
     {
	//printf("Je suis %s je redirige ma sortie standard\n", cmd->cmd_args[i][0] );
	close( 1 ); dup( Pipe[1] ); close( Pipe[0] ); close( Pipe[1] );
      }
    //*************************************************************************************************************************
    //******************** Redirection standard ****************************
     if( strcmp( cmd->redir[i][STDIN], "NULL" ) != 0 )   // redirection entrée standard
     {
       int fichier = open( cmd->redir[i][STDIN], O_RDONLY  );
       close( 0 );
       dup( fichier );
       close( fichier );
     }
     
     if( strcmp( cmd->redir[i][STDOUT], "NULL" ) != 0 ) // redirection sortie standard
     {
       int fichier;
       if( cmd->type_redir[i][STDOUT] == RAPPEND )          //en mode ajout
       {
	 fichier = open( cmd->redir[i][STDOUT], O_RDWR | O_APPEND );
       }
       else                                                 //en mode normal
       {
	 fichier = open( cmd->redir[i][STDOUT], O_WRONLY | O_CREAT, 0777 );
       }
       
       close( 1 );
       dup( fichier );
       close( fichier );
     }
     
     if( strcmp( cmd->redir[i][STDERR], "NULL" ) != 0 )  // redirection sortie d'erreur standard
     {
       int fichier;
       if( cmd->type_redir[i][STDERR] == RAPPEND )            // en mode ajout
       {
	 fichier = open( cmd->redir[i][STDERR],  O_RDWR | O_APPEND );
       }
       else                                                   // en mode normal
       {
	 fichier = open( cmd->redir[i][STDERR], O_WRONLY | O_CREAT, 0777 );
       }
       
       close( 2 );
       dup( fichier );
       close( fichier );
     }
     //**********************************************************************
     //************* Execution **********************************************
     
     cmd->cmd_args[i] = (char**)realloc( cmd->cmd_args[i], (cmd->nb_args_membres[i] + 1) * sizeof( char*) );
     cmd->cmd_args[i][ cmd->nb_args_membres[i] ] = NULL; //rajout d'un pointeur NULL dans la liste d'arguements pour execvp
     
     execvp( cmd->cmd_args[i][0], cmd->cmd_args[i] );
  }
  else
  {	
    if( i == 0 && cmd->attendreRetour == 1) // On attache que le 1er au shell les autres s'attendent via les pipes
    {
      waitpid( fils, NULL, 0 );
    }
  }
}