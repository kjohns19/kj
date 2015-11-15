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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
