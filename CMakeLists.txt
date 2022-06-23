cmake_minimum_required(VERSION 3.12.0)

project(oasisEngine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OASDK_MAIN_DIR ${dir


add_library(oaUtilities SHARED CMakeLists.txt)

add_subdirectory(oaUtilities)

