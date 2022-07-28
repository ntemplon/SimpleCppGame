# This script is based on the script provided under the WTFPL here:
#       https://schemingdeveloper.com/2020/07/02/how-to-create-a-new-python-virtual-environment-in-cmake/
#
# create_python_venv
#
# Function that creates a python virtual environment with the specified parameters.
#
# Required Arguments:
#   TARGET:             (string)        Name of the build target that creates the virtual environment.
#
# Optional Arguments:
#   REQUIREMENTS_TXT:   (string list)   Path to requirements.txt list to install with pip. Can be relative to ${CMAKE_BINARY_DIR}
#                                       or absolute.
#   PREFIX:             (string)        Path to the root directory in which the environment will be placed. Can be relative
#                                       ${CMAKE_BINARY_DIR} or absolute. 
#   ENV_NAME:           (string)        The name of the virtual environment. If not specified, is set to TARGET.
#   PYTHON_VERSION:     (string)        The version of python to construct the virtual environment. If omitted, the system default
#                                       python installation, regardless of version, will be used.
#   SOURCES:            (string list)   Any sources on which the virtual environment is dependent.
#   REQUIREMENTS:       (string list)   Any additional requirements to install with pip that aren't part of requirements.txt (e.g.
#                                       local packages)
#
# Optional Output Arguments:
#   OUT_PYTHON_EXE:     (out string)    Stores the path to the python executable of the virtual environment.
#   OUT_BINARY_DIR:     (out string)    Stores the directory of any scripts / executables that are created as part of the environment,
#                                       such as python[.exe], pip[.exe], activate, etc.
#   OUT_VENV_DIR:       (out string)    Stores the root path of the virtual environment.
#
# Usage:
#
#

function(create_python_venv TARGET)
    # Declare keyword arguments
    set(KEYWORD_ARGS
        REQUIREMENTS_TXT
        PREFIX
        ENV_NAME
        OUT_PYTHON_EXE
        OUT_BINARY_DIR
        OUT_VENV_DIR
        PYTHON_VERSION
        )

    # Declare multivariable arguments
    set(MULTI_ARGS
        SOURCES
        REQUIREMENTS)

    # Parse the arguments into variables, with the prefix ARG in front of each of them.
    cmake_parse_arguments(ARG "" "${KEYWORD_ARGS}" "${MULTI_ARGS}" ${ARGN})

    # If an environment name argument wasn't provided, assume the target name is the environment name.
    if (NOT ARG_ENV_NAME)
        set(ARG_ENV_NAME ${TARGET})
    endif ()

    # This sets Python_EXECUTABLE to the path to the interpretor we want
    if (ARG_PYTHON_VERSION)
        # We need a specific python version
        find_package(Python
            "${ARG_PYTHON_VERSION}" EXACT
            REQUIRED COMPONENTS Interpreter
            )
    else ()
        # Use whatever we find
        find_package(Python REQUIRED COMPONENTS Interpreter)
    endif ()

    # Set the variable VENV to contain the path to where we will create the virtual environment.
    if (ARG_PREFIX)
        if (IS_ABSOLUTE ${ARG_PREFIX})
            # Case: Prefix is provided an it's absolute
            set(VENV ${ARG_PREFIX}/${ARG_ENV_NAME})
        else ()
            # Case: Prefix is provided an it's relative
            set(VENV ${CMAKE_BINARY_DIR}/${ARG_PREFIX}/${ARG_ENV_NAME})
        endif ()
    else ()
        # Case: Prefix is not provided
        set(VENV ${CMAKE_BINARY_DIR}/${ARG_ENV_NAME})
    endif ()

    # Set variables pointint to the binary folders and python executable, with cases for Windows
    #   and POSIX
    if (WIN32)
        set(BIN_DIR ${VENV}/Scripts)
        set(PYTHON ${BIN_DIR}/python.exe)
    else ()
        set(BIN_DIR ${VENV}/bin)
        set(PYTHON ${BIN_DIR}/python)
    endif ()

    # Is this unnecesssary?
    #   I think so - it's overwritten in the if (REQUIREMENTS) block in both branches before it's used again
    #set(INSTALL_CMD ${BIN_DIR}/pip install --disable-pip-version-check)

    # If a requirements.txt file is specified, build the environment with it
    if (ARG_REQUIREMENTS_TXT)
        if (IS_ABSOLUTE ${ARG_REQUIREMENTS_TXT})
            # Case: Absolute requirements.txt path provided already
            set(REQ_TEXT_PATH ${ARG_REQUIREMENTS_TXT})
        else ()
            # Case: Relative requirements.txt path provided, so resolve it
            set(REQ_TEXT_PATH ${CMAKE_BINARY_DIR}/${ARG_REQUIREMENTS_TXT})
        endif()

        # Set the bit of text we're going to pass to pip later to install the requirements
        set(REQUIREMENTS -r ${REQ_TEXT_PATH})
    endif()

    # Build the requirements lsit
    set(REQUIREMENTS ${REQUIREMENTS} "${ARG_REQUIREMENTS}")

    if (REQUIREMENTS)
        # Build the installation command
        set(INSTALL_CMD ${BIN_DIR}/pip install --disable-pip-version-check)
        set(INSTALL_CMD ${INSTALL_CMD} ${REQUIREMENTS})
    else()
        # If there are no requirements, there is no installation command
        set(INSTALL_CMD "")
    endif()

    # Point at the configuration file that will be created for our new virtual environment
    set(CFG_FILE ${VENV}/pyvenv.cfg)

    # Creates the virtual environment and puts the output into the config file
    add_custom_command(
            OUTPUT ${CFG_FILE}
            COMMAND ${Python_EXECUTABLE} -m venv ${VENV}
    )

    # Add a command to install the dependencies and put the result in the OUTPUT_FILE
    #  Depends on the output file that is updated by the pip freeze command so this will re-run on next build
    #  if the process is interrupted mid-installation
    # Other dependencies ensure the command is re-run if the venv is recreated, new sources are added as arguments,
    #  or the requirements.txt file is updated.
    set(OUTPUT_FILE ${VENV}/environment.txt)
    add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${INSTALL_CMD}
            COMMAND ${BIN_DIR}/pip freeze > ${OUTPUT_FILE}
            DEPENDS ${CFG_FILE} ${ARG_SOURCES} ${ARG_REQUIREMENTS_TXT}
    )

    # Create our target that will build the environment when run
    add_custom_target(${TARGET} DEPENDS ${OUTPUT_FILE})

    # Output the output args
    if (ARG_OUT_VENV_DIR)
        set(${ARG_OUT_VENV_DIR} ${VENV} PARENT_SCOPE)
    endif ()

    if (ARG_OUT_PYTHON_EXE)
        set(${ARG_OUT_PYTHON_EXE} ${PYTHON} PARENT_SCOPE)
    endif ()

    if (ARG_OUT_BINARY_DIR)
        set(${ARG_OUT_BINARY_DIR} ${BIN_DIR} PARENT_SCOPE)
    endif ()

endfunction() # End of function create_python_venv