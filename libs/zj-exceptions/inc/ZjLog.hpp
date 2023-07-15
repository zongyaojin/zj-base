#include "ZjSingleton.hpp"
#include <string>

class ZjLog : public ZjSingleton<ZjLog>
{
public:
    void info(const std::string& msg);

    void warn(const std::string& msg);

    void fault(const std::string& msg);

    void failure(const std::string& msg);
};