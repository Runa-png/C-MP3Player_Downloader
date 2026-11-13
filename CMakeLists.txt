
cmake_minimum_required(VERSION 3.20)

project(Mp3Player LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Collect source files, excluding the build directory
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/functions/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/colors/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/widgets/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/functions/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/colors/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/widgets/*.h"
)

add_executable(app
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app PRIVATE
    Qt6::Widgets
)

target_compile_options(app PRIVATE
    -Wall
    -Wextra
)
