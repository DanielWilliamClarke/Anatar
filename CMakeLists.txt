# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

project(Annatar)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# Get sfml from conan
include(conanbuildinfo.cmake)
conan_basic_setup()

#set(SFML_DIR "lib/SFML-2.5.1/lib/cmake/SFML")
#find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Link gtest - below line found in 
# https://raw.githubusercontent.com/google/googletest/master/googletest/README.md
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()
add_subdirectory (lib/googletest)

# Add src
include_directories(src)
add_subdirectory (src)

# Add tests
add_subdirectory (test)