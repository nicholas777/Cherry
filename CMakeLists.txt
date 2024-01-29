
cmake_minimum_required(VERSION 3.10)

project(Cherry VERSION 0.1)

set(BUILD_EXAMPLE OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dear ImGui doesn't have a cmake build file so we build it ourselves
file(GLOB IMGUI_SOURCES cherry/vendor/imgui/*.cpp 
    cherry/vendor/imgui/backends/imgui_impl_glfw.cpp
    cherry/vendor/imgui/backends/imgui_impl_opengl3.cpp)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
add_library(imgui ${IMGUI_SOURCES})

# Same with glad
add_library(glad cherry/vendor/glad/src/glad.c)
include_directories(cherry/vendor/glad/include)

add_library(osdialog cherry/vendor/osdialog/osdialog.c cherry/vendor/osdialog/osdialog_zenity.c)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

file(GLOB CH_SOURCES cherry/src/core/**.cpp cherry/src/events/**.cpp
    cherry/src/graphics/**.cpp cherry/src/imgui/**.cpp cherry/src/math/**.cpp
    cherry/src/renderer/**.cpp cherry/src/scene/**.cpp cherry/src/system/**.cpp
    cherry/src/utils/**.cpp cherry/src/scripting/**.cpp cherry/src/debug/**.cpp)

set(CH_STB_IMAGE cherry/vendor/stb_image/stb_image.cpp)

if (WIN32)
    file(GLOB CH_PLATFORM_SOURCES cherry/src/platform/windows/**.cpp)
elseif(LINUX)
    file(GLOB CH_PLATFORM_SOURCES cherry/src/platform/linux/**.cpp)
else()
    message(FATAL_ERROR "Platform not supported")
endif()

set(GRAPHICS_API_OPENGL ON)
if (GRAPHICS_API_OPENGL)
    file(GLOB CH_GRAPHICS_SOURCES cherry/src/platform/openGL/*.cpp)
endif()

add_library(cherry ${CH_SOURCES} ${CH_GRAPHICS_SOURCES} ${CH_PLATFORM_SOURCES} ${CH_STB_IMAGE})
include_directories(cherry/src cherry/vendor/stb_image)

target_precompile_headers(cherry PRIVATE cherry/src/epch.h)

if (WIN32)
    add_compile_definitions(CH_PLATFORM_WINDOWS)
elseif(LINUX)
    add_compile_definitions(CH_PLATFORM_LINUX)
endif()

# TODO: Allow user to specify this through cmd line
add_compile_definitions(CH_DEBUG_MODE)

set(freetype-gl_WITH_GLAD ON CACHE BOOL "Enable glad")
set(freetype-gl_WITH_GLEW OFF CACHE BOOL "Enable glew")
set(freetype-gl_BUILD_APIDOC OFF CACHE BOOL "Build doc")
set(freetype-gl_BUILD_DEMOS OFF CACHE BOOL "Build demos")
set(freetype-gl_BUILD_TESTS OFF CACHE BOOL "Build tests")
add_subdirectory(cherry/vendor/freetype_gl)
link_libraries(freetype-gl)
include_directories(cherry/vendor/freetype_gl)
include_directories($<TARGET_PROPERTY:freetype-gl,BINARY_DIR>)

set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "Build yaml-cpp tools")
add_subdirectory(cherry/vendor/yaml_cpp)
link_libraries(yaml-cpp)
include_directories(cherry/vendor/yaml_cpp/include)

include_directories(cherry/vendor/entt/src)

add_subdirectory(cherry/vendor/spdlog)
link_libraries(spdlog)
include_directories(cherry/vendor/spdlog/include)

link_libraries(glad)
include_directories(cherry/vendor/glad/include)

set(GLFW_INSTALL OFF)
add_subdirectory(cherry/vendor/glfw)
link_libraries(glfw)
include_directories(cherry/vendor/glfw/include)

link_libraries(imgui)
include_directories(cherry/vendor/imgui)

add_subdirectory(cherry/vendor/lua-cmake)
target_link_libraries(cherry lua)
include_directories(cherry/vendor/lua)

include_directories(cherry/vendor/osdialog)
target_link_libraries(cherry osdialog)

file(GLOB BLOSSOM_SOURCES blossom/src/*.cpp blossom/src/panels/*.cpp)

add_executable(blossom ${BLOSSOM_SOURCES})
target_include_directories(blossom PRIVATE cherry/src blossom/src)
target_include_directories(blossom PRIVATE blossom/vendor/filewatch)
target_link_libraries(blossom cherry imgui glfw lua)
target_compile_options(blossom PRIVATE "-Wno-unknown-pragmas")

if(BUILD_EXAMPLE)
    add_executable(example tests/src/hello.cpp) 
    include_directories(cherry/src)
    link_libraries(cherry)
endif()

