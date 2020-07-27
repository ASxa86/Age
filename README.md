# AGE

## Overview

Aaron's (Another) Game Engine is a general game engine for building 2D and maybe 3D software games, simulations, and applications.

## Quick Start

Prerequisites:

* Windows 10, Linux
* Visual Studio 2019 (on Windows)
* Git
* gcc >= 9 or equivalent clang (on Linux)
* CMake >= 3.15

Dependencies:

* boost 1.7+
* SFML 2.5+
* GTest 1.8+
* Celero

To get started:

Download and build dependencies using [vcpkg](github.com/microsoft/vcpkg)

```
> git clone https://github.com/ASxa86/age.git
> cd age
> mkdir build && cd build
> cmake ../ -DCMAKE_TOOLCHAIN_FILE=<vcpkg-path>/scripts/buildsystems/vcpkg.cmake
> make -j8
```

## License

Code licensed under the [MIT License](https://github.com/ASxa86/AGE/blob/master/LICENSE.txt)
