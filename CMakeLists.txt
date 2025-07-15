cmake_minimum_required(VERSION 3.23)

project(cli LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(parser)

add_library(cli INTERFACE)

target_compile_features(cli INTERFACE cxx_std_17)

target_include_directories(cli
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/parser/include
)

target_link_libraries(cli
	INTERFACE parser
)

set(LIB_TARGETS cli PARENT_SCOPE)