[![ubuntu](https://github.com/shekeraoleksandr/SreamlineX/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/shekeraoleksandr/SreamlineX/actions/workflows/ubuntu.yml)
 
# StreamlineX
*StreamlineX* - is a project consisting of several mini-projects.

The four modules have been completed at the moment:

* `[x]` Serialization
* `[x]` Deserialization
* `[x]` Networking module
* `[x]` Event System (glfw lib)

## Serialization and deserialization
I wanted to try to create my custom serialization and deserialization, so I did it through byte-wise decomposition of the basic data types. 

## Networking module
Simple UDP server and client implemented using Linux sockets.

## Event System
I'm using Conan to install glfw lib in the root *CMakeList* file.

Event System monitors the position of the mouse on the created windows, keyboard, and mouse keystrokes, simultaneously outputting the changes to the console. 

## Conan and CMake
I'm using *Conan version 1.60.0*. 
For better CMake and Conan usage, I included the `conan.cmake` file from: https://github.com/conan-io/cmake-conan 


Typically we get two errors:

### Package manager mode install
```bash
xorg/system: ERROR: while executing system_requirements(): 
System requirements: 'libx11-xcb-dev, ...' are missing but can't install because tools.system.package_manager:mode is 'check'.
Please update packages manually or set 'tools.system.package_manager:mode' to 'install' in the [conf] section of the profile, 
or in the command line using '-c tools.system.package_manager:mode=install'
```
### Xcb plugin not found
```bash
qt.qpa.xcb: could not connect to display
qt.qpa.plugin: Could not load the Qt platform plugin "xcb" in "" even though it was found.
This application failed to start because no Qt platform plugin could be initialized. Reinstalling the application may fix this problem.
```

To solve them we define custom profile with *"tools.system.package_manager:mode=install"* configuration and *qt:shared=True* option. 


```cmake
conan_cmake_profile(FILEPATH    "${CMAKE_BINARY_DIR}/profile"
                    SETTINGS    os=Linux
                                os_build=Linux
                                arch=x86_64
                                arch_build=x86_64
                                compiler=gcc
                                compiler.version=9
                                compiler.libcxx=libstdc++11
                                build_type=Release
                    OPTIONS     qt:shared=True
                    CONF        "tools.system.package_manager:mode=install"
                                "tools.system.package_manager:sudo=True")    
```

To use this profile over default I added `PROFILE profile` to the root *CMakeLists.txt*:

```cmake
conan_cmake_run(REQUIRES
        ...
        PROFILE profile)
```

# Building

First, we clone the GitHub repository:

```bash
git clone https://github.com/shekeraoleksandr/StreamlineX.git
```

Then create a build folder inside of the repository's folder and navigate into it:

```bash
cd StreamlineX && mkdir build && cd build
```

Once we've created the build directory, we can run Conan and CMake in one step:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

In this case, we have configured our build system to compile debug versions of the binaries. Now we can build with the following command:

```bash
cmake --build .
```

