cmake_minimum_required(VERSION 3.10)

project(ConnectFour VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(connect-four main.cpp ConnectFour.cpp)
