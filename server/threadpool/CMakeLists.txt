cmake_minimum_required(VERSION 3.0.0)
project(threadpool)

add_library(${PROJECT_NAME} threadpool.cpp)

target_link_libraries(${PROJECT_NAME}
    pthread
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)