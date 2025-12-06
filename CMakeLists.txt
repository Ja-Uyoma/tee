cmake_minimum_required(VERSION 3.23)

include(cmake/prelude.cmake)

project(tee 
    VERSION 0.1
    DESCRIPTION "Unix utility program that reads from stdin and writes to stdout and files"
    HOMEPAGE_URL "https://github.com/Ja-Uyoma/tee"
    LANGUAGES C
)

include(cmake/variables.cmake)

# Declare library and executable

add_subdirectory(source)

# Install rules

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif()

# Developer mode

if(NOT tee_DEVELOPER_MODE)
    return()
elseif()
    message(AUTHOR_WARNING "Developer mode is intended for developers of tee")
endif()

include(cmake/dev-mode.cmake)
