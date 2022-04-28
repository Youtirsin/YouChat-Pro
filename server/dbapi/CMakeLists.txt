cmake_minimum_required(VERSION 3.0.0)
project(dbapi)

# required by redis++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# third party libraries
set(CMAKE_PREFIX_PATH "/home/youtirsin/mybin/rediscpp")

aux_source_directory(${PROJECT_SOURCE_DIR}/src DBAPI_SRC)

add_library(${PROJECT_NAME} ${DBAPI_SRC})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    hiredis
    mysqlclient
    pthread

    request
    response
)

# ---------- redis++ -----------------

find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${REDIS_PLUS_PLUS_HEADER}
)

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(${PROJECT_NAME} 
    ${REDIS_PLUS_PLUS_LIB}
)

# test
# add_executable(test test.cpp)
# target_link_libraries(test ${PROJECT_NAME})

# target_include_directories(test
#     PRIVATE ${PROJECT_SOURCE_DIR}/include
# )