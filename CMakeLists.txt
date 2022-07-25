cmake_minimum_required(VERSION 3.0.0)

# Set Project Name and Version
project(SimpleCppGame VERSION 0.1.0)

# This defines a build target called "Application" that makes an executable out of these source files
add_executable(RunMe 
    src/main.cpp
    src/game.cpp
    src/screen.cpp
    )
# Specify that the RunMe target will use C++11
set_property(TARGET RunMe PROPERTY C_STANDARD 11)

# Put the Find*.cmake files at ./cmake onto the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Add the ./include and ./res directories to the build path so header files and images are available
target_include_directories(RunMe PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(RunMe PRIVATE ${PROJECT_SOURCE_DIR}/res)

# Load SFML. MODULE is used to force usage of the FindSFML.cmake file over the .config file that comes
#  with the SFML installation from the Ubuntu 22.04 repositories.
find_package(SFML 2.5 MODULE COMPONENTS system window graphics network audio REQUIRED)

#Specify that what is found by the SFML find above should be linked to the RunMe target as a public dependency
target_link_libraries(RunMe PUBLIC ${SFML_LIBRARIES})

# Add the subdirectories. I have learned the hardway that if you do not DO THIS LAST, lots of dependencies will
#  break, hilarity will ensue, and you will forget to do your laundry while trying to fix them.
add_subdirectory(src)
add_subdirectory (docs)