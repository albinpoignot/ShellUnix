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
    cmd* cmd = malloc( 1 * sizeof( cmd ) );
    
    commande = readline( "Veuillez entrer votre commande\n" );

    parse_membres( commande, cmd );
    parse_args( cmd ); 
    
    for( i = 0; i < cmd->nb_membres; i++ )
    {
      parse_redir( i, cmd );
    }
    
    free( commande );
    //free cmd and co
    //flush le clavier
  //}                                      
}