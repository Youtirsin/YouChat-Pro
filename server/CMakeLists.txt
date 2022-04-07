cmake_minimum_required(VERSION 3.0.0)
project(YouChat-Pro VERSION 0.1.0)

# include(CTest)
# enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(src SERVER_SRC)
aux_source_directory(src/request SERVER_SRC)
aux_source_directory(src/response SERVER_SRC)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(server main.cpp
    ${SERVER_SRC}
)


target_link_libraries(server
    pthread
    jsoncpp
    hiredis
    mysqlclient
)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

# ---------- redis++ -----------------
find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(server PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(server ${REDIS_PLUS_PLUS_LIB})
