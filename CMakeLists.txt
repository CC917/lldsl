cmake_minimum_required(VERSION 3.10)

project(package_dsl VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB DSL_SOURCE "src/*.cpp")

configure_file(test.pdsl test.pdsl)

add_executable(package_dsl "${DSL_SOURCE}")

target_include_directories(package_dsl PUBLIC "${PROJECT_SOURCE_DIR}/include")
