cmake_minimum_required(VERSION 3.0.0)
project(YouChat-Pro VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(src SRC)
aux_source_directory(src/response SRC)

add_executable(test test.cpp)

target_link_libraries(test
    mysqlclient
    pthread
    hiredis
    jsoncpp
)

# ---------- redis++ -----------------
find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(test PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(test ${REDIS_PLUS_PLUS_LIB})
