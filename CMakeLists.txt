cmake_minimum_required(VERSION 3.27)
project(kp8)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_CXX_STANDARD 17)
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)
include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c"
                  "${PROJECT_SOURCE_DIR}/include/*.h"
                  "${PROJECT_SOURCE_DIR}/include/*/*.h")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
add_executable(kp8 ${sources})

