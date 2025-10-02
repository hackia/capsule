cmake_minimum_required(VERSION 3.10)
project(capsule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(capsule main.cpp)
install(TARGETS capsule DESTINATION bin)