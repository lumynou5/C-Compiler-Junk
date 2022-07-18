cmake_minimum_required(VERSION 3.22)
project(C_Compiler)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} fmt)
