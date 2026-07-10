cmake_minimum_required(VERSION 3.16)
project(bit_chess VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to an optimized-with-symbols build with warnings when none is chosen.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type" FORCE)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Keep an in-source build from clobbering hand-written files.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are not allowed. Run:\n"
        "  cmake -B build && cmake --build build")
endif()

# ---------------------------------------------------------------------------
# Dependencies
#   glad, glm, and stb_image are vendored in lib/.
#   GLFW is used from the system if installed, otherwise fetched and built.
# ---------------------------------------------------------------------------
set(LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib")

find_package(OpenGL REQUIRED)

find_package(glfw3 3.3 QUIET)
if(NOT glfw3_FOUND)
    message(STATUS "System GLFW not found -- fetching and building it from source")
    include(FetchContent)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(glfw)
endif()

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------
file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB GLAD_SRC_FILES CONFIGURE_DEPENDS "${LIB}/glad/src/*.c")

add_executable(bit_chess ${SRC_FILES} ${GLAD_SRC_FILES})

target_include_directories(bit_chess PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${LIB}/glad/include"
    "${LIB}/glm"
    "${LIB}/stb_image"
)

target_link_libraries(bit_chess PRIVATE glfw OpenGL::GL)

# Convenience: `cmake --build build --target run`
add_custom_target(run
    COMMAND bit_chess
    DEPENDS bit_chess
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    USES_TERMINAL
)
