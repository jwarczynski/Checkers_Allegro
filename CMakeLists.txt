cmake_minimum_required(VERSION 3.22)
project(Checkers)

set(CMAKE_CXX_STANDARD 14)

set(ALLEGRO_DIR "allegro")

include_directories(${ALLEGRO_DIR}/include)
include_directories(include)

link_directories(${ALLEGRO_DIR}/lib)

link_libraries(
        allegro.dll
        allegro_font.dll
        allegro_image.dll
        allegro_primitives.dll
        allegro_ttf.dll
)

file(GLOB SOURCES "src/*.cpp")

# turn off terminal
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")

add_executable(Checkers ${SOURCES})

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set_target_properties(Checkers PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        )