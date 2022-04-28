cmake_minimum_required(VERSION 3.0.0)
project(YouChat-Pro VERSION 0.1.0)

# required by redis++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# third party libraries
set(CMAKE_PREFIX_PATH "/home/youtirsin/mybin/rediscpp")

add_subdirectory(request)
add_subdirectory(response)
add_subdirectory(dbapi)
add_subdirectory(myepoll)
add_subdirectory(threadpool)
add_subdirectory(server)


add_executable(youchatpro main.cpp)

target_link_libraries(youchatpro
    server
)