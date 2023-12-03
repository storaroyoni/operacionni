#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command> [arguments]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *command = argv[1];
    char *args[argc];
    for (int i = 2; i < argc; i++)
    {
        args[i - 2] = argv[i];
    }
    args[argc - 2] = NULL; 

    int child_pid;
    while (1)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            fprintf(stderr, "fork: Cannot allocate memory\n");
            continue;
        }

        if (child_pid == 0)
        {
            execvp(args[0], args);
            perror("exec");
            exit(EXIT_FAILURE);
        }

        // parent process
        waitpid(child_pid, NULL, 0);

        sleep(2);
    }

    return EXIT_SUCCESS;
}
