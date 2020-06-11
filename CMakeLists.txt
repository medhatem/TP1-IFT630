cmake_minimum_required(VERSION 3.16)
project(TP1_IFT630)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(TP1_IFT630 main.cpp)
add_executable(philo_sem philosophers.cpp)
add_executable(barber_sem barber.cpp)

target_link_libraries(TP1_IFT630 Threads::Threads)
target_link_libraries(philo_sem Threads::Threads)
target_link_libraries(barber_sem Threads::Threads)