cmake_minimum_required(VERSION 3.25)
project(Editor_Hexadecimal
LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Editor
    # headers
    src/udf.h

    #sources
    src/main.c
    src/udf.c
)

if(MSVC)
    target_compile_definitions(Editor PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()
