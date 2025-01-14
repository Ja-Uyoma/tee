add_executable(tee)

target_sources(tee 
    PUBLIC main.c
    PRIVATE tee.h tee.c
)

target_compile_features(tee PUBLIC c_std_23)

target_compile_options(tee
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror>
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
)
