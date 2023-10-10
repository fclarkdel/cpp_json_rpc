cmake_minimum_required(VERSION 3.26)

project(CppJsonRpc)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Source/CppJsonRpc)

add_library(
    CppJsonRpc
    INTERFACE
)
target_link_libraries(
    CppJsonRpc
    INTERFACE
    CppJsonRpc_Library
)