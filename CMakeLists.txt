cmake_minimum_required(VERSION 3.17)
project(algo-labs)

set(CMAKE_CXX_STANDARD 20)

file(GLOB FILES term3/3/src/*.cpp)

foreach (FILE ${FILES})
    get_filename_component(TARGET ${FILE} NAME_WE)
    add_executable(${TARGET} ${FILE})
endforeach ()

add_compile_definitions(LOCAL)
