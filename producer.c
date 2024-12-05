#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include "fifo_ipc.h"
#include "sync_control.h"  // Thêm đồng bộ semaphore
#include <time.h>

int fifo_fd;  // Biến toàn cục lưu descriptor của FIFO
struct timespec start_time; // Biến lưu thời gian bắt đầu

void send_message(const char* message) {
    // Ghi lại thời gian bắt đầu gửi tin nhắn
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Gửi tin nhắn qua FIFO với thời gian
    char message_with_time[256];
    snprintf(message_with_time, sizeof(message_with_time), "%ld.%ld|%s", 
             start_time.tv_sec, start_time.tv_nsec, message);
    write(fifo_fd, message_with_time, strlen(message_with_time) + 1);
}


int main() {
    const char *fifo_name = "/tmp/my_fifo";
    const char *messages[] = {"Message 1", "Message 2", "Message 3", "Message 4", "Message 5"};
    
    init_sync();  // Khởi tạo semaphore

    // Tạo FIFO nếu chưa tồn tại
    create_fifo(fifo_name);

    fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++) {
        char message[100];
        snprintf(message, sizeof(message), "%s\n", messages[i]);  // Thêm ký tự xuống dòng sau mỗi thông điệp
        printf("Producer: Writing %s to FIFO\n", message);
        
        send_message(message);
        printf("Producer: Data written to FIFO\n");
        signal_sync();  // Báo hiệu cho Consumer rằng có dữ liệu mới

        sleep(3);  // Chờ trước khi gửi tin nhắn tiếp theo
    }

    close(fifo_fd);
    cleanup_sync();  // Dọn dẹp semaphore
    return 0;
}
