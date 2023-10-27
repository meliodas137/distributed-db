cmake_minimum_required(VERSION 3.11)

if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()

project(DistributedDB)

if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else ()
  set (CMAKE_CXX_STANDARD 11)
endif ()

add_subdirectory(src)

add_subdirectory(apps)
