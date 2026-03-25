cmake_minimum_required(VERSION 4.1)
project(minimum_c C)

set(CMAKE_C_STANDARD 17)

file(GLOB experiment_sources "*.c")

foreach(source_file ${experiment_sources})
    get_filename_component(executable_name ${source_file} NAME_WE)
    if(NOT executable_name STREQUAL "var_declaration_vs_definition" AND NOT executable_name STREQUAL "external_definition")
        add_executable(${executable_name} ${source_file})
        target_include_directories(${executable_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    endif()
endforeach()
