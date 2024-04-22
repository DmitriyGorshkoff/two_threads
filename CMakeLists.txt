cmake_minimum_required(VERSION 3.4.3)

project(TwoThreads)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_EXE 	main.cpp)

set(SOURCE_LIB1 FirstThreadClass.cpp)

set(SOURCE_LIB2 SecondThreadClass.cpp)

add_library(FirstThreadClass STATIC ${SOURCE_LIB1})

add_library(SecondThreadClass STATIC ${SOURCE_LIB2})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main FirstThreadClass)

target_link_libraries(main SecondThreadClass)