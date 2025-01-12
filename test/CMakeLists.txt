cmake_minimum_required(VERSION 3.5)
project(mini_rpc_test LANGUAGES CXX)

set(MINIRPC_TEST_BINARY_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${MINIRPC_TEST_BINARY_PATH})
set(LIBRARY_OUTPUT_PATH ${MINIRPC_TEST_BINARY_PATH})

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Forcing Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")


#Google test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG release-1.11.0
)
FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    set(GTEST_BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/googletest-build")
    add_subdirectory(${googletest_SOURCE_DIR} ${GTEST_BINARY_DIR})
endif()
#

macro(mini_rpc_add_test test_name)
    set(the_test_binary "${test_name}_test")
    add_executable(${the_test_binary} "./${the_test_binary}.cpp")
    target_link_libraries(${the_test_binary} mini_rpc gtest_main gmock_main)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        target_link_libraries(${the_test_binary}  pthread)
    endif()

    add_test(NAME "${test_name}.test" COMMAND ${the_test_binary})
    message("add test ${the_test_binary}")
#    add_custom_command(TARGET ${the_test_binary} POST_BUILD
#                       COMMAND ${the_test_binary})
endmacro(mini_rpc_add_test)

mini_rpc_add_test(serialization)


