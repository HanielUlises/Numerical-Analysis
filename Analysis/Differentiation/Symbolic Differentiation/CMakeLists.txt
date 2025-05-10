cmake_minimum_required(VERSION 3.10)

project(SymbolicDifferentiation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    symbolic_diff.cpp
    main.cpp
)

set(HEADERS
    symbolic_diff.h
)

add_executable(symbolic_diff ${SOURCES} ${HEADERS})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|MSVC")
    target_compile_options(symbolic_diff PRIVATE -Wall -Wextra -pedantic)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)