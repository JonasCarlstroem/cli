cmake_minimum_required(VERSION 3.23)

project(parser LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(parser INTERFACE)

target_compile_features(parser INTERFACE cxx_std_17)