cmake_minimum_required(VERSION 3.15)

project(keep)
find_package(OpenGL REQUIRED)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)

include_directories(external/glfw/include/)
include_directories(external/stb/)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad OpenGL::GL)