#include "cmd.h"

void parse_args( cmd * c )
{
  char str[] ="ls -l";
  char * pch;

  pch = strtok (str," |");

  while (pch != NULL)
  {
    printf ("%s\n",pch);

    pch = strtok (NULL, " |");
  }

}

