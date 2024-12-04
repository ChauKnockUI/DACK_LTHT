#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void create_fifo(const char *fifo_name) {
    if (access(fifo_name, F_OK) == -1) {  // Kiểm tra xem FIFO đã tồn tại chưa
        if (mkfifo(fifo_name, 0666) == -1) {
            perror("Failed to create FIFO");
            exit(EXIT_FAILURE);
        }
        printf("FIFO created: %s\n", fifo_name);
    } else {
        printf("FIFO already exists: %s\n", fifo_name);
    }
}


void write_to_fifo(const char *fifo_name, const char *message) {
    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }
    write(fd, message, strlen(message) + 1);
    close(fd);
}

ssize_t read_from_fifo(int fd, char *buffer, size_t buffer_size) {
    return read(fd, buffer, buffer_size);
}

void delete_fifo(const char *fifo_name) {
    if (unlink(fifo_name) == -1) {
        perror("Failed to delete FIFO");
    }
}
