include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

# Set dependency versions
set(SFML_VERSION 2.6.1)
set(IMGUI_VERSION 1.89)

# Install SFML location
FetchContent_Declare(
    SFML
    URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
# Install Imgui location
FetchContent_Declare(
    imgui
    URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
# Install IMGUI_SFML
fetchcontent_declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG 2.6.x
)

# Set SFML options
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Set Dear ImGui options
FetchContent_MakeAvailable(imgui)

# Set ImGui-SFML options
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
FetchContent_MakeAvailable(imgui-sfml)