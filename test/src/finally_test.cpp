#include <kj/finally.hpp>
#include <gtest/gtest.h>

TEST(FinallyTest, CalledAtScopeEnd)
{
    int value = 5;
    {
        auto changeValue = kj::finally([&value] { value = 10; });
        EXPECT_EQ(5, value);
    }
    EXPECT_EQ(10, value);
}

TEST(FinallyTest, CanReleaseFinally)
{
    int value = 5;
    {
        auto changeValue = kj::finally([&value] { value = 10; });
        changeValue.release();
    }
    EXPECT_EQ(5, value);
}
