cmake_minimum_required(VERSION 3.26)

project(cpp_json_rpc)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(source/cpp_json_rpc)

add_library(
    CppJsonRpc
    INTERFACE
)
target_link_libraries(
    CppJsonRpc
    INTERFACE
    CppJsonRpc_Library
)