#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Semaphore chính cho tín hiệu giữa Producer và Consumer
sem_t *sem;

void init_sync() {
    // Khởi tạo semaphore chính
    sem = sem_open("/my_sem", O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) {
        perror("Failed to create semaphore /my_sem");
        exit(EXIT_FAILURE);
    }
}

void wait_sync() {
    if (sem_wait(sem) == -1) {
        perror("Error waiting for semaphore");
        exit(EXIT_FAILURE);
    }
}

void signal_sync() {
    if (sem_post(sem) == -1) {
        perror("Error signaling semaphore");
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

}
