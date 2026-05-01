cmake_minimum_required(VERSION 3.10)
project(AnimWeaver)

set(GLFW_DIR "libraries/glfw")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${GLFW_DIR})

include_directories(
    ${GLFW_DIR}/include)
include_directories(
    "code/include")

file(GLOB_RECURSE SOURCES 
    "code/source/*.cpp")

file(GLOB_RECURSE HEADERS 
    "code/include/*.h")

source_group(TREE "code/source" PREFIX "source" FILES ${SOURCES})
source_group(TREE "code/include" PREFIX "include" FILES ${HEADERS})

add_executable(AnimWeaver ${SOURCES} ${HEADERS})
target_link_libraries(AnimWeaver glfw)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AnimWeaver)