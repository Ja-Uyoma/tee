cmake_minimum_required(VERSION 3.17)

project(tee 
    VERSION 0.1 
    DESCRIPTION "Unix utility program that reads from stdin and writes to stdout and files"
    LANGUAGES C
)

set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(src)
