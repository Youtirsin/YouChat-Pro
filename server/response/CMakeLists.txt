cmake_minimum_required(VERSION 3.0.0)
project(response)

aux_source_directory(${PROJECT_SOURCE_DIR}/src RESPONSE_SRC)

add_library(${PROJECT_NAME} ${RESPONSE_SRC})

target_link_libraries(${PROJECT_NAME}
    jsoncpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
