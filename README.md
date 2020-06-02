# ADev

[Builds & Artifacts](https://github.com/Agnesoft/ADev/actions?query=branch%3Amaster)

![Build](https://github.com/Agnesoft/ADev/workflows/ADev/badge.svg)

Central development repository providing shared cross platform infrastructure to projects.

## Build

All build actions are done using **build.sh** script. Bash scripts are native on Linux and macOS, on Windows use **Git Bash**. When run without any commands it prints extensive readme with all avaiable actions, requirements and used environment variables for each action. It also auto-detects the prerequisites for each action. If any prerequisites for a given action are missing it offers a platform independent installation action (./build.sh install-xxx). This requires you to have a package manager though:

* [Chocolatey](https://chocolatey.org/) on Windows
* [apt](https://en.wikipedia.org/wiki/APT_(software)) on Linux
* [Homebrew](https://brew.sh/index_cs) on macOS

For simply building all of ADev you will require CMake generator, Ninja build system and a C++ toolchain, then run:

`./build.sh build`

## Projects

* [ABenchmarks](projects/ABenchmarks/README.md) Collection of benchmarks from other projects.
* [ABuild](projects/ABuild/README.md) C++ automatic build system.
* [ACore](projects/ACore/README.md) C++ basic containers and utilities.

## Third Party Projects
* [Catch2](https://github.com/catchorg/Catch2) C++ a multi-paradigm test framework.
* [tiny-process-library](https://gitlab.com/eidheim/tiny-process-library) C++ platform independent process library.

## Continuous Integration (GitHub Actions)

All of the following are part of the **build.sh** script and can be run locally on your system.

#### Analysis (./build.sh analysis)
Static analysis using [Clang-Tidy](https://clang.llvm.org/extra/clang-tidy/). No warnings are required. Use `//NOLINT` to suprress irrelevant warnings.

#### Coverage (./build.sh coverage)
Test/code coverage using [LLVM Source Code Coverage Tools](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html). 100 % line and 100 % function coverage is required. Region coverage can be any% due to `constexpr` code being handled incorrectly by LLVM Code Coverage Tools. 

*Code coverage report is part of the build artifacts.*

#### Documentation (./build.sh documentation)
HTML documentation generated by [Doxygen](https://www.doxygen.nl/index.html). Full documentation is required. Use `//! \cond IMPLEMENTAION_DETAIL` and `//! \endcond` to remove non-public code from documentation. 

*Documentation is part of the build artifacts.*

#### Formatting (./build.sh formatting)
Code formatting using [Clang-Format](https://clang.llvm.org/docs/ClangFormat.html). Compliant formatting is required. Use `// clang-format off` and `// clang-format on` to selectively suppress the automatic formatting.

#### Sanitize Address (./build.sh sanitize-address)
Builds & run tests with [Clang's Address Sanitizer](https://clang.llvm.org/docs/AddressSanitizer.html). No detected issues are allowed.

#### Sanitize Memory (./build.sh sanitize-memory)
Builds & run tests with [Clang's Memory Sanitizer](https://clang.llvm.org/docs/MemorySanitizer.html). No detected issues are allowed.

#### Sanitize Undefined Behavior (./build.sh sanitize-ub)
Builds & run tests with [Clang's Undefined Behavior Sanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html). No detected issues are allowed.

#### Windows MSVC x64 Build (./build.sh build)
Builds optimized (Release) 64-bit configuration on Windows using Visual Studio (MSVC). Runs tests. Runs benchmarks.

*Binaries are part of the build artifacts.*

#### Linux GCC x64 Build (./build.sh build)
Builds optimized (Release) 64-bit configuration on Linux (Ubuntu) using GCC. Runs tests. Runs benchmarks.

*Binaries are part of the build artifacts.*

#### macOS Clang x64 Build (./build.sh build)
Builds optimized (Release) 64-bit configuration on macOS using Clang. Runs tests. Runs benchmarks.

*Binaries are part of the build artifacts.*

#### Tests & Benchmarks (./build.sh tests, ./build.sh benchmarks)
For each build configuration the tests are run 100x times to detect flaky tests. Therefore all tests must run as fast as possible.

For each build configuration the benchmarks are run. Every benchmark has preset requirements and they can fail if the performance of the benchmarked code deteriorates.
