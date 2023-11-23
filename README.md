# ZJ C++ Base

[![C++ Build](https://github.com/zongyaojin/zj-base/actions/workflows/cpp-build.yml/badge.svg)](https://github.com/zongyaojin/zj-base/actions/workflows/cpp-build.yml)
[![GitHub license](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](https://github.com/zongyaojin/zj-base/blob/main/LICENSE)

This package provides some fundamental utilities for C++ client projects, including functionalities such as logging, debugging, stack tracing, and timing. The package mostly follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). But there are a few exceptions:

- headers use the `#pragma once` include guard;
- regular header and source files use the `.hpp` and `.cpp` extensions;
- some global functions start with an underscore, such as `_ZjMessage()`, indicating that they are not intended for client code to use;
- Macro functions start with an underscore, such as `_ZJ_TRY()`
- Macro variables defined within the package do not have leading or trailing underscores, such as `ZJ_PURPLE`;
- Macro variables defined through CMake follow the two underscores pattern, such as `__FOO_BAR__`;
- filenames follow the `foo-bar.xyz` pattern to make their style consistent with packages such as [zj-cmake](https://github.com/zongyaojin/zj-cmake/tree/main) and [zj-common-scripts](https://github.com/zongyaojin/zj-common-scripts).

This package is only tested on Ubuntu 22.04 with compiler options set to C++23 and C17.
