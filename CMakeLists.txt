# Experimenting with PackageName_ROOT to help direct to a sphinx installation in the virtual environment,
#  which requires 3.12
cmake_minimum_required(VERSION 3.12.0)

# Set Project Name and Version
project(SimpleCppGame VERSION 0.1.0)

# Make sure we get our dependencies
add_subdirectory(dependencies)

# Find all resource files in res so that we can copy them to build next to the executable
set(SOURCE_RESOURCE_DIR ${CMAKE_SOURCE_DIR}/res/)
file(GLOB_RECURSE RESOURCE_FILES ${SOURCE_RESOURCE_DIR}/*.*)

# Make a dependency between each file in build and it's origin in ./res
set(TARGET_RESOURCE_DIR ${CMAKE_BINARY_DIR}/res/)
foreach(RESOURCE_FILE ${RESOURCE_FILES})
    file(RELATIVE_PATH REL_PATH ${SOURCE_RESOURCE_DIR} ${RESOURCE_FILE})
    set(TARGET_FILE ${TARGET_RESOURCE_DIR}${REL_PATH})
    configure_file(${RESOURCE_FILE} ${TARGET_FILE} COPYONLY)
endforeach()

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# This defines a build target called "simple-cpp-game" that makes an executable out of these source files
add_executable(simple-cpp-game ${SRC_FILES})
# Specify that the simple-cpp-game target will use C++14
set_property(TARGET simple-cpp-game
             PROPERTY C_STANDARD 14
)
set_property(TARGET simple-cpp-game
    PROPERTY CXX_STANDARD 14
)

# Put the Find*.cmake files at ./cmake onto the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Add the ./include and ./res directories to the build path so header files and images are available
target_include_directories(simple-cpp-game PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(simple-cpp-game PUBLIC ${PROJECT_SOURCE_DIR}/include/entity/)

target_link_libraries(simple-cpp-game PRIVATE libjupiter-engine)

# Add the subdirectories. I have learned the hardway that if you do not DO THIS LAST, lots of dependencies will
#  break, hilarity will ensue, and you will forget to do your laundry while trying to fix them.
add_subdirectory(src)
add_subdirectory(docs)