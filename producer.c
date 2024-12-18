#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "fifo_ipc.h"
#include "sync_control.h"  // Thêm đồng bộ semaphore
#include <time.h>

int fifo_fd;  // Biến toàn cục lưu descriptor của FIFO

void send_message(const char *message) {
    write(fifo_fd, message, strlen(message) + 1);
    wait_ack(); 
}

void send_file(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    printf("Producer: Sending file -> %s\n", file_path);

    char buffer[256];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        ssize_t bytes_written = write(fifo_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to FIFO");
            fclose(file);
            return;
        }
        signal_sync();  // Gửi tín hiệu tới Consumer
        wait_ack();   // Chờ tín hiệu ACK từ Consumer
        printf("Producer: Sent %zu bytes\n", bytes_read);
    }
    fclose(file);

    // Gửi cờ EOF riêng biệt
    const char *eof_marker = "EOF";
    write(fifo_fd, eof_marker, strlen(eof_marker) + 1);
    signal_sync();  // Gửi tín hiệu tới Consumer
    wait_ack(); 
    printf("Producer: Sent EOF marker\n");
}






int main() {
    const char *fifo_name = "/tmp/my_fifo";
    const char *messages[] = {
        "TEXT|Hello, this is a text message!",
        "INT|42",
        "FLOAT|3.14"
    };

    init_sync();  // Khởi tạo semaphore
    create_fifo(fifo_name);

    fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) {
        send_message(messages[i]);
        signal_sync();  // Báo hiệu Consumer xử lý
        printf("Producer: Sent message and signaled Consumer\n");
        sleep(2);
    }

    // Gửi một file
    send_file("/home/trnghuy-bru/Desktop/DACK_LTHT/example.txt");
        printf("Producer: Send file and signaled Consumer\n");

    // Gửi tín hiệu kết thúc
    send_message("END");
    signal_sync();
    wait_ack() ; // Đảm bảo Consumer nhận tín hiệu END

    close(fifo_fd);
    cleanup_sync();  // Dọn dẹp semaphore
    return 0;
}

