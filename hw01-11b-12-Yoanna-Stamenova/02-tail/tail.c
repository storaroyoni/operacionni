#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <file1> [file2] ...\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);

        if (fd == -1)
        {
        perror("open");
        }

        if (i != 1){
        printf("==> %s <==\n", argv[i]);
        }

        lseek(fd, -10 * sizeof(char), SEEK_END);

        char buffer[1024];
        int n;
        while ((n = read(fd, buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, n);
        }

        close(fd);
    }

    return EXIT_SUCCESS;
}
