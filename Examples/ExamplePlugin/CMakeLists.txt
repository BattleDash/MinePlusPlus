cmake_minimum_required(VERSION 3.16.3)
project(ExamplePlugin)

# Linux Compiler Flags
if(NOT WIN32)
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)
endif(NOT WIN32)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
        ${PROJECT_SOURCE_DIR}/Source/Public
)
include_directories(SYSTEM INTERFACE
        ${PROJECT_SOURCE_DIR}/../../Source/Public
)

# I know globbing files is discouraged, but with the addition of CONFIGURE_DEPENDS many of the issues are negated and I much prefer this approach to manually listing every source file.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/Source/Private/*.cpp
)

add_library(ExamplePlugin MODULE ${SOURCES})

target_link_libraries(ExamplePlugin ${PROJECT_SOURCE_DIR}/MinePlusPlus.lib)

if(WIN32)
    target_compile_definitions(ExamplePlugin PRIVATE MPP_PLATFORM_WINDOWS)
else()
    target_compile_definitions(ExamplePlugin PRIVATE MPP_PLATFORM_LINUX)
endif()