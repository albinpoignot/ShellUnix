#include <stdlib.h>
#include <stdio.h>

#include "cmd.h"

int main( int argc, const char* argv[] )
{
  int i;
  char tampon[250];                                         //Chaine de 250 caracteres servant a la concatenation
  
  cmd* cmd = malloc( 1 * sizeof( cmd ) );                   //Allocation de la structure CMD
  cmd->nb_membres = 1;
  
  cmd->membres_cmd = (char**)malloc( cmd->nb_membres * sizeof( char* ) );
  cmd->membres_cmd[0] = (char*) malloc( 250 * sizeof( char ) );
  cmd->nb_args_membres = (int*)malloc( cmd->nb_membres * sizeof( int ) );
  
  for( i = 1; i < argc; i++ )                               //On parcourt tout les elements passés en parametre au programme
  {
      strcat( tampon, argv[i] );                            //On les "append" au tampon
      strcat( tampon, " ");                        	    //On rajoute les espaces tronqués
  }
  
  cmd->initial_cmd = (char*)malloc( 1 * sizeof( tampon ) ); //Allocation de la chaine initial_cmd de la structure CMD
  strcpy( cmd->initial_cmd, tampon ) ;                      //Copie du tampon dans la chaine allouée
  strcpy( cmd->membres_cmd[0], cmd->initial_cmd );
  
  parse_args( cmd );                                        
}