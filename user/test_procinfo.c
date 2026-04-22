#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int pid1 = getpid();   // normal syscall
  int pid2 = ugetpid();  // fast version (no syscall)

  printf("getpid(): %d\n", pid1);
  printf("ugetpid(): %d\n", pid2);

  exit(0);
}