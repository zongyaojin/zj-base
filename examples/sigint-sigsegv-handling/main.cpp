#include "zj-logging.hpp"
#include "zj-tools.hpp"

#include <csignal>

// Signal handler function for SIGINT (Ctrl-C)
void SigintHandler(int signal)
{
    _ZJ_WARN("Program terminated by Ctrl-C (SIGINT).");

    ZjLogger::GetInstance().Shutdown();
    ZjProgramSwitch::GetInstance().TurnOff();

    exit(signal);
}

// Signal handler function for SIGSEGV (Segmentation fault)
void SigsegvHandler(int signal)
{
    _ZJ_WARN("Segmentation fault (SIGSEGV) occurred.");

    ZjLogger::GetInstance().Shutdown();
    ZjProgramSwitch::GetInstance().TurnOff();

    exit(signal);
}

void TurnOffRoutine()
{
    _ZJ_DEBUG("turn off routine says bye...");
}

int main()
{
    ZjProgramSwitch::GetInstance().TurnOn();
    ZjProgramSwitch::GetInstance().RegisterTurnOffRoutine(&TurnOffRoutine);

    /// @see <signum_generic.h> for more signals
    std::signal(SIGINT, SigintHandler);
    std::signal(SIGSEGV, SigsegvHandler);

    _ZJ_INFO("hello");

    std::vector<int>* ptr = nullptr;

    auto start_time = ZjChronoClock::now();

    while (true) {
        auto time_spent = std::chrono::duration_cast<ZjChronoMs>(ZjChronoClock::now() - start_time);
        _ZJ_INFO_T(1, "Ctrl-C to terminate, or wait 5 sec to trigger segmentation fault, current count: [{}]", time_spent.count());
        if (time_spent.count() > 5000) {
            _ZJ_WARN("triggering segmentation fault now");
            ptr->push_back(1); // cppcheck-suppress nullPointer
        }
    }

    return 0;
}
