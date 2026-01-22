cmake_minimum_required(VERSION 3.10)
project(Snake3D C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 1. Set C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()


#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#   add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
#    add_link_options(-fsanitize=address)
#endif()

# 2. Find Packages (Required for 3D)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

# 3. Include Directories
include_directories(
    scene/
    core/
    dependencies/
    loaders/
    geometry/
    input/
    render/
    ${GLFW_INCLUDE_DIRSW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)

# 4. Collect Source Files
set(SOURCES
  app/main.c
  scene/camera.c
  core/mvp.c
  core/logger.c
  core/window.c
  dependencies/glad.c
  loaders/shaders.c
  loaders/textures.c
  loaders/terrain.c
  geometry/mesh.c
  geometry/primitives.c
  dependencies/stb.c
  input/input.c
  render/render.c
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
