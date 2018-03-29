cmake_minimum_required(VERSION 3.7)
project(orga2_tp1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        string_processor.h
        string_processor.c
        string_processor_asm.o
        main.c)

add_executable(orga2_tp1 ${SOURCE_FILES})