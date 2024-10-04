cmake_minimum_required(VERSION 3.23)

project(tee 
    VERSION 0.1 
    LANGUAGES C
    DESCRIPTION "Unix utility program that reads from stdin and writes to stdout and files"
)

# Only set the C standard if it has not been set elsewhere
if (NOT DEFINED CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 17)
endif()

set(CMAKE_C_EXTENSIONS OFF)

include(cmake/EnforceOutOfSourceBuilds.cmake)
include(cmake/StandardProjectSettings.cmake)

add_subdirectory(src)
add_subdirectory(test)