# Declare library

add_library(tee_lib OBJECT)

target_sources(tee_lib
    PRIVATE
        tee.h
        tee.c
)

target_include_directories(tee_lib
    ${warning_guard}
    PUBLIC
        "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(tee_lib
    PUBLIC
        c_std_23
)

find_package(hedley REQUIRED)

target_link_libraries(tee_lib
    PRIVATE
        hedley::hedley
)

# Declare executable

add_executable(tee_exe)

target_sources(tee_exe
    PRIVATE
        main.c
)

add_executable(tee::exe ALIAS tee_exe)

set_property(TARGET tee_exe PROPERTY OUTPUT_NAME tee)

target_compile_features(tee_exe
    PRIVATE
        c_std_23
)

target_link_libraries(tee_exe
    PRIVATE
        tee_lib
)
