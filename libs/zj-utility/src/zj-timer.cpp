/**
 * @file zj-timer.cpp
 * @author Zongyao Jin (zongyaojin@outlook.com)
 * @date 2023-08
 * @copyright Copyright (c) 2023 by Zongyao Jin
 */

#include "zj-timer.hpp"
#include "zj-logging-macros-simplified.hpp"

#include <thread>

ZjTimer::ZjTimer(const std::string& name)
{
    if (!name.empty()) {
        name_ = fmt::format("ZjTimer-{}", name);
    }
}

void ZjTimer::Init(const unsigned frequency, const unsigned overtime_count_limit)
{
    total_count_ = 0;
    total_time_spent = 0;

    overtime_count_limit_ = overtime_count_limit;
    overtime_count_ = 0;

    period_ = ZjChronoNs {static_cast<ZjChronoCount>(zj::kSecToNs / frequency)};
}

ZjChronoCount ZjTimer::Guard()
{
    total_count_++;

    time_spent_ = std::chrono::duration_cast<ZjChronoNs>(ZjChronoClock::now() - start_time_);
    total_time_spent += time_spent_.count();
    time_left_ = period_ - time_spent_;

    if (time_left_.count() > 0) [[likely]] {
        std::this_thread::sleep_for(time_left_);
    } else if (time_left_.count() < 0) [[unlikely]] {
        overtime_count_++;
    }

    // There should be an [[unlikely]] here, but the current version of cpplint doesn't get it
    if (overtime_count_limit_ > 0 && overtime_count_ > overtime_count_limit_) {
        auto&& loopAvgMs = static_cast<double>(total_time_spent) / total_count_ * zj::kNsToMs;
        auto&& periodMs = period_.count() * zj::kNsToMs;
        _ZJ_WARN("[{}] ========== ==========", name_);
        _ZJ_WARN("-- overtime count [{}] exceeds limit [{}]", overtime_count_, overtime_count_limit_);
        _ZJ_WARN("-- loop average [{:.3f} ms], expected period  [{:.3f} ms]", loopAvgMs, periodMs);
        _ZJ_WARN("-- overtime count has been reset to start over");
        overtime_count_ = 0;
    }

    return time_spent_.count();
}

double ZjTimer::TotalLoopAverage(const ZjChronoUnit unit) const
{
    switch (unit) {
        case ZjChronoUnit::kSec:
            return static_cast<double>(total_time_spent) / total_count_ * zj::kNsToSec;
        case ZjChronoUnit::kMs:
            return static_cast<double>(total_time_spent) / total_count_ * zj::kNsToMs;
        case ZjChronoUnit::kUs:
            return static_cast<double>(total_time_spent) / total_count_ * zj::kNsToUs;
        case ZjChronoUnit::kNs:
            return static_cast<double>(total_time_spent) / total_count_;
        default:
            return 0.0;
    }
}

double ZjTimer::Period(const ZjChronoUnit unit) const
{
    switch (unit) {
        case ZjChronoUnit::kSec:
            return period_.count() * zj::kNsToSec;
        case ZjChronoUnit::kMs:
            return period_.count() * zj::kNsToMs;
        case ZjChronoUnit::kUs:
            return period_.count() * zj::kNsToUs;
        case ZjChronoUnit::kNs:
            return period_.count();
        default:
            return 0.0;
    }
}
