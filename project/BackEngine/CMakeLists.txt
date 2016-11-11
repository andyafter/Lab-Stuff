cmake_minimum_required (VERSION 2.8)

# Project Information
project(BackEngine)

find_package (Threads)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(INCLUDE "include")
set(EXTERNAL "external")

#set(HEADERS ./include/project)
#set(DIR_SRCS ./src/)
include_directories(./include/project)

aux_source_directory(./src DIR_SRCS)
aux_source_directory(./include/project HEADERS)


add_executable(Demo
  ${DIR_SRCS}
  )

