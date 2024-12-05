#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include "fifo_ipc.h"
#include "sync_control.h"  // Thêm đồng bộ semaphore
#include <time.h>

// Biến toàn cục
int fifo_fd;                
int message_count = 0;       // Bộ đếm tin nhắn
double total_time = 0.0;     // Tổng thời gian truyền
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex để đồng bộ log

// Hàm nhận và xử lý tin nhắn
void receive_message(const char *message) {
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    // Tách thời gian và nội dung tin nhắn
    long start_sec, start_nsec;
    char content[200];
    if (sscanf(message, "%ld.%ld|%[^\n]", &start_sec, &start_nsec, content) == 3) {
        // Tính thời gian truyền
        double transmission_time = (end_time.tv_sec - start_sec) +
                                   (end_time.tv_nsec - start_nsec) / 1e9;

        // Cập nhật log hiệu suất
        message_count++;
        total_time += transmission_time;

        // Ghi vào file log (được đồng bộ bằng mutex)
        pthread_mutex_lock(&log_mutex);
        FILE* log_file = fopen("performance_log.txt", "a");
        
        if (log_file != NULL) {
            fprintf(log_file, "Message %d: %s\n", message_count, content);
            fprintf(log_file, "Transmission Time: %.6f seconds\n", transmission_time);
            fclose(log_file);
        }
        pthread_mutex_unlock(&log_mutex);
    } else {
        fprintf(stderr, "Error parsing message: %s\n", message);
    }
}

// Hàm ghi log thời gian trung bình
void log_average_time() {
    printf("Logging average time...\n");
    if (message_count > 0) {
        double average_time = total_time / message_count;

        pthread_mutex_lock(&log_mutex);
        FILE* log_file = fopen("performance_log.txt", "a");
        if (log_file != NULL) {
            fprintf(log_file, "Total Messages: %d\n", message_count);
            fprintf(log_file, "Average Transmission Time: %.6f seconds\n", average_time);
            fclose(log_file);
        }
        pthread_mutex_unlock(&log_mutex);
    } else {
        printf("No messages to log average time\n");
    }
}


// Hàm main
int main() {
    const char *fifo_name = "/tmp/my_fifo";

    init_sync();  // Khởi tạo semaphore

    fifo_fd = open(fifo_name, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for reading");
        exit(EXIT_FAILURE);
    }
    printf("Consumer: FIFO opened for reading.\n");

    char buffer[256];
    while (1) {
        wait_sync();  // Chờ tín hiệu từ Producer
        printf("Consumer: Wait completed\n");  // Thêm thông báo debug

        int bytes_read = read(fifo_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // Kết thúc chuỗi
            printf("Consumer: Received -> %s\n", buffer);
            receive_message(buffer);
        } else if (bytes_read == 0) {
            printf("Consumer: No more data to read, exiting...\n");
            break;
        } else {
            perror("Error reading from FIFO");
            break;
        }
    }
    printf("Consumer: Calling log_average_time()\n");
    log_average_time();
    close(fifo_fd);
    cleanup_sync();  // Dọn dẹp semaphore
    return 0;
}
