cmake_minimum_required (VERSION 2.8)

# Project Information
project(BackEngine)

find_package (Threads)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(EXTERNAL "external")

include_directories("${EXTERNAL}")
include_directories("${EXTERNAL}/include")
include_directories("${EXTERNAL}/include/project")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(EXTERNAL_LIB_PATH "${EXTERNAL}/lib/osx")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(EXTERNAL_LIB_PATH "${EXTERNAL}/lib/linux" "/usr/lib64")
elseif(WIN32)
    set(EXTERNAL_LIB_PATH "${EXTERNAL}/lib/win")
endif()

link_directories(${EXTERNAL_LIB_PATH})

# include gtest
#include_directories(./include/gtest)
#include_directories(./external/include/gtest)

aux_source_directory(./src DIR_SRCS)
aux_source_directory(./external/include/project HEADERS)


add_executable(Demo
  ${DIR_SRCS}
  )

#target_link_libraries(Demo /usr/local/lib/libgtest.a)
#target_link_libraries(Demo ./external/lib/osx/libgtest.a)
