cmake_minimum_required(VERSION 2.8)
project(confighandler)

set(BUILD_SHARED_LIBS FALSE)

FIND_LIBRARY(LIBCONFIGPP_LIBRARY config++
        /usr/local/lib
        /usr/lib
        )

add_library(confighandler confighandler.cpp confighandler.h)

target_link_libraries(confighandler ${LIBCONFIGPP_LIBRARY})
