#include <stdio.h>
#include <time.h>

void log_message(const char *message) {
    FILE *log_file = fopen("/tmp/fifo_log.txt", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    time_t now;
    time(&now);
    fprintf(log_file, "[%s] %s\n", ctime(&now), message);

    fclose(log_file);
}

void log_performance(int num_messages) {
    printf("Logging performance: %d messages processed\n", num_messages);
    // Ghi log vào file hoặc database
}
