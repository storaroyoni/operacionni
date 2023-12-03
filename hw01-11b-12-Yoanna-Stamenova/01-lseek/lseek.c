#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct
{
    char data;
    unsigned char nextElementAddress;
} Block;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage : %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("failed to open");
        return EXIT_FAILURE;
    }

    Block currentBlock;
    for (int i = 0; i < 128; i++)
    {

        if (read(fd, &currentBlock, sizeof(Block)) != sizeof(Block))
        {
            perror("failed to read the block :( )");
            return EXIT_FAILURE;
        }

        if (currentBlock.nextElementAddress == 0)
        {
            break;
        }

        printf("%c", currentBlock.data);
        lseek(fd, currentBlock.nextElementAddress, SEEK_SET);
      }

    close(fd);
    return EXIT_SUCCESS;
}
