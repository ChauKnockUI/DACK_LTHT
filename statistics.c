#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

// Cấu trúc lưu trữ thống kê cho mỗi loại tin nhắn
struct MessageStats {
    int count;
    double total_time;
    double min_time;
    double max_time;
};

// Biến toàn cục lưu trữ thống kê
static struct MessageStats text_stats = {0, 0.0, 999999.0, 0.0};
static struct MessageStats int_stats = {0, 0.0, 999999.0, 0.0};
static struct MessageStats float_stats = {0, 0.0, 999999.0, 0.0};
static struct MessageStats file_stats = {0, 0.0, 999999.0, 0.0};

// Hàm lấy thời gian hiện tại theo microseconds
double get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

void log_message(const char *message, const char *direction) {
    FILE *log_file = fopen("/tmp/fifo_log.txt", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }

    time_t now;
    time(&now);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Xóa ký tự newline
    fprintf(log_file, "[%s] %s: %s\n", time_str, direction, message);

    fclose(log_file);
}

// Hàm cập nhật thống kê cho một loại tin nhắn
void update_stats(struct MessageStats *stats, double time_taken) {
    stats->count++;
    stats->total_time += time_taken;
    if (time_taken < stats->min_time) stats->min_time = time_taken;
    if (time_taken > stats->max_time) stats->max_time = time_taken;
}

// Hàm ghi nhận thời gian truyền tin nhắn
void record_message_timing(const char *message_type, double time_taken) {
    if (strcmp(message_type, "TEXT") == 0) {
        update_stats(&text_stats, time_taken);
    } else if (strcmp(message_type, "INT") == 0) {
        update_stats(&int_stats, time_taken);
    } else if (strcmp(message_type, "FLOAT") == 0) {
        update_stats(&float_stats, time_taken);
    } else if (strcmp(message_type, "FILE") == 0) {
        update_stats(&file_stats, time_taken);
    }
}

// Hàm in báo cáo thống kê
void print_statistics() {
    printf("\n=== Communication Statistics ===\n");
    
    // Text Messages
    if (text_stats.count > 0) {
        printf("\nText Messages:\n");
        printf("Count: %d\n", text_stats.count);
        printf("Average Time: %.6f seconds\n", text_stats.total_time / text_stats.count);
        printf("Min Time: %.6f seconds\n", text_stats.min_time);
        printf("Max Time: %.6f seconds\n", text_stats.max_time);
    }
    
    // Integer Messages
    if (int_stats.count > 0) {
        printf("\nInteger Messages:\n");
        printf("Count: %d\n", int_stats.count);
        printf("Average Time: %.6f seconds\n", int_stats.total_time / int_stats.count);
        printf("Min Time: %.6f seconds\n", int_stats.min_time);
        printf("Max Time: %.6f seconds\n", int_stats.max_time);
    }
    
    // Float Messages
    if (float_stats.count > 0) {
        printf("\nFloat Messages:\n");
        printf("Count: %d\n", float_stats.count);
        printf("Average Time: %.6f seconds\n", float_stats.total_time / float_stats.count);
        printf("Min Time: %.6f seconds\n", float_stats.min_time);
        printf("Max Time: %.6f seconds\n", float_stats.max_time);
    }
    
    // File Transfers
    if (file_stats.count > 0) {
        printf("\nFile Transfers:\n");
        printf("Count: %d\n", file_stats.count);
        printf("Average Time: %.6f seconds\n", file_stats.total_time / file_stats.count);
        printf("Min Time: %.6f seconds\n", file_stats.min_time);
        printf("Max Time: %.6f seconds\n", file_stats.max_time);
    }
}