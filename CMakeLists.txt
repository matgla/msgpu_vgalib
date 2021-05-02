cmake_minimum_required(VERSION 3.20)

project (msgpu_vgalib C CXX) 

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(source)
add_subdirectory(interface)

add_executable(msgpu_test)

target_sources(msgpu_test 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
)

target_link_libraries(msgpu_test 
    PRIVATE 
        msgpu_vgalib
)

