#ifndef SYNC_CONTROL_H
#define SYNC_CONTROL_H

#include <pthread.h>
#include <semaphore.h>

// Biến mutex và semaphore
extern pthread_mutex_t mutex;
extern sem_t *sem;

// Hàm khởi tạo đồng bộ
void init_sync();

// Hàm chờ tín hiệu (Consumer)
void wait_sync();

// Hàm phát tín hiệu (Producer)
void signal_sync();

// Hàm dọn dẹp đồng bộ
void cleanup_sync();

#endif // SYNC_CONTROL_H
