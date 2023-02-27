#include <gtest/gtest.h>

int kArgc;
char** kArgv;

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    kArgc = argc;
    kArgv = argv;
    return RUN_ALL_TESTS();
}
