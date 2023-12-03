#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char line[1024];
    while (1)
    {
        printf("$ ");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            break;
        }

    char *args[1024];
    int n = 0;
    for (char *p = line; *p != '\0';)
    {
        while (*p == ' ' || *p == '\n')
        {
            *p = '\0';
            p++;
        }

        if (*p != '\0')
        {
            args[n++] = p;
        }

        while (*p != '\0' && *p != ' ' && *p != '\n')
        {
            p++;
        }
    }
    args[n++] = NULL;

    if (args[0] == NULL)
    {
        continue;
    }

        int child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            continue;
        }

        if (child_pid == 0)
        {
            execvp(args[0], args);
            perror("exec");
            exit(EXIT_FAILURE);
        }

        waitpid(child_pid, NULL, 0);
    }

    return EXIT_SUCCESS;
}
