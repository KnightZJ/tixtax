cmake_minimum_required(VERSION 3.22)
project(tixtax)

include_directories("include")

file(GLOB SRC "src/*.cpp")

add_executable(tixtax ${SRC})