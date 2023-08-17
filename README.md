# ZJ C++ Tools

<!-- https://docs.github.com/en/actions/monitoring-and-troubleshooting-workflows/adding-a-workflow-status-badge -->
[![Build status](https://github.com/zongyaojin/zj-base/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/zongyaojin/zj-base/actions/workflows/c-cpp.yml)
[![GitHub license](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://github.com/zongyaojin/zj-base/blob/main/LICENSE)

This package contains some handy tools such as logging and debugging for C++ projects.

- `ZjChrono` provides some time-related functions, definitions, and aliases
- `ZjSingleton` provides a singleton base class using the Curiously Recurring Template Pattern

- `ZjDebug.hpp` provides macros for abort, try, catch, and throw mechanisms that can report error with the call site/stack information
- `ZjVerifyNumerics.hpp` provides a macro to check Eigen or std variable singularity
- `ZjLogMacroExtensions.hpp` provides macros for assertion and regular, condition-based, and periodic message with built-in log support

- `ZjCsvLog` provides a singleton class that can create as many files as needed and log Eigen vectors with time stamp to a given file in a thread-safe fashion
- `ZjProgramSwitch` provides a singleton class that can be used as a global program switch and run user-specified functions when it turns off
- `ZjTimer` provides a timer class that can be used to guard a periodic loop of a certain frequency
- `ZjUtility.hpp` provides some functions for map access and pointer clean up

- `[./examples/sigint-sigsegv-handling/]` shows how to handle a Ctrl-C or a Segmentation Fault terminated program
- `[./examples/compile-definitions/]` shows the usage of some compile definitions provided by the [zj-cmake](https://github.com/zongyaojin/zj-cmake/tree/main) submodule

---

See also:

- [Version history](./version-history.md)
- [Create and push tags](https://stackoverflow.com/a/18223354)
- [Delete and push tags](https://stackoverflow.com/a/5480292)
