# Parent project does not export its library target, so this CMakeLists.txt implicitly
# depends on being added from it, i.e., the testing is done only from the build tree and
# is not feasible from an install location

project(teeTests
    LANGUAGES C
)

# Dependencies

find_package(cmocka REQUIRED)

# Tests

add_executable(tee_test)

target_sources(tee_test
    PRIVATE
        main.test.c
)

target_link_libraries(tee_test
    PRIVATE
        tee_lib
        cmocka::cmocka
)

target_compile_features(tee_test
    PRIVATE
        c_std_23
)

add_test(NAME tests COMMAND tee_test)
