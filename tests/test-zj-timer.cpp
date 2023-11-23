#include "gtest/gtest.h"
#include <thread>
#include <chrono>

#include "zj-timer.hpp"
#include "zj-logging-macros-simplified.hpp"

ZjChronoCount TestZjTimer(unsigned hz, double sec)
{
    using std::literals::chrono_literals::operator""s;

    auto start = ZjChronoClock::now();
    auto target_ns_count = ZjChronoNs(static_cast<ZjChronoNs::rep>(sec * zj::kSecToNs));

    ZjTimer timer(fmt::format("test: {}hz, {}s", hz, sec));
    timer.Init(hz);

    int actual_total_count = 0;
    while (std::chrono::duration_cast<ZjChronoNs>(ZjChronoClock::now() - start) < target_ns_count) {
        timer.Start();
        std::this_thread::sleep_for(0.0015s);
        actual_total_count++;
        timer.Guard();
    }

    _ZJ_DEBUG("name: {}, overtime count: {}", timer.Name(), timer.OvertimeCount());
    _ZJ_DEBUG("actual total count vs. expected: [{} | {:.1f}]", actual_total_count, hz * sec);
    _ZJ_DEBUG(
        "avg loop time vs. period: [{:.5f} s | {:.5f} s]", timer.TotalLoopAverage(ZjChronoUnit::kSec), timer.Period(ZjChronoUnit::kSec));
    return timer.TotalCount();
}

TEST(TestZjTimer, One)
{
    EXPECT_NEAR(TestZjTimer(100, 0.1), 10, 1);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Two)
{
    EXPECT_NEAR(TestZjTimer(200, 0.2), 40, 1);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Three)
{
    EXPECT_NEAR(TestZjTimer(300, 0.1), 30, 1);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Four)
{
    // Why the avg loop rate is far lower than 0.002s, but the while loop ran way less than expected; probably due to linux non-realtime
    EXPECT_NEAR(TestZjTimer(500, 0.3), 150, 10);
    ZjLogger::GetInstance().Shutdown();
}

TEST(TestZjTimer, Five)
{
    EXPECT_NEAR(TestZjTimer(30, 0.1), 3, 1);
    ZjLogger::GetInstance().Shutdown();
}
