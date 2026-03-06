cmake_minimum_required(VERSION 3.14)
project(Sample-SFML-Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# SFML
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/SFML ${CMAKE_BINARY_DIR}/_deps/SFML-build SYSTEM)

# imgui
file(GLOB imgui-src
  ${CMAKE_SOURCE_DIR}/thirdparty/imgui/*.cpp
  ${CMAKE_SOURCE_DIR}/thirdparty/imgui/misc/cpp/*.cpp
)
add_library(imgui ${imgui-src})
target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/thirdparty/imgui)

# imgui-sfml
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(IMGUI_SFML_IMGUI_DEMO OFF CACHE BOOL "" FORCE)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)
set(IMGUI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/imgui-sfml ${CMAKE_BINARY_DIR}/_deps/imgui-sfml-build SYSTEM)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include/)
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra>
)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio ImGui-SFML::ImGui-SFML)

# Disable the console on a Windows release build
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>)
endif()
