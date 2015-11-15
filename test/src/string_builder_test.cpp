#include <kj/string_builder.hpp>
#include <gtest/gtest.h>

TEST(StringBuilderTest, StartsEmpty)
{
    std::string str = kj::StringBuilder();
    EXPECT_EQ("", str);
}

TEST(StringBuilderTest, WritesStrings)
{
    std::string str = kj::StringBuilder() << "Hello " << "world";
    EXPECT_EQ("Hello world", str);
}

TEST(StringBuilderTest, WorksWithModifiers)
{
    std::string str = kj::StringBuilder() << 16 << " " << std::hex << 16;
    EXPECT_EQ("16 10", str);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
