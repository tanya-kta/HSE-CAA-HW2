cmake_minimum_required(VERSION 3.16)
project(HSE_HW2)

set(CMAKE_CXX_STANDARD 14)

add_executable(HSE_HW2 main.cpp algorithms/naive.cpp algorithms/KMP_StandardBr.cpp algorithms/KMP_SmartBrs.cpp)
