cmake_minimum_required(VERSION 3.23)

project(tee 
    VERSION 0.1 
    LANGUAGES C
    DESCRIPTION "Unix utility program that reads from stdin and writes to stdout and files"
)

# Only set the C standard if it has not been set elsewhere
if (NOT DEFINED CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 23)
endif()

set(CMAKE_C_EXTENSIONS OFF)

include(cmake/EnforceOutOfSourceBuilds.cmake)
include(cmake/StandardProjectSettings.cmake)

add_subdirectory(src)

# Don't consider testing if not the top-level project
if (NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()

include(CTest)

if (BUILD_TESTING)
    message("Adding tests...")
    add_subdirectory(test)
endif()
