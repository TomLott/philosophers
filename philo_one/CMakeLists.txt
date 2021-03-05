cmake_minimum_required(VERSION 3.17)
project(filo C)

set(CMAKE_C_STANDARD 11)

add_executable(filo
        philo_one.c init.c utils_1.c threads.c status.c utils_2.c)
