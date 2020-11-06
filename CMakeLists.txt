cmake_minimum_required(VERSION 3.17)
project(dm-labs)

set(CMAKE_CXX_STANDARD 17)

set(LAB y2020-1-2)

file(GLOB FILES src/${LAB}/**.cpp)

foreach (FILE ${FILES})
    get_filename_component(TARGET ${FILE} NAME_WE)
    add_executable(${TARGET} ${FILE})
endforeach ()