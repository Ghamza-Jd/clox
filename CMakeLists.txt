cmake_minimum_required(VERSION 3.27.3)

project(clox C)

find_package(PkgConfig)
pkg_search_module(GLIB REQUIRED IMPORTED_TARGET glib-2.0)

add_executable(clox src/main.c src/chunk.c src/debug.c)

target_link_libraries(clox PkgConfig::GLIB)
