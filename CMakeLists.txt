cmake_minimum_required(VERSION 3.20)
project(openclGpuProgramming VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES src/main.cpp)

add_executable(openclGpuProgramming ${SOURCES})

target_include_directories(openclGpuProgramming PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(openclGpuProgramming PRIVATE -Wall -Wextra -Wpedantic)
endif()

find_package(OpenCL REQUIRED)
target_link_libraries(openclGpuProgramming PRIVATE OpenCL::OpenCL)

file(GLOB_RECURSE ALL_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/include/*.h)

find_program(CLANG_FORMAT_EXE NAMES clang-format-19 clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i --style=file ${ALL_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

find_program(CLANG_TIDY_EXE NAMES run-clang-tidy-19 run-clang-tidy)
if(CLANG_TIDY_EXE)
    add_custom_target(tidy
        COMMAND ${CLANG_TIDY_EXE} -p ${CMAKE_BINARY_DIR} -warnings-as-errors=* ${ALL_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

if(CLANG_FORMAT_EXE AND CLANG_TIDY_EXE)
    add_custom_target(lint DEPENDS format tidy)
endif()

