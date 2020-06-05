#change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(Anatar)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)
## In most cases better set in the CMake cache
set(SFML_DIR "../libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Set version information in a config.h file
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "Anatar")
add_executable(${EXECUTABLE_NAME}
 main.cc
 player.cc
 fps.cc 
 animation_component.cc
 animation.cc
 movement_component.cc)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
include(CPack)

target_link_libraries(Anatar sfml-graphics sfml-audio)
