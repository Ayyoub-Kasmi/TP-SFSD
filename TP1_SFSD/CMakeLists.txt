cmake_minimum_required(VERSION 3.23)
project(TP1_SFSD C)

set(CMAKE_C_STANDARD 99)

add_executable(TP1_SFSD main.c tovcFunctions.h tovcFunctions.c DataManipulation.c DataManipulation.h LnOF-library.c LnOF-library.h student-library.c student-library.h)
