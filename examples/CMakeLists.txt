
add_executable(server_example
    server.cpp
)
target_link_libraries(server_example
        PRIVATE
   mini_rpc 
)
target_include_directories(server_example
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${protobuf_SOURCE_DIR}/src
)

