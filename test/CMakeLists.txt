add_executable(testee)

find_package(cmocka REQUIRED)

target_include_directories(testee 
    PRIVATE "${PROJECT_SOURCE_DIR}/src"
)

target_sources(testee
    PUBLIC 
        main.c
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/tee.h"
        "${PROJECT_SOURCE_DIR}/src/tee.c"
)

target_link_libraries(testee cmocka::cmocka)

target_compile_features(testee PUBLIC c_std_17)

target_compile_options(testee 
    PUBLIC -Wall -Wextra -Werror -Wpedantic
)