cmake_minimum_required(VERSION 3.17)
project(philo_two C)

set(CMAKE_C_STANDARD 11)

add_executable(philo_two
        philo_two.c
        philo_two.h
        utils_1.c
        utils_2.c init.c init_sem.c run.c)
