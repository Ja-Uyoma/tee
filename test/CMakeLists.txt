add_executable(testee)

find_package(cmocka REQUIRED)

target_sources(testee
    PUBLIC main.c
)

target_link_libraries(testee cmocka::cmocka)

target_compile_features(testee PUBLIC c_std_17)

target_compile_options(testee 
    PUBLIC -Wall -Wextra -Werror -Wpedantic
)