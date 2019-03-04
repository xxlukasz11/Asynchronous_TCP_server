cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../bin)

set(CMAKE_CXX_COMPILER "g++")

project (server_example)

include_directories("${PROJECT_SOURCE_DIR}/../include")
file(GLOB SOURCES "../src/*.cpp" "*.cpp")
add_executable(server_example ${SOURCES})

set_property(TARGET server_example PROPERTY CXX_STANDARD 11)
set_property(TARGET server_example PROPERTY C_STANDARD 11)

target_compile_options(server_example PRIVATE -Wall)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "server_example")
target_link_libraries(server_example pthread)
