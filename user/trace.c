#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;
  char *nargv[32];

  if(argc < 3){
    fprintf(2, "usage: trace mask command\n");
    exit(1);
  }

  int mask = atoi(argv[1]);
  trace(mask);

  for(i = 2; i < argc && i < 32; i++){
    nargv[i-2] = argv[i];
  }
  nargv[i-2] = 0;

  exec(nargv[0], nargv);

  fprintf(2, "exec failed\n");
  exit(1);
}
