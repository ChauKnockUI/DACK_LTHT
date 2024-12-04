#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t *sem;

void init_sync() {
    sem = sem_open("/my_sem", O_CREAT, 0644, 0);  // Semaphore khởi tạo với giá trị ban đầu là 0
    if (sem == SEM_FAILED) {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }
}

void wait_sync() {
    sem_wait(sem);  // Đợi tín hiệu từ Producer
}

void signal_sync() {
    sem_post(sem);  // Gửi tín hiệu cho Consumer
}

void cleanup_sync() {
    sem_close(sem);  // Đóng semaphore
    sem_unlink("/my_sem");  // Xóa semaphore khỏi hệ thống
}
