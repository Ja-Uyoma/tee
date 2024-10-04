add_executable(tests)

find_package(cmocka REQUIRED)

target_include_directories(tests
    PRIVATE "${PROJECT_SOURCE_DIR}/src"
)

target_sources(tests
    PUBLIC 
        main.test.c
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/tee.h"
        "${PROJECT_SOURCE_DIR}/src/tee.c"
)

target_link_libraries(tests cmocka::cmocka)

target_compile_features(tests PUBLIC c_std_17)

target_compile_options(tests
    PUBLIC -Wall -Wextra -Werror -Wpedantic
)