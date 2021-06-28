cmake_minimum_required(VERSION 3.16)

project(d_graph)

option(WARN_ERROR "Turn all warnings into errors" OFF)

set(CMAKE_C_STANDARD 11)


if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()

if (WARN_ERROR)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(examples)

set(d_graph_src 
    libfdr/dllist.c 
    libfdr/jrb.c 
    libfdr/jval.c 
    d_graph_constructors.c
    d_graph_interface.c
    d_graph_DAG_topo.c
    d_graph_visitor_paths.c)


if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
  set(d_graph_src ${d_graph_src} libfdr/fields.c)
  message(STATUS "${CMAKE_SYSTEM_NAME} is detected and fields.c is added.")
else (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
  message(STATUS "${CMAKE_SYSTEM_NAME} is detected, you can use fields.c only in Linux")
endif (${CMAKE_SYSTEM_NAME} STREQUAL Linux)


add_library(d_graph STATIC ${d_graph_src})
target_compile_options(d_graph PRIVATE -w)

set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr")

set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/LeVDuan/d_graph")

file (READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION D_GRAPH_VERSION)

# Set a Package Version
set(CPACK_PACKAGE_VERSION ${D_GRAPH_VERSION})