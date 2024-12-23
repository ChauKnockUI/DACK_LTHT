#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "fifo_ipc.h"
#include "sync_control.h"
#include <time.h>
#include "statistics.h"

int fifo_fd;

void send_message(const char *message) {
    double start_time = get_current_time();
    write(fifo_fd, message, strlen(message) + 1);
    wait_ack();
    double end_time = get_current_time();
    record_message_timing("TEXT", end_time - start_time);
    log_message(message, "SENT");
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
        signal_sync();
        wait_ack();
        printf("Producer: Sent %zu bytes\n", bytes_read);
    }
    fclose(file);

    const char *eof_marker = "EOF";
    write(fifo_fd, eof_marker, strlen(eof_marker) + 1);
    signal_sync();
    wait_ack();
    printf("Producer: Sent EOF marker\n");
}

void send_text_message() {
    char text[256];
    printf("Enter text message: ");
    getchar(); // Clear newline
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline

    char formatted_message[512];
    snprintf(formatted_message, sizeof(formatted_message), "TEXT|%s", text);
    
    send_message(formatted_message);
    signal_sync();
    printf("Producer: Sent text message and signaled Consumer\n");
}

void send_integer_message() {
    int number;
    printf("Enter integer number: ");
    while (scanf("%d", &number) != 1) {
        printf("Invalid input. Please enter an integer: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    char formatted_message[64];
    snprintf(formatted_message, sizeof(formatted_message), "INT|%d", number);
    
    send_message(formatted_message);
    signal_sync();
    printf("Producer: Sent integer message and signaled Consumer\n");
}

void send_float_message() {
    float number;
    printf("Enter float number: ");
    while (scanf("%f", &number) != 1) {
        printf("Invalid input. Please enter a float: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    char formatted_message[64];
    snprintf(formatted_message, sizeof(formatted_message), "FLOAT|%f", number);
    
    send_message(formatted_message);
    signal_sync();
    printf("Producer: Sent float message and signaled Consumer\n");
}

void send_file_message() {
    char file_path[256];
    printf("Enter file path: ");
    getchar(); // Clear newline
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0; // Remove newline

    send_file(file_path);
}

void display_menu() {
    printf("\n=== Producer Menu ===\n");
    printf("1. Send Text Message\n");
    printf("2. Send Integer Number\n");
    printf("3. Send Float Number\n");
    printf("4. Send File\n");
    printf("5. Exit\n");
    printf("Enter your choice (1-5): ");
}

int main() {
    const char *fifo_name = "/tmp/my_fifo";

    init_sync();
    create_fifo(fifo_name);

    fifo_fd = open(fifo_name, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(EXIT_FAILURE);
    }

    int choice;
    do {
        display_menu();
        while (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number (1-5): ");
            while (getchar() != '\n'); // Clear input buffer
        }

        switch (choice) {
            case 1:
                send_text_message();
                break;
            case 2:
                send_integer_message();
                break;
            case 3:
                send_float_message();
                break;
            case 4:
                send_file_message();
                break;
            case 5:
                printf("Sending END signal to consumer...\n");
                send_message("END");
                signal_sync();
                wait_ack();
                print_statistics();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    close(fifo_fd);
    cleanup_sync();
    return 0;
}