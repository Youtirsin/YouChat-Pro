cmake_minimum_required(VERSION 3.0.0)
project(YouChat-Pro VERSION 0.1.0)

# include(CTest)
# enable_testing()

aux_source_directory(src/client SRC)
aux_source_directory(src/request SRC)
aux_source_directory(src/response SRC)

add_executable(client src/client/client.cpp ${SRC})

target_include_directories( client
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
