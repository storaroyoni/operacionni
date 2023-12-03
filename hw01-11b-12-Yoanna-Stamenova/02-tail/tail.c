#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file1> [file2] ...\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t chunk_size = 1024;

    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);

        if (fd == -1) {
            perror("open");
            continue;
        }
      
        printf("==> %s <==\n", argv[i]);

        off_t file_size = lseek(fd, 0, SEEK_END);
        off_t offset = 0;
        char buffer[chunk_size];
        int lines_count = 0;

        for (offset = file_size - chunk_size; offset >= 0 && lines_count < 10; offset -= chunk_size) {
            lseek(fd, offset, SEEK_SET);

            ssize_t read_bytes = read(fd, buffer, chunk_size);

            if (read_bytes == -1) {
                perror("read");
                close(fd);
                return EXIT_FAILURE;
            }

            for (ssize_t i = read_bytes - 1; i >= 0 && lines_count < 10; i--) {
                if (buffer[i] == '\n') {
                    lines_count++;
                }
            }
        }
      
        lseek(fd, offset + chunk_size, SEEK_SET);

        while (read(fd, buffer, sizeof(char)) > 0) {
            write(STDOUT_FILENO, buffer, sizeof(char));
        }

        close(fd);
    }

    return EXIT_SUCCESS;
}
