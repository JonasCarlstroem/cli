cmake_minimum_required(VERSION 3.23)

project(cli VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

CREATE_LIB(cli INTERFACE)
#add_library(cli INTERFACE)

target_compile_features(cli INTERFACE cxx_std_17)

target_include_directories(cli 
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include/cli>
)

#target_link_libraries(cli
#	INTERFACE parser
#)

INSTALL_LIB(cli True cli)