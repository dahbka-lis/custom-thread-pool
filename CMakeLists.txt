cmake_minimum_required(VERSION 3.26)
project(custom_thread_pool)

set(CMAKE_CXX_STANDARD 20)

add_executable(custom_thread_pool main.cpp thread_pool/thread_pool.cpp queue/queue.cpp)
