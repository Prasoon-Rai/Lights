cmake_minimum_required(VERSION 3.16)
project(LearnRaylib LANGUAGES C CXX)

# Use a modern C++ standard supported by raylib examples
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Try to use an existing raylib installation first (e.g., Homebrew on macOS)
# If not found, fall back to fetching raylib from GitHub.
include(FetchContent)
set(RAYLIB_VERSION "5.0")

find_package(raylib CONFIG QUIET)

if(NOT raylib_FOUND)
    message(STATUS "raylib not found on system. Fetching raylib ${RAYLIB_VERSION}...")
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG ${RAYLIB_VERSION}
    )
    # Build raylib without examples/tests/tools to speed up
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

add_executable(LearnRaylib main.cpp
        raylights.h++
        LightPoint.h++)

# Link against raylib target
# The imported/added target is named "raylib" in both find_package and FetchContent cases
# On Apple platforms, raylib's target already links required frameworks.
# On Linux, extra system libs are handled by raylib as interface deps.
target_link_libraries(LearnRaylib PRIVATE raylib)

# On Windows, ensure WinMain is used properly when building a GUI app (optional)
if(WIN32)
    # set_property(TARGET LearnRaylib PROPERTY WIN32_EXECUTABLE TRUE)
endif()
