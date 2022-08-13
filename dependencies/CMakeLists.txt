# Fetch Jupiter Engine from the remote repository
include(FetchContent)

FetchContent_Declare(
    jupiter-engine
    GIT_REPOSITORY  https://github.com/ntemplon/jupiter-engine.git
    GIT_TAG         latest-release
    )

add_subdirectory(jupiter-engine)