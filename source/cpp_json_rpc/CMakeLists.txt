add_library(
    CppJsonRpc_Library
    concurrent_queue.hpp
    error.cpp
    error.hpp
    notification.hpp
    notification.cpp
    proxy.hpp
    proxy.cpp
    response.hpp
    response.cpp
    request.hpp
    request.cpp
    shared_member_types.hpp
)
target_include_directories(
    CppJsonRpc_Library
    PUBLIC
    ..
)
include(FetchContent)

FetchContent_Declare(
    fluent_curl
    GIT_REPOSITORY https://github.com/fclarkdel/fluent_curl.git
    GIT_TAG main
)
FetchContent_MakeAvailable(
    fluent_curl
)
target_link_libraries(
    CppJsonRpc_Library
    PUBLIC
    fluent_curl
)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(
        CppJsonRpc_Tests
        concurrent_queue.test.cpp
        error.test.cpp
        notification.test.cpp
        proxy.test.cpp
        request.test.cpp
        response.test.cpp
    )
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    target_link_libraries(
        CppJsonRpc_Tests
        PRIVATE
        CppJsonRpc_Library
        gmock_main
    )
    enable_testing()
endif()