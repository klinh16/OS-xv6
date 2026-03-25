#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAXARG 32

int main(int argc, char *argv[]) {
    char buf[512];
    char *base_argv[MAXARG];

    for (int i = 1; i < argc; i++) {
        base_argv[i - 1] = argv[i];
    }

    int base = argc - 1;
    int idx = 0;
    char c;

    while (read(0, &c, 1) > 0) {
        if (c == '\n') {
            buf[idx] = 0;

            char *args[MAXARG];

            for (int i = 0; i < base; i++) {
                args[i] = base_argv[i];
            }

            if (idx == 0) {
                args[base] = 0;
            } else {
                args[base] = buf;
                args[base + 1] = 0;
            }

            if (fork() == 0) {
                exec(args[0], args);
                exit(0);
            }
            wait(0);

            idx = 0;
        } else {
            buf[idx++] = c;
        }
    }

    if (idx > 0) {
        buf[idx] = 0;

        char *args[MAXARG];
        for (int i = 0; i < base; i++) {
            args[i] = base_argv[i];
        }

        args[base] = buf;
        args[base + 1] = 0;

        if (fork() == 0) {
            exec(args[0], args);
            exit(0);
        }
        wait(0);
    }

    exit(0);
}