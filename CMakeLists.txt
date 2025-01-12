cmake_minimum_required(VERSION 3.15)

project(mini_rpc LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MAF_ENABLE_TEST ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(MINIRPC_ROOT_DIR .)
set(MINIRPC_LIB_INCLUDE_PATH ${MINIRPC_ROOT_DIR}/include)
include_directories(${MINIRPC_LIB_INCLUDE_PATH})

# --> Collect platforms dependent sources/headers
file(GLOB_RECURSE MINIRPC_COMMON_SOURCES
    src/common/mini_rpc/*.cpp)
file(GLOB_RECURSE MINIRPC_LIBRARY_HEADERS
    include/*.h)
file(GLOB_RECURSE MINIRPC_COMMON_PRIV_SOURCES
    src/common/mini_rpc/*.h)
# <-- platforms dependent sources/headers

if(BUILD_SHARED_LIBS)
    set(MINIRPC_BUILD_SHARED_LIB ${BUILD_SHARED_LIBS})
endif(BUILD_SHARED_LIBS)

if(MINIRPC_BUILD_SHARED_LIB)
    add_definitions(-DMINIRPC_SHARED_LIBRARY)
else()
    add_definitions(-DMINIRPC_STATIC_LIBRARY)
endif()

# Build mini_rpc.lib
set( MINIRPC_ALL_SOURCES
    ${MINIRPC_COMMON_SOURCES}
    ${MINIRPC_PLATFORM_SOURCES}
    ${MINIRPC_LIBRARY_HEADERS}
    ${MINIRPC_COMMON_PRIV_SOURCES}
    ${MINIRPC_PLATFORM_HEADERS}
    )
    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MINIRPC_BUILD_SHARED_LIB)
    add_library(${PROJECT_NAME} SHARED ${MINIRPC_ALL_SOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${MINIRPC_ALL_SOURCES}
        include/mini_rpc/serialization/SerializableObjectBegin.macro.h
        include/mini_rpc/serialization/SerializableObjectEnd.macro.h)
endif(MINIRPC_BUILD_SHARED_LIB)

if(MAF_ENABLE_TEST)
    enable_testing()
    add_subdirectory("test/")
endif(MAF_ENABLE_TEST)

# Grouping sources/headers into tree layout for IDE browsing
if(NOT DISABLE_SOURCE_GROUP)
    source_group(TREE ${PROJECT_SOURCE_DIR}/src PREFIX "Sources" FILES ${MINIRPC_COMMON_SOURCES} )
    source_group(TREE ${PROJECT_SOURCE_DIR}/src PREFIX "Sources" FILES ${MINIRPC_PLATFORM_SOURCES} )
    source_group(TREE ${PROJECT_SOURCE_DIR}/src PREFIX "Sources" FILES ${MINIRPC_COMMON_PRIV_SOURCES} )
    source_group(TREE ${PROJECT_SOURCE_DIR}/src PREFIX "Sources" FILES ${MINIRPC_PLATFORM_HEADERS} )
    source_group(TREE ${PROJECT_SOURCE_DIR}/include PREFIX "include" FILES ${MINIRPC_LIBRARY_HEADERS} )
endif(NOT DISABLE_SOURCE_GROUP)
