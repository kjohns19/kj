#include <kj/nullable.hpp>
#include <gtest/gtest.h>

TEST(NullableTest, StartsNull)
{
    kj::Nullable<int> value;
    EXPECT_TRUE(value.isNull());
}

TEST(NullableTest, StoresValue)
{
    kj::Nullable<int> value(10);
    ASSERT_FALSE(value.isNull());
    EXPECT_EQ(10, value.value());
}

TEST(NullableTest, CanMakeNull)
{
    kj::Nullable<int> value(10);
    ASSERT_FALSE(value.isNull());
    value.makeNull();
    EXPECT_TRUE(value.isNull());
}

TEST(NullableTest, IsAssignable)
{
    kj::Nullable<int> value1, value2;
    value1.makeValue(10);
    value2 = value1;
    ASSERT_TRUE(!value2.isNull());
    EXPECT_EQ(value1.value(), value2.value());
}
TEST(NullableTest, IsMoveable)
{
    kj::Nullable<int> value1, value2;
    value1.makeValue(10);
    value2 = std::move(value1);
    EXPECT_TRUE(value1.isNull());
    ASSERT_TRUE(!value2.isNull());
    EXPECT_EQ(10, value2.value());
}
