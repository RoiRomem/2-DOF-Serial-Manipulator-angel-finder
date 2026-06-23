cmake_minimum_required(VERSION 3.20)
project(2DOF C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_VISIBILITY_PRESET default)

file(GLOB_RECURSE ALL_SOURCES "${PROJECT_SOURCE_DIR}/engine/*.c")

add_library(ik_engine SHARED ${ALL_SOURCES})

target_include_directories(ik_engine PUBLIC
    "${PROJECT_SOURCE_DIR}/engine"
    "${PROJECT_SOURCE_DIR}/engine/geometricSolver"
)

target_link_libraries(ik_engine PUBLIC m)
