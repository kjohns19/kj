#include <kj/location.hpp>
#include <gtest/gtest.h>
#include <sstream>

TEST(LocationTest, DefaultZero)
{
    kj::Location loc;
    EXPECT_EQ(0, loc.x());
    EXPECT_EQ(0, loc.y());
}

TEST(LocationTest, ConstructorXY)
{
    kj::Location loc(1, 2);
    EXPECT_EQ(1, loc.x());
    EXPECT_EQ(2, loc.y());
}

TEST(LocationTest, Comparable)
{
    kj::Location loc1(1, 2);
    kj::Location loc2(4, 5);

    EXPECT_TRUE(loc1 != loc2);
    EXPECT_FALSE(loc1 == loc2);
}

TEST(LocationTest, Modifiable)
{
    kj::Location loc;
    loc.x(4);
    loc.y(8);
    EXPECT_EQ(4, loc.x());
    EXPECT_EQ(8, loc.y());

    loc.set(5, 6);
    EXPECT_EQ(5, loc.x());
    EXPECT_EQ(6, loc.y());
}

TEST(LocationTest, Translatable)
{
    kj::Location loc(4, 5);
    loc.translate(1, 2);
    EXPECT_EQ(5, loc.x());
    EXPECT_EQ(7, loc.y());
    kj::Location loc2 = loc.translated(-4, 6);
    EXPECT_EQ(5, loc.x());
    EXPECT_EQ(7, loc.y());
    EXPECT_EQ(1, loc2.x());
    EXPECT_EQ(13, loc2.y());
}

TEST(LocationTest, Printable)
{
    kj::Location loc(3, 4);
    std::ostringstream stream;
    stream << loc;
    EXPECT_EQ("(3, 4)", stream.str());
}
