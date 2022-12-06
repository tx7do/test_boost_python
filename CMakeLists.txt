cmake_minimum_required(VERSION 3.16)

project(test_boost_python)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)

# Set C version
set(CMAKE_C_STANDARD 11)


# 查找python3，Interpreter：解释器；Development：开发环境（包括头文件和库文件）；Compiler：编译器；Numpy：numpy的包含目录。
FIND_PACKAGE(Python3 REQUIRED COMPONENTS Interpreter Development)
FIND_PACKAGE(Boost COMPONENTS python${PYTHON_VERSION_MAJOR} ${PYTHON_VERSION_MINOR})

message(STATUS "Python: Version=${Python3_VERSION} Interpreter=${Python3_EXECUTABLE}")
if (NOT Python3_FOUND AND Python3_Development_FOUND)
    FIND_PACKAGE(PythonInterp)
    FIND_PACKAGE(PythonLibs REQUIRED)
    if (NOT PYTHONINTERP_FOUND)
        message("Python not found")
    endif ()
endif ()

add_executable(test_boost_python main.cpp)

target_link_libraries(test_boost_python ${Boost_LIBRARIES} ${Python3_LIBRARIES})
target_include_directories(test_boost_python PRIVATE ${Python3_INCLUDE_DIRS})
