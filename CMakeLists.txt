project(testMHD)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR})
find_package(MHD REQUIRED)

include_directories(${/home/usr/include})
target_link_libraries(testMHD microhttpd ${/home/usr/lib/libmicrohttpd.a})

set(CMAKE_VERBOSE_MAKEFILE 1)
