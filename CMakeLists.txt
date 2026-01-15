cmake_minimum_required(VERSION 3.10)
project(Snake3D C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 1. Set C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# 2. Find Packages (Required for 3D)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

# 3. Include Directories
include_directories(
    core
    input
    dependencies
    geometry
    render
    resources
    scene
    ${GLFW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)

# 4. Collect Source Files
set(SOURCES
    app/main.c
    core/window.c
    core/geometry_calculation.c
    core/logger.c
    input/input.c
    dependencies/glad.c
    geometry/models.c
    geometry/primitives.c
    render/render.c
    resources/textures.c
    resources/shaders.c
    scene/camera.c
)

# 5. Create Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 6. Link Libraries
target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    assimp::assimp
    m # Link math library for geometry_calculation.c
)

# This copies your shaders/models to the build folder so the app can find them
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
