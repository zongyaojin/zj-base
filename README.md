# ZJ Basic Cpp Tools

<!-- https://docs.github.com/en/actions/monitoring-and-troubleshooting-workflows/adding-a-workflow-status-badge -->
[![Build status](https://github.com/zongyaojin/zj-base/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/zongyaojin/zj-base/actions/workflows/c-cpp.yml)
[![GitHub license](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://github.com/zongyaojin/zj-base/blob/main/LICENSE)

v1.0

- `ZjChrono` provides some time-related functions, definitions, and aliases
- `ZjSingleton` provides a singleton base class using the Curiously Recurring Template Pattern

- `ZjDebug` provides macros for try, catch, and throw mechanisms that can report error with the call stack information
- `ZjLogMacroExtensions` provides macros for assertion and regular, condition-based, and periodic message with built-in log support

- `ZjCsvLog` provides a singleton class that can create as many files as needed and log Eigen vectors with time stamp to a given file in a thread-safe fashion
- `ZjProgramSwitch` provides a singleton class that can be used as a global program switch and run user-specified functions when it turns off
- `ZjTimer` provides a timer class that can be used to guard a periodic loop of a certain frequency
- `ZjUtility` provides some functions for map access and pointer clean up

- `examples/sigint-sigsegv-handling` provides an example showing how to handle a Ctrl-C or a Segmentation Fault terminated program
