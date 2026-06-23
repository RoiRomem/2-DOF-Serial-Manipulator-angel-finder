cmake_minimum_required(VERSION 3.20)

project(2DOF C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(2DOF ${SOURCES})

target_include_directories(2DOF PRIVATE
    "${PROJECT_SOURCE_DIR}/engine"
)

target_link_libraries(2DOF PRIVATE m)
