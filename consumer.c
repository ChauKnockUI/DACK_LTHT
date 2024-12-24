#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "fifo_ipc.h"
#include "sync_control.h"
#include "statistics.h"

int fifo_fd;

void handle_text(const char *text) {
    printf("Received Text: %s\n", text);
    log_message(text, "RECEIVED");
}

void handle_int(int value) {
    printf("Received Integer: %d\n", value);
    char message[64];
    snprintf(message, sizeof(message), "%d", value);
    log_message(message, "RECEIVED");
}

void handle_float(float value) {
    printf("Received Float: %.2f\n", value);
    char message[64];
    snprintf(message, sizeof(message), "%.2f", value);
    log_message(message, "RECEIVED");
}

void handle_file_data(const char *data) {
    FILE *file = fopen("/home/chauzz/Desktop/DACK/received_file.txt", "a");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    printf("Received File\n");
    fwrite(data, 1, strlen(data), file);
    fclose(file);
    log_message("/home/chauzz/Desktop/DACK/received_file.txt", "RECEIVED");
}

void process_message(const char *message) {
    if (strncmp(message, "TEXT|", 5) == 0) {
        handle_text(message + 5);
    } else if (strncmp(message, "INT|", 4) == 0) {
        int value = atoi(message + 4);
        handle_int(value);
    } else if (strncmp(message, "FLOAT|", 6) == 0) {
        float value = atof(message + 6);
        handle_float(value);
    } else if (strncmp(message, "FILE|DATA|", 10) == 0) {
        handle_file_data(message + 10);
    } else if (strncmp(message, "EOF", 3) == 0) {
        // Nếu nhận được EOF, dừng quá trình nhận file
        printf("Received EOF marker. Finished receiving file data.\n");
        signal_sync();
        return;  // Dừng nhận file
    } else if (strcmp(message, "END") == 0) {
        // Nếu nhận được END, dừng consumer
        printf("Received END signal. Exiting...\n");
        signal_sync();
        cleanup_sync(); // Dọn dẹp semaphore
        close(fifo_fd); // Đóng FIFO
        exit(0);  // Thoát khỏi vòng lặp và kết thúc chương trình
    }
    signal_sync();
}

int main() {
    const char *fifo_name = "/tmp/my_fifo";

    init_sync();  // Khởi tạo semaphore

    fifo_fd = open(fifo_name, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (1) {
        printf("Consumer: Waiting for signal from Producer\n");

        int bytes_read = read(fifo_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // Đảm bảo kết thúc chuỗi
            process_message(buffer);
        } else if (bytes_read == 0) {
            printf("No more data to read. Exiting...\n");
            break;
        } else {
            perror("Error reading from FIFO");
            break;
        }
    }

    close(fifo_fd);
    cleanup_sync();  // Dọn dẹp semaphore
    return 0;
}