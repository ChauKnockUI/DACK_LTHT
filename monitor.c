#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fifo_ipc.h"

void monitor_fifo(const char *fifo_name) {
    while (1) {
        if (access(fifo_name, F_OK) != -1) {
            printf("FIFO exists, monitoring...\n");
            // Thực hiện các hành động giám sát khác ở đây
        } else {
            printf("FIFO does not exist\n");
            break;
        }
        sleep(2);  // Kiểm tra mỗi 2 giây
    }
}
