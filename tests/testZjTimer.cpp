#include <gtest/gtest.h>
#include <thread>

#include "ZjTimer.hpp"
#include "ZjLogMacrosExtension.hpp"

ZjChrono::Count testZjTimer(unsigned hz, double sec)
{
    using namespace std::chrono_literals;

    auto start = ZjChrono::Clock::now();
    auto targetNsCount = ZjChrono::Ns(static_cast<long>(sec * ZjChrono::s_secToNs));

    ZjTimer timer(fmt::format("test: {}hz, {}s", hz, sec));
    timer.init(hz);

    int actualTotalCount = 0;
    while (std::chrono::duration_cast<ZjChrono::Ns>(ZjChrono::Clock::now() - start) < targetNsCount) {
        timer.start();
        std::this_thread::sleep_for(0.0015s);
        actualTotalCount++;
        timer.guard();
    }

    _ZJ_DEBUG("name: {}, overtime count: {}", timer.name(), timer.overtimeCount());
    _ZJ_DEBUG("actual total count vs. expected: [{} | {:.1f}]", actualTotalCount, hz * sec);
    _ZJ_DEBUG(
        "avg loop time vs. period: [{:.5f} s | {:.5f} s]", timer.totalLoopAvg(ZjChrono::Unit::Sec), timer.period(ZjChrono::Unit::Sec));
    return timer.totalCount();
}

TEST(TestZjTimer, One)
{
    EXPECT_NEAR(testZjTimer(100, 0.1), 10, 1);
}

TEST(TestZjTimer, Two)
{
    EXPECT_NEAR(testZjTimer(200, 0.2), 40, 1);
}

TEST(TestZjTimer, Three)
{
    EXPECT_NEAR(testZjTimer(300, 0.1), 30, 1);
}

TEST(TestZjTimer, Four)
{
    // why the avg loop rate is far lower than 0.002s, but the while loop ran way less than expected???
    EXPECT_NEAR(testZjTimer(500, 0.3), 150, 10);
}

TEST(TestZjTimer, Five)
{
    EXPECT_NEAR(testZjTimer(30, 0.1), 3, 1);
}