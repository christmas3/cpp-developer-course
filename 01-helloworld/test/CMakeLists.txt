set(ALL_TESTS "")

set(INCLUDES
        "${PROJECT_SOURCE_DIR}"
        )

set(GTEST_LIBS
        gtest
        )

set(TEST_EXECUTABLE "version_test")
add_executable(version_test main_test.cpp version_test.cpp)
target_include_directories(${TEST_EXECUTABLE} PRIVATE ${INCLUDES})
target_link_libraries(${TEST_EXECUTABLE} helloworld ${GTEST_LIBS})
add_test(NAME version_test COMMAND "version_test" WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}")
