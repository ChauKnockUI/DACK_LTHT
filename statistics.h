#ifndef STATISTICS_H
#define STATISTICS_H

// Hàm lấy thời gian hiện tại
double get_current_time();

// Hàm ghi log
void log_message(const char *message, const char *direction);

// Hàm ghi nhận thời gian truyền tin nhắn
void record_message_timing(const char *message_type, double time_taken);

// Hàm in thống kê
void print_statistics();

#endif // STATISTICS_H