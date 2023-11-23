# ZJ C++ Base

[![C++ Build](https://github.com/zongyaojin/zj-base/actions/workflows/cpp-build.yml/badge.svg)](https://github.com/zongyaojin/zj-base/actions/workflows/cpp-build.yml)
[![GitHub license](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://github.com/zongyaojin/zj-base/blob/main/LICENSE)

This package contains some basic tools such as logging and debugging for C++ projects.

- `ZjChrono` provides some time-related functions, definitions, and aliases
- `ZjSingleton` provides a singleton base class using the Curiously Recurring Template Pattern

- `zj-debug.hpp` provides macros for print, try-catch, and throw mechanisms that can report error with call site and stack trace information
- `ZjVerifyNumerics.hpp` provides a macro to check Eigen or std variable singularity
- `ZjLogMacroExtensions.hpp` provides macros for assertion and regular, condition-based, and periodic message with built-in log support

- `ZjCsvLog` provides a singleton class that can create as many files as needed and log Eigen vectors with time stamp to a given file in a thread-safe fashion
- `ZjProgramSwitch` provides a singleton class that can be used as a global program switch and run user-specified functions when it turns off
- `ZjTimer` provides a timer class that can be used to guard a periodic loop of a certain frequency
- `ZjUtility.hpp` provides some functions for map access and pointer clean up

- `[./examples/sigint-sigsegv-handling/]` shows how to handle a Ctrl-C or a Segmentation Fault terminated program
- `[./examples/compile-definitions/]` shows the usage of some compile definitions provided by the [zj-cmake](https://github.com/zongyaojin/zj-cmake/tree/main) submodule
