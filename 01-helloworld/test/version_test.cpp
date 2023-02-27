#include <gtest/gtest.h>

#include "lib.h"

extern int kArgc;
extern char** kArgv;

TEST(HelloworldTest, Version)
{
    ASSERT_EQ(kArgc, 2);
    EXPECT_EQ(version_lib::version(), atoi(kArgv[1]));
}
