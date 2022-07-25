# Get our dependencies available
find_package(Doxygen REQUIRED) # Included with the Ubuntu 22.04 repo installation
find_package(Sphinx REQUIRED) # ./cmake/FindSphinx.cmake

# Get a list of all public header files so that we can generate documentation for them
get_target_property(RUN_ME_PUBLIC_HEADER_DIR RunMe INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE RUN_ME_PUBLIC_HEADERS ${RUN_ME_PUBLIC_HEADER_DIR}/*.hpp ${RUN_ME_PUBLIC_HEADER_DIR}/*.h)

set(DOXYGEN_INPUT_DIR ${RUN_ME_PUBLIC_HEADER_DIR}) # PROJECT_SOURCE_DIR
set(DOXYGEN_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/out/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${RUN_ME_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   MAIN_DEPENDENCY ${DOXYFILE_IN}
                   COMMENT "Generating docs")

message(STATUS "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})


set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${PROJECT_SOURCE_DIR}/out/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

# Only regenerate Sphinx when:
# - Doxygen has rerun
# - Our doc files have been updated
# - The Sphinx config has been updated
add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
                   COMMAND ${SPHINX_EXECUTABLE} -b html
                   # Tell Breathe where to find the Doxygen output
                   -Dbreathe_projects.CatCutifier=${DOXYGEN_OUTPUT_DIR}/xml
                   ${SPHINX_SOURCE} ${SPHINX_BUILD}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS
                   # Other docs files you want to track should go here (or in some variable)
                   ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
                   ${DOXYGEN_INDEX_FILE}
                   MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
                   COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})

# Add an install target to install the docs
#include(GNUInstallDirs)
#install(DIRECTORY ${SPHINX_BUILD} DESTINATION ${CMAKE_INSTALL_DOCDIR})