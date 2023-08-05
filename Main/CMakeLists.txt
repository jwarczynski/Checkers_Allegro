cmake_minimum_required(VERSION 3.22)
project(Checkers_Main)

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

file(GLOB_RECURSE SOURCES "Main/src/*.cpp")

# turn off terminal
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")

add_executable(Checkers ${SOURCES} include/types.h src/main.c src/boardSetup.c include/boardSetup.h src/gameEngine/gameEngineUtil.c include/gameEngine/gameEngineUtil.h src/moves/move.c include/moves/move.h include/moves/captures/queenCapture.h include/moves/moveUtil.h src/moves/captures/queenCapture.c src/moves/moveUtil.c src/gameEngine/gameEngine.c include/gameEngine/gameEngine.h src/gameEngine/playerMove.c include/gameEngine/playerMove.h src/moves/captures/captureUtil.c include/moves/captures/captureUtil.h src/moves/moves/pawnMove.c src/moves/moves/queenMove.c src/moves/captures/pawnCapture.c include/moves/captures/pawnCapture.h src/moves/captures/capture.c include/moves/captures/capture.h src/gameEngine/moveValidator.c include/gameEngine/moveValidator.h src/input/consoleInputParser.c include/input/consoleInputParser.h include/ui/uiState.h src/ui/uiInitializer.c include/ui/uiInitializer.h src/ui/display/boardPainter.c include/ui/display/boardPainter.h src/ui/events/eventHandler.c include/ui/events/eventHandler.h src/ui/events/eventHandlerUtil.c include/ui/events/eventHandlerUtil.h include/ui/display/UIConstants.h src/threadManager.c include/threadManager.h include/globals.h src/ui/display/animations/moveAnimation.c include/ui/display/animations/moveAnimation.h)
add_library(Checkers_lib STATIC ${SOURCES} include/types.h src/main.c src/boardSetup.c include/boardSetup.h src/gameEngine/gameEngineUtil.c include/gameEngine/gameEngineUtil.h src/moves/move.c include/moves/move.h include/moves/captures/queenCapture.h include/moves/moveUtil.h src/moves/captures/queenCapture.c src/moves/moveUtil.c src/gameEngine/gameEngine.c include/gameEngine/gameEngine.h src/gameEngine/playerMove.c include/gameEngine/playerMove.h src/moves/captures/captureUtil.c include/moves/captures/captureUtil.h src/moves/moves/pawnMove.c src/moves/moves/queenMove.c src/moves/captures/pawnCapture.c include/moves/captures/pawnCapture.h src/moves/captures/capture.c include/moves/captures/capture.h src/gameEngine/moveValidator.c include/gameEngine/moveValidator.h src/input/consoleInputParser.c include/input/consoleInputParser.h include/ui/uiState.h src/ui/uiInitializer.c include/ui/uiInitializer.h src/ui/display/boardPainter.c include/ui/display/boardPainter.h src/ui/events/eventHandler.c include/ui/events/eventHandler.h src/ui/events/eventHandlerUtil.c include/ui/events/eventHandlerUtil.h include/ui/display/UIConstants.h src/threadManager.c include/threadManager.h include/globals.h)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Main/bin)
message("My variable value: ${CMAKE_BINARY_DIR}")

set_target_properties(Checkers PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        )
