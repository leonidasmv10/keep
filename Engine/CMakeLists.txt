cmake_minimum_required(VERSION 3.15)

file(GLOB_RECURSE files_code
         RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
         ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
         ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(Engine SHARED ${files_code})
