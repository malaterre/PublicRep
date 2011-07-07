#include "myfile.h"
#include <stdio.h>

bool myfile::open( const char *filename )
{
  FILE *f = fopen(filename, "r");
  if ( f == NULL )
    {
    fprintf( stderr, "could not open %s", filename );
    return false;
    }
  return true;
}
