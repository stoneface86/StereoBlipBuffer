cmake_minimum_required(VERSION 3.8)

project(StereoBlipBuffer CXX)

# remove default warning flags for msvc
if (MSVC)
    string(REGEX REPLACE "/W[3|4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif ()

# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(WARNFLAGS /W4)
endif ()

add_library(stereoblipbuffer STATIC "Blip_Buffer.cpp")
target_include_directories(stereoblipbuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(stereoblipbuffer PRIVATE ${WARNFLAGS})
