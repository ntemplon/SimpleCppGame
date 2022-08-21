# Fetch Jupiter Engine from the remote repository
include(FetchContent)

FetchContent_Declare(
    jupiter-engine
    GIT_REPOSITORY https://github.com/ntemplon/jupiter-engine.git
    GIT_TAG c08f9f30377e58568833f3deee96c26962634cd2
)

add_subdirectory(jupiter-engine)