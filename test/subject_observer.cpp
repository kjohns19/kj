#include <kj/subject.hpp>
#include <kj/observer.hpp>
#include <gtest/gtest.h>

struct TestObserver : public kj::Observer<int>
{
    TestObserver(): count(0) {}
    void update(int dummy) override { count++; }
    int count;
};

class SubjectObserverTest : public ::testing::Test
{
public:
    void SetUp() {}
    void TearDown() {}
    kj::Subject<int> subject;
    TestObserver observer1;
    TestObserver observer2;
};

TEST_F(SubjectObserverTest, CanNotifyOne)
{
    subject.addObserver(observer1);
    subject.notifyObservers(0);
    EXPECT_EQ(1, observer1.count);
}

TEST_F(SubjectObserverTest, CanNotifyMultiple)
{
    subject.addObserver(observer1);
    subject.addObserver(observer2);
    subject.notifyObservers(0);
    EXPECT_EQ(1, observer1.count);
    EXPECT_EQ(1, observer2.count);
}

TEST_F(SubjectObserverTest, CanRemove)
{
    subject.addObserver(observer1);
    subject.removeObserver(observer1);
    subject.notifyObservers(0);
    EXPECT_EQ(0, observer1.count);
}

TEST_F(SubjectObserverTest, CanAddMultipleTimes)
{
    int count = 5;
    for(int i = 0; i < 5; i++)
        subject.addObserver(observer1);
    subject.notifyObservers(0);
    EXPECT_EQ(count, observer1.count);
}
