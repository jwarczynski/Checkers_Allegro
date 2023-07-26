cmake_minimum_required(VERSION 3.22)
project(Checkers_Tests)

set(CMAKE_CXX_STANDARD 14)

set(ALLEGRO_DIR "../Main/allegro")

set(UNITY_SRC "Unity/src/unity.c" testMain.c src/queenCaptureTest.c include/queenCaptureTest.h src/pawnCaptureTest.c include/pawnCaptureTest.h src/pawnMoveTest.c include/pawnMoveTest.h src/queenMoveTest.c include/queenMoveTest.h src/testUtil.c include/testUtil.h src/gameEngineTest.c include/gameEngineTest.h)

include_directories(${ALLEGRO_DIR}/include)
include_directories(../Main/include)

link_directories(${ALLEGRO_DIR}/lib)

file(GLOB_RECURSE SOURCE_FILES "../Main/src/*.c")
file(GLOB_RECURSE INCLUDE_FILES "../Main/include/*.h")
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.c$")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${UNITY_SRC} ${INCLUDE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Checkers_lib)
