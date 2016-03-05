#include <kj/string_util.hpp>
#include <gtest/gtest.h>

TEST(StringUtilTestTrim, LTrimWorks)
{
    std::string str;
    std::string original = "Hello world";

    str = original;
    EXPECT_EQ(original, kj::StringUtil::ltrimmed(str));

    str = std::string("    ") + original;
    EXPECT_EQ(original, kj::StringUtil::ltrimmed(str));

    str = original + std::string("    ");
    EXPECT_EQ(str, kj::StringUtil::ltrimmed(str));

    str = std::string("    ") + original;
    kj::StringUtil::ltrim(&str);
    EXPECT_EQ(original, str);
}
TEST(StringUtilTestTrim, RTrimWorks)
{
    std::string str;
    std::string original = "Hello world";

    str = original;
    EXPECT_EQ(original, kj::StringUtil::rtrimmed(str));

    str = std::string("    ") + original;
    EXPECT_EQ(str, kj::StringUtil::rtrimmed(str));

    str = original + std::string("    ");
    EXPECT_EQ(original, kj::StringUtil::rtrimmed(str));

    str = original + std::string("    ");
    kj::StringUtil::rtrim(&str);
    EXPECT_EQ(original, str);
}
TEST(StringUtilTestTrim, TrimWorks)
{
    std::string str;
    std::string original = "Hello world";

    str = original;
    EXPECT_EQ(original, kj::StringUtil::trimmed(str));

    str = std::string("    ") + original;
    EXPECT_EQ(original, kj::StringUtil::trimmed(str));

    str = original + std::string("    ");
    EXPECT_EQ(original, kj::StringUtil::trimmed(str));

    str = std::string("    ") + original + std::string("    ");
    EXPECT_EQ(original, kj::StringUtil::trimmed(str));

    str = std::string("    ") + original + std::string("    ");
    kj::StringUtil::trim(&str);
    EXPECT_EQ(original, str);
}

TEST(StringUtilTestCase, UpcaseWorks)
{
    std::string str;
    std::string expect = "HELLO WORLD";

    str = "hello world";
    EXPECT_EQ(expect, kj::StringUtil::upcased(str));

    str = "hello world";
    kj::StringUtil::upcase(&str);
    EXPECT_EQ(expect, str);
}
TEST(StringUtilTestCase, DowncaseWorks)
{
    std::string str;
    std::string expect = "hello world";

    str = "HELLO WORLD";
    EXPECT_EQ(expect, kj::StringUtil::downcased(str));

    str = "HELLO WORLD";
    kj::StringUtil::downcase(&str);
    EXPECT_EQ(expect, str);
}

TEST(StringUtilTestCase, CompareWorks)
{
    EXPECT_EQ(kj::StringUtil::caseCompare("aaa", "AAA"), 0);
    EXPECT_LT(kj::StringUtil::caseCompare("aaa", "BBB"), 0);
    EXPECT_LT(kj::StringUtil::caseCompare("AAA", "bbb"), 0);
    EXPECT_TRUE(kj::StringUtil::caseEqual("aaa", "AAA"));
    EXPECT_TRUE(kj::StringUtil::caseLess("aaa", "BBB"));
}

TEST(StringUtilTestReplace, ReplaceWorks)
{
    std::string str = "Hello world";
    EXPECT_EQ("Hello everyone", kj::StringUtil::replaced("world", "everyone", str));
    EXPECT_EQ("Goodbye world", kj::StringUtil::replaced("Hello", "Goodbye", str));
    EXPECT_EQ("Held", kj::StringUtil::replaced("llo wor", "", str));

    kj::StringUtil::replace("world", "everyone", &str);
    EXPECT_EQ("Hello everyone", str);
}

TEST(StringUtilTestReplace, ReplaceAllWorks)
{
    std::string str = "Location location location";
    EXPECT_EQ("Locale locale locale", kj::StringUtil::replacedAll("tion", "le",str));

    kj::StringUtil::replaceAll("tion", "le", &str);
    EXPECT_EQ("Locale locale locale", str);
}
