cmake_minimum_required(VERSION 3.5)
project(ip_cap)

set(CMAKE_CXX_STANDARD 11)

find_library(pcap /usr/lib)
find_library(pthread /usr/lib)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
message(staus "GTK3_INCLUDE_DIRS = ${GTK3_INCLUDE_DIRS}")
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

set(SOURCE_FILES main.c table.c packet_handler.c global.h)
add_executable(ip_cap ${SOURCE_FILES})
target_link_libraries(ip_cap pcap)
target_link_libraries(ip_cap pthread)
target_link_libraries(ip_cap ${GTK3_LIBRARIES})
