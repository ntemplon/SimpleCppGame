Installing and Getting Started
================================

Simple Cpp Game is designed to work on x86 Linux, Mac, and Windows. ARM is not explicitly supported at this time due to lack of available
test hardware for the developer.

Installing Dependencies
-------------------------

The Simple Cpp Game (and associated documentation generation) has the following dependencies:

1. A C++ Compiler
    Any C++ Compiler and CMake. A C++ compiler that supports C++14 and :code:`#pragma once` will suffice. The game was developed and debugged using g++ 
    12.2 (Ubuntu 22.04 default).

    On Ubuntu 22.04: :code:`sudo apt install gcc g++ cmake`

    **Mac** users can install the clang/clang++ compilers and cmake via homebrew: :code:`brew install llvm cmake`

2. SFML Dependencies
    The Simple Cpp Game is built with the Jupiter engine that is dependent on `SFML <https://www.sfml-dev.org/download/sfml/2.5.1/>`_. The CMake
    files will build SFML from source, but SFML's dependencies (xrandr, freetype, and udev) need to be installed manually first.
    
    **Linux** users are recommended to install these dependencies via their distribution's package manager, if possible. For example, in Ubuntu:

    :code:`sudo apt install libxrandr-dev libfreetype-dev libudev-dev mesa-common-dev`

    **Mac** users do not need any additional dependencies to build SFML.
    
    **Windows** users should consult the Oracle of Google for how to best install dependencies.

2. Doxygen (with graphviz)

    **Linux** users should install Doxygen via their distribution's package manager. For example, on Ubuntu:

    :code:`sudo apt install doxygen graphviz`

    **Mac** users should install Doxygen via Homebrew.

    :code:`brew install doxygen graphviz`

    **Windows** users should download and run the `Doxygen installer <https://doxygen.nl/download.html>`_ and
    `graphviz installer <https://graphviz.org/download/>`_.

3. Python3
    Any version of Python 3 will work with Simple Cpp Game. It is used for the environment in which the documentation is built.

    **Linux** users should install a version of Python from their distribution's repositories. Be sure that this includes the virtual
    environment tools as well. For example, to install Python3.10 on Ubuntu:

    :code:`sudo apt install python3.10 python3.10-venv`

    **Mac** users should install python3, pip, and the virtualenv tools. There are many ways to do this, such as with homebrew:

    :code:`brew install python3`

    :code:`pip3 install virtualenv`

    **Windows** users should download and run an installter from `the Python website <https://www.python.org/downloads/>`_. Do NOT
    use the version of Python from the windows store; it is substantially more difficult to work with.


Downloading the Game
---------------------
The code and other resources for the Simple Cpp Game can be found `in the repository <https://github.com/ntemplon/SimpleCppGame>`_.
You can download the repository from the website or by cloning it with :code:`git clone https://github.com/ntemplon/SimpleCppGame`.

Building the Game
------------------
The easiest way to build the game is to open `VSCode <https://code.visualstudio.com/>`_ in the respository directory and invoke the
CMake: Configure and CMake: Built Target simple-cpp-game commands with Ctrl + Shift + P or Cmd + Shift + P on Mac.

To manually build the game, open a terminal in the repository directory and run the following commands. They are provided for Linux;
use whatever equivalent commands are available on your operating system.

1. Make the working directory inside of the repository

.. code-block::
    
    mkdir build;cd ./build

2. Configure the project to prepare to build

.. code-block::

    cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER:FILEPATH=/path/to/c_compiler -DCMAKE_CXX_COMPILER:FILEPATH=/path/to/cxx_compiler -S/path/to/repo/root -B/path/to/repo/root/build -G "Unix Makefiles"

Note: The default location for c compilers and cxx compilers on Ubuntu is /usr/bin

Note: If on windows, use cmake-gui.exe instead and refer to the CMake documentation for assistance.

3. Build the target

.. code-block::
    
    cmake --build . --config Release --target all

This will result in a simple-cpp-game executable in the build folder, which you can run to play the game!