cmake_minimum_required(VERSION 3.10)

project(package_dsl VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB DSL_SOURCE "src/*.cpp")
file(GLOB DSL_HEADER "include/*.h")

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/spdlog")

configure_file(test.pdsl test.pdsl)

add_executable(package_dsl "${DSL_HEADER}" "${DSL_SOURCE}")

set_target_properties(package_dsl PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(package_dsl spdlog_header_only)

target_include_directories(package_dsl PUBLIC "${PROJECT_SOURCE_DIR}/include")
