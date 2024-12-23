cmake_minimum_required(VERSION 3.10)
project(DACK)

# Thêm đường dẫn tới tệp header
include_directories(${CMAKE_SOURCE_DIR})
# Hoặc nếu thư mục include/
#include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(producer producer.c fifo_ipc.c sync_control.c statistics.c)
add_executable(consumer consumer.c fifo_ipc.c sync_control.c statistics.c)

# Thêm thư viện pthread
target_link_libraries(producer pthread)
target_link_libraries(consumer pthread)