cmake_minimum_required(VERSION 3.22)
project(C_Compiler)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES} ${INCLUDE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} fmt)
