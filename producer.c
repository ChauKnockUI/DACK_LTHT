#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include "fifo_ipc.h"
#include "sync_control.h"  // Thêm đồng bộ semaphore

pthread_mutex_t fifo_mutex = PTHREAD_MUTEX_INITIALIZER;  // Khởi tạo mutex

int main() {
    const char *fifo_name = "/tmp/my_fifo";
    const char *messages[] = {"Message 1", "Message 2", "Message 3", "Message 4", "Message 5"};
    
    init_sync();  // Khởi tạo semaphore
    // Tạo FIFO nếu chưa tồn tại
    create_fifo(fifo_name);
    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&fifo_mutex);

        char message[100];
        snprintf(message, sizeof(message), "%s\n", messages[i]);  // Thêm ký tự xuống dòng sau mỗi thông điệp
        printf("Producer: Writing %s to FIFO\n", message);
        
        if (write(fd, message, strlen(message)) == -1) {
            perror("Error writing to FIFO");
        } else {
            printf("Producer: Data written to FIFO\n");
            signal_sync();  // Báo hiệu cho Consumer rằng có dữ liệu mới
        }

        pthread_mutex_unlock(&fifo_mutex);
        sleep(2);  // Chờ trước khi gửi tin nhắn tiếp theo
    }

    close(fd);
    cleanup_sync();  // Dọn dẹp semaphore
    return 0;
}
