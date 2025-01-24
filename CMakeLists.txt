cmake_minimum_required(VERSION 3.10)
project(RaySpy)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify source files
set(SOURCES
    ./src/main.cpp
    ./src/glad.c
    ./src/common/shader.cpp
)

# Specify include directories
set(INCLUDE_DIRS

    include
    common
    /opt/homebrew/Cellar/glm/1.0.1/include
    src
)

# Add source files to the project
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories to the compiler
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# Find and link GLFW
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW OpenGL::GL)

# Find and link GLM (header-only, no linking needed)
find_path(GLM_INCLUDE_DIR glm/glm.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIR})
include_directories(/opt/homebrew/Cellar/glm/1.0.1/include)

