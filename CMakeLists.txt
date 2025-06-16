cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(cache-architecture-sim ${SOURCE_FILES})

target_include_directories(cache-architecture-sim PRIVATE include)

if(WIN32)
    message(STATUS "Configuring for Windows")
elseif(APPLE)
    message(STATUS "Configuring for macOS")
elseif(UNIX)
    message(STATUS "Configuring for Linux/Unix")
endif()