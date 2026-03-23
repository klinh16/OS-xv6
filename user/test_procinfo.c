#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    struct procinfo info;

    if(procinfo(getpid(), &info) == 0){
        printf("Process: %s\n", info.name);
        printf("PID: %d, PPID: %d\n", info.pid, info.ppid);
        printf("State: %d\n", info.state);
        printf("Memory: %ld bytes\n", info.sz);
    } else {
        printf("Error\n");
    }

    exit(0);
}
