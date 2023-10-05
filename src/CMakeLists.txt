add_executable(tee)

target_sources(tee 
    PUBLIC main.c
    PRIVATE tee.h tee.c
)

target_compile_features(tee PUBLIC c_std_17)

target_compile_options(tee 
    PUBLIC -Wall -Wextra -Werror -Wpedantic
)
