#include "zj-log.hpp"
#include "zj-utility.hpp"

#include <csignal>

// Signal handler function for SIGINT (Ctrl-C)
void sigintHandler(int signal)
{
    _ZJ_WARN("Program terminated by Ctrl-C (SIGINT).");

    ZjLog::getInstance().shutdown();
    ZjProgramSwitch::getInstance().turnOff();

    exit(signal);
}

// Signal handler function for SIGSEGV (Segmentation fault)
void sigsegvHandler(int signal)
{
    _ZJ_WARN("Segmentation fault (SIGSEGV) occurred.");

    ZjLog::getInstance().shutdown();
    ZjProgramSwitch::getInstance().turnOff();

    exit(signal);
}

void turnOffRoutine()
{
    _ZJ_DEBUG("turn off routine says bye...");
}

int main()
{
    ZjProgramSwitch::getInstance().turnOn();
    ZjProgramSwitch::getInstance().registerTurnOffRoutine(&turnOffRoutine);

    /// @see <signum_generic.h> for more signals
    std::signal(SIGINT, sigintHandler);
    std::signal(SIGSEGV, sigsegvHandler);

    _ZJ_INFO("hello");

    std::vector<int>* ptr = nullptr;

    auto startTime = ZjChrono::Clock::now();

    while (true) {
        auto timeSpent = std::chrono::duration_cast<ZjChrono::Ms>(ZjChrono::Clock::now() - startTime);
        _ZJ_INFO_T(1, "Ctrl-C to terminate, or wait 5 sec to trigger segmentation fault, current count: [{}]", timeSpent.count());
        if (timeSpent.count() > 5000) {
            _ZJ_WARN("triggering segmentation fault now");
            ptr->push_back(1);
        }
    }

    return 0;
}
