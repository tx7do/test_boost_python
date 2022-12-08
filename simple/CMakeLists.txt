cmake_minimum_required(VERSION 3.16)

project(simple)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)

# Set C version
set(CMAKE_C_STANDARD 11)

add_executable(simple main.cpp)

target_link_libraries(simple ${Boost_LIBRARIES} ${Python3_LIBRARIES})
target_include_directories(simple PRIVATE ${Python3_INCLUDE_DIRS})
