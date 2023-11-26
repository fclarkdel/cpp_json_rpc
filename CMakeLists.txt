cmake_minimum_required(VERSION 3.26)

project(cpp_json_rpc)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(source/cpp_json_rpc)

add_library(
    cpp_json_rpc
    INTERFACE
)
target_link_libraries(
    cpp_json_rpc
    INTERFACE
    cpp_json_rpc_library
)