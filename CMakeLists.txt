cmake_minimum_required(VERSION 3.15)

project(Lab)
find_package(OpenGL REQUIRED)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)

add_subdirectory(Engine)
# list(APPEND EXTRA_LIBS Engine)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Engine")

include_directories(external/glfw/include/)
include_directories(external/stb/)

add_executable(${PROJECT_NAME} Lab/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad OpenGL::GL)

target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# set_target_properties(Engine PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

