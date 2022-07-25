cmake_minimum_required(VERSION 3.22.0)

project(Tester VERSION 0.1.0)
add_subdirectory(src)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/res)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
find_package(SFML 2.5 MODULE COMPONENTS system window graphics network audio REQUIRED)

# This defines a build target called "Application" that makes an executable out of main.cpp
add_executable(RunMe 
    src/main.cpp
    src/game.cpp
    )
target_link_libraries(RunMe PUBLIC ${SFML_LIBRARIES})