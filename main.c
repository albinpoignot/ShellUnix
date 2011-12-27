#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cmd.h"

int main( int argc, const char* argv[] )
{
  /*while(1)
  {*/
    char* commande; 
    int i = 0;
    Cmd* cmd = (Cmd*)malloc( 1 * sizeof( Cmd ) );
    
    commande = readline( "Veuillez entrer votre commande\n" );

    parse_membres( commande, cmd );
    parse_args( cmd ); 
    
    for( i = 0; i < cmd->nb_membres; i++ )
    {
      parse_redir( i, cmd );
    }
    
    exec_cmd( cmd );
    
    /*aff_membres( cmd );
    aff_args( cmd );
    
    for( i = 0; i < cmd->nb_membres; i++ )
    {
      aff_redir( cmd, i );
    }*/
    
    free_redir( cmd );
    free_args( cmd );
    free_membres( cmd );
    
    free( commande );
    free( cmd );
    
  //}                                      
}