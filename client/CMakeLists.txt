cmake_minimum_required(VERSION 3.15)
project(client)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS system coroutine REQUIRED)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find boost libs")
    return()
else()
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(../confighandler)

add_executable(client main.cpp client.cpp client.h)

target_link_libraries(client ${Boost_LIBRARIES} confighandler)
