project(tixtax)

include_directories("include")

file(GLOB SRC "src/*.cpp")

add_executable(tixtax ${SRC})