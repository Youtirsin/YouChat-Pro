cmake_minimum_required(VERSION 3.0.0)
project(myepoll)

add_library(${PROJECT_NAME} epoll.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)