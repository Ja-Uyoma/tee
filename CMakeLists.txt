cmake_minimum_required(VERSION 3.23)

project(tee 
    VERSION 0.1 
    LANGUAGES C
    DESCRIPTION "Unix utility program that reads from stdin and writes to stdout and files"
)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/EnforceOutOfSourceBuilds.cmake)

add_subdirectory(src)
add_subdirectory(test)