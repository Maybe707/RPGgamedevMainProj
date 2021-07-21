cmake_minimum_required(VERSION 3.15)
project(RPG)
 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

file(GLOB SOURCES src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

add_subdirectory(libs/glad)
target_link_libraries(${CMAKE_PROJECT_NAME} glad)

add_subdirectory(libs/glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL::GL)

add_subdirectory(libs/stb_image)
target_link_libraries(${CMAKE_PROJECT_NAME} stb_image)
