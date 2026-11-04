cmake_minimum_required(VERSION 3.10)
project(Sage)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)
find_package(cJSON REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -g -O1)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROJECT_NAME} cjson)
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)