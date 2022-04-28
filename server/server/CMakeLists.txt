cmake_minimum_required(VERSION 3.0.0)
project(YouChat-Pro VERSION 0.1.0)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SERVER_SRC)
message(${SERVER_SRC})

add_library(server ${SERVER_SRC})

target_include_directories(server
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(server
    myepoll
    threadpool
    dbapi
    request
    response
)