cmake_minimum_required(VERSION 3.10)
project(MyHashMap)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

file(GLOB SOURCES "${SRC_DIR}/*.cpp")
include_directories("${INCLUDE_DIR}")

add_executable(${PROJECT_NAME} ${SOURCES})
