#include <stdlib.h>
#include <stdio.h>

#include "cmd.h"

int main( int argc, const char* argv[] )
{
  while(1)
  {
    char commande[500];
    
    cmd* cmd = malloc( 1 * sizeof( cmd ) );
    cmd->nb_membres = 1;
    cmd->membres_cmd = (char**)malloc( cmd->nb_membres * sizeof( char* ) );
    cmd->membres_cmd[0] = (char*) malloc( 250 * sizeof( char ) );
    cmd->nb_args_membres = (int*)malloc( cmd->nb_membres * sizeof( int ) );
    
    printf("Veuillez entrer votre commande\n");
    scanf( "%s", commande );
    
    cmd->initial_cmd = (char*)malloc( 1 * sizeof( commande ) ); //Allocation de la chaine initial_cmd de la structure CMD
    strcpy( cmd->initial_cmd, commande ) ;                      //Copie du tampon dans la chaine allouée
    strcpy( cmd->membres_cmd[0], cmd->initial_cmd );
  
    parse_args( cmd ); 
    
    //free cmd and co
  }                                      
}