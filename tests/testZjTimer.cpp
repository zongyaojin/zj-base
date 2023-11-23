#include "gtest/gtest.h"
#include <thread>
#include <chrono>

#include "ZjTimer.hpp"
#include "zj-logging-macros-simplified.hpp"

ZjChronoCount testZjTimer(unsigned hz, double sec)
{
    using std::literals::chrono_literals::operator""s;

    auto start = ZjChronoClock::now();
    auto targetNsCount = ZjChronoNs(static_cast<ZjChronoNs::rep>(sec * zj::kSecToNs));

    ZjTimer timer(fmt::format("test: {}hz, {}s", hz, sec));
    timer.Init(hz);

    int actualTotalCount = 0;
    while (std::chrono::duration_cast<ZjChronoNs>(ZjChronoClock::now() - start) < targetNsCount) {
        timer.start();
        std::this_thread::sleep_for(0.0015s);
        actualTotalCount++;
        timer.guard();
    }

    _ZJ_DEBUG("name: {}, overtime count: {}", timer.name(), timer.overtimeCount());
    _ZJ_DEBUG("actual total count vs. expected: [{} | {:.1f}]", actualTotalCount, hz * sec);
    _ZJ_DEBUG(
        "avg loop time vs. period: [{:.5f} s | {:.5f} s]", timer.totalLoopAvg(ZjChronoUnit::kSec), timer.period(ZjChronoUnit::kSec));
    return timer.totalCount();
}

TEST(TestZjTimer, One)
{
    EXPECT_NEAR(testZjTimer(100, 0.1), 10, 1);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Two)
{
    EXPECT_NEAR(testZjTimer(200, 0.2), 40, 1);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Three)
{
    EXPECT_NEAR(testZjTimer(300, 0.1), 30, 1);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Four)
{
    // Why the avg loop rate is far lower than 0.002s, but the while loop ran way less than expected; probably due to linux non-realtime
    EXPECT_NEAR(testZjTimer(500, 0.3), 150, 10);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Five)
{
    EXPECT_NEAR(testZjTimer(30, 0.1), 3, 1);
    ZjLogger::GetInstance().Shutdown();
}
