# Required for Python virtual environment hint
cmake_minimum_required(VERSION 3.15.0)

include(${CMAKE_SOURCE_DIR}/cmake/CreatePythonVenv.cmake)

create_python_venv(
    docenv
    PYTHON_VERSION 3.9
    REQUIREMENTS_TXT ${CMAKE_CURRENT_SOURCE_DIR}/venv_reqs.txt
    OUT_PYTHON_EXE PYTHON_EXE
    OUT_BINARY_DIR VENV_BIN_DIR
    ENV_NAME .docenv
)

# Get our dependencies available
find_package(Doxygen REQUIRED) # Included with the Ubuntu 22.04 repo installation
set(SPHINX_EXECUTABLE ${VENV_BIN_DIR}/sphinx-build) # This will be installed off of pip, so we can assume a location

# Get a list of all public header files so that we can generate documentation for them
get_target_property(RUN_ME_PUBLIC_HEADER_DIR RunMe INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE RUN_ME_PUBLIC_HEADERS ${INTERFACE_INCLUDE_DIRECTORIES}/*.hpp) # ${PROJECT_SOURCE_DIR}/include/*.h

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/include/) # Root directory with RECURSIVE = TRUE in the Doxyfile
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${RUN_ME_PUBLIC_HEADERS}
                   DEPENDS ${DOXYFILE_IN}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "Generating Doxygen files")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})


set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_SOURCE_DIR}/out/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

file(GLOB_RECURSE RST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.rst)

# Only regenerate Sphinx when:
# - Doxygen has rerun
# - Our doc files have been updated
# - The Sphinx config has been updated
add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
                   COMMAND ${SPHINX_EXECUTABLE} -b html
                   # Tell Breathe where to find the Doxygen output
                   -Dbreathe_projects.RunMe=${DOXYGEN_OUTPUT_DIR}/xml
                   ${SPHINX_SOURCE} ${SPHINX_BUILD}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS
                   # Other docs files you want to track should go here (or in some variable)
                   ${RST_FILES}
                   ${DOXYGEN_INDEX_FILE}
                   MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
                   COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})
add_dependencies(Sphinx docenv) # ensure environment is built before calling it