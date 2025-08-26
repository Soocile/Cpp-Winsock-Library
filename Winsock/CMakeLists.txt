cmake_minimum_required(VERSION 3.10)
project(NetLibrary CXX)

# specifies the header files of the library
include_directories(include)

# define the source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# create the library
add_library(NetLibrary ${SRC_FILES})

# link the winsock library on Windows
target_link_libraries(NetLibrary PRIVATE ws2_32)