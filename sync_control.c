#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Xóa mutex vì không sử dụng
sem_t *sem;

void init_sync() {
    sem = sem_open("/my_sem", O_CREAT, 0644, 0);  // Semaphore khởi tạo với giá trị ban đầu là 0
    if (sem == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }
}

void wait_sync() {
    if (sem_wait(sem) == -1) {  // Đợi tín hiệu từ Producer
        perror("Error waiting for semaphore");
        exit(EXIT_FAILURE);
    }
}

void signal_sync() {
    if (sem_post(sem) == -1) {  // Gửi tín hiệu cho Consumer
        perror("Error signaling semaphore");
        exit(EXIT_FAILURE);
    }
}

void cleanup_sync() {
    if (sem_close(sem) == -1) {  // Đóng semaphore
        perror("Error closing semaphore");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink("/my_sem") == -1) {  // Xóa semaphore khỏi hệ thống
        perror("Error unlinking semaphore");
        exit(EXIT_FAILURE);
    }
}
