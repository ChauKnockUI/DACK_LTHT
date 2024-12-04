#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include "fifo_ipc.h"
#include "sync_control.h"  // Thêm đồng bộ semaphore

pthread_mutex_t fifo_mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    const char *fifo_name = "/tmp/my_fifo";

    init_sync();  // Khởi tạo semaphore

    int fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for reading");
        exit(EXIT_FAILURE);
    }
    printf("Consumer: FIFO opened for reading.\n");

    char buffer[100];
    while (1) {
        wait_sync();  // Chờ tín hiệu từ Producer

        pthread_mutex_lock(&fifo_mutex);

        int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // Kết thúc chuỗi
            printf("Consumer: Received -> %s", buffer);
        } else if (bytes_read == 0) {
            printf("Consumer: No more data to read, exiting...\n");
            pthread_mutex_unlock(&fifo_mutex);
            break;
        } else {
            perror("Error reading from FIFO");
            pthread_mutex_unlock(&fifo_mutex);
            break;
        }

        pthread_mutex_unlock(&fifo_mutex);
    }

    close(fd);
    cleanup_sync();  // Dọn dẹp semaphore
    return 0;
}
