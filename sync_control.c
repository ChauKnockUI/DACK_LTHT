#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Semaphore chính cho tín hiệu giữa Producer và Consumer
sem_t *sem;
// Semaphore ACK cho tín hiệu phản hồi từ Consumer đến Producer
sem_t *ack_sem;

void init_sync() {
    // Khởi tạo semaphore chính
    sem = sem_open("/my_sem", O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) {
        perror("Failed to create semaphore /my_sem");
        exit(EXIT_FAILURE);
    }

    ack_sem = sem_open("/ack_sem", O_CREAT, 0644, 0);
    if (ack_sem == SEM_FAILED) {
        perror("Failed to create semaphore /ack_sem");
        sem_close(sem);
        sem_unlink("/my_sem");  // Dọn dẹp nếu khởi tạo `ack_sem` thất bại
        exit(EXIT_FAILURE);
    }
}

void wait_sync() {
    // Consumer đợi tín hiệu từ Producer
    if (sem_wait(sem) == -1) {
        perror("Error waiting for semaphore");
        exit(EXIT_FAILURE);
    }
}

void signal_sync() {
    // Producer gửi tín hiệu cho Consumer
    if (sem_post(sem) == -1) {
        perror("Error signaling semaphore");
        exit(EXIT_FAILURE);
    }
}

void wait_ack() {
    // Producer đợi ACK từ Consumer
    if (sem_wait(ack_sem) == -1) {
        perror("Error waiting for ACK semaphore");
        exit(EXIT_FAILURE);
    }
}

void signal_ack() {
    // Consumer gửi ACK cho Producer
    if (sem_post(ack_sem) == -1) {
        perror("Error signaling ACK semaphore");
        exit(EXIT_FAILURE);
    }
}

void cleanup_sync() {
    if (sem_close(sem) == -1) {
        perror("Error closing semaphore /my_sem");
    }

    if (sem_unlink("/my_sem") == -1) {
        if (errno != ENOENT) { // ENOENT: Semaphore không tồn tại
            perror("Error unlinking /my_sem");
        } else {
            printf("/my_sem already unlinked or does not exist.\n");
        }
    }

    if (sem_close(ack_sem) == -1) {
        perror("Error closing semaphore /ack_sem");
    }

    if (sem_unlink("/ack_sem") == -1) {
        if (errno != ENOENT) {
            perror("Error unlinking /ack_sem");
        } else {
            printf("/ack_sem already unlinked or does not exist.\n");
        }
    }
}
