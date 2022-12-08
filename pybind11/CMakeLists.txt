cmake_minimum_required(VERSION 3.16)

project(pybind11)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)

# Set C version
set(CMAKE_C_STANDARD 11)

add_executable(pybind11 ./main.cpp)

target_link_libraries(pybind11 ${Boost_LIBRARIES} ${Python3_LIBRARIES})
target_include_directories(pybind11 PRIVATE ${Python3_INCLUDE_DIRS} ../third_party/pybind11/include)
