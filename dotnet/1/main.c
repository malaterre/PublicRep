#include <stdio.h>

typedef struct c c;

c* ns_create(void);
const char *ns_get(c*);
void ns_delete(c*);

int main()
{
  c* c = ns_create();
  for( int i = 0; i < 10; ++i) {
    puts( ns_get(c) );
  }
  ns_delete(c);
}
