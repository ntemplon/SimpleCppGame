# SimpleCppGame
A simple game written in C++ that shameless rips of Pong. Simple Cpp Game is designed to work on x86 Linux, Mac, and Windows. ARM is not explicitly supported at this time due to lack of available test hardware for the developer.

Installing and Getting Started
================================

Installing Dependencies
-------------------------

The Simple Cpp Game (and associated documentation generation) has the following dependencies:

1. A C++ Compiler
    Any C++ Compiler that supports C++14 and :code:`#pragma once` will suffice. The game was developed and debugged using g++ 
    12.2 (Ubuntu 22.04 default).

2. SFML
    SFML is provided for Windows, Mac, and Linux [here](https://www.sfml-dev.org/download/sfml/2.5.1/).
    
    **Linux** users are recommended to install SFML via their distribution's package manager, if possible. For example, in Ubuntu:

    `sudo apt install libsfml-dev`

    **Mac** users should install SFML following [these instructions](https://www.sfml-dev.org/tutorials/2.5/start-osx.php).

    **Windows** users (or other users that wish to keep SFML separate) can unzip the appropriate package and direct the game build
    files there by setting the `SFML_ROOT` environment variable to the root SFML directory after unzipping.

2. Doxygen (with graphviz)

    **Linux** users should install Doxygen via their distribution's package manager.

    `sudo [apt/dnf/yum] install doxygen graphviz`

    **Mac** users should install Doxygen via Homebrew.

    `sudo brew install doxygen graphviz`

    **Windows** users should download and run the [Doxygen installer](https://doxygen.nl/download.html) and
    [graphviz installer](https://graphviz.org/download/).

3. Python3
    Any version of Python 3 will work with Simple Cpp Game. It is used for the environment in which the documentation is built.

    **Linux** users should install a version of Python from their distribution's repositories. Be sure that this includes the virtual
    environment tools as well. For example, to install Python3.10 on Ubuntu:

    `sudo apt install python3.10 python3.10-venv`

    **Mac** users can download Python from [the official website](https://www.python.org/downloads/macos/).

    **Windows** users should download and run an installter from [the Python website](https://www.python.org/downloads/). Do NOT
    use the version of Python from the windows store; it is substantially more difficult to work with.


Downloading the Game
---------------------
The code and other resources for the Simple Cpp Game can be found in the repository (here!).
You can download the repository from the website or by cloning it with `git clone https://github.com/ntemplon/SimpleCppGame`.

Building the Game
------------------
The easiest way to build the game is to open [VSCode](https://code.visualstudio.com/) in the respository directory and invoke the
CMake: Configure and CMake: Built Target RunMe commands with Ctrl + Shift + P or equivalent Mac command.

To manually build the game, open a terminal in the repository directory and run the following commands. They are provided for Linux;
use whatever equivalent commands are available on your operating system.

1. Make the working directory inside of the repository

  `mkdir build;cd ./build`

2. Configure the project to prepare to build

    `cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER:FILEPATH=/path/to/c_compiler -DCMAKE_CXX_COMPILER:FILEPATH=/path/to/cxx_compiler -S/path/to/repo/root -B/path/to/repo/root/build -G "Unix Makefiles"`

Note: The default location for c compilers and cxx compilers on Ubuntu is /usr/bin
Note: If on windows, use cmake-gui.exe instead and refer to the CMake documentation for assistance.

3. Build the target

    `cmake --build . --config Release --target all`

This will result in a RunMe executable in the build folder, which you can run to play the game!
