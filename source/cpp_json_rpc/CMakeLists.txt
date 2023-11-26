add_library(
    cpp_json_rpc_library
    error.cpp
    error.hpp
    notification.hpp
    notification.cpp
    session.hpp
    session.cpp
    response.hpp
    response.cpp
    request.hpp
    request.cpp
    shared_member_types.hpp
)
target_include_directories(
    cpp_json_rpc_library
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
    cpp_json_rpc_library
    PUBLIC
    fluent_curl
)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(
        cpp_json_rpc_tests
        error.test.cpp
        notification.test.cpp
        session.test.cpp
        request.test.cpp
        response.test.cpp
    )
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    target_link_libraries(
        cpp_json_rpc_tests
        PRIVATE
        cpp_json_rpc_library
        gmock_main
    )
    enable_testing()
endif()