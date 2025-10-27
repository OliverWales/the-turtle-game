cmake_minimum_required(VERSION 3.10)
project(TheTurtleGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML2
set(SFML_ROOT /opt/homebrew/opt/sfml@2)
set(SFML_INCLUDE_DIR ${SFML_ROOT}/include)
set(SFML_LIBRARY_DIR ${SFML_ROOT}/lib)

# Include directories
include_directories(${SFML_INCLUDE_DIR})

# Add executable
add_executable(TheTurtleGame
    TheTurtleGame/TheTurtleGame/Main.cpp
    TheTurtleGame/TheTurtleGame/Game.cpp
    TheTurtleGame/TheTurtleGame/Game.hpp
    TheTurtleGame/TheTurtleGame/State.hpp
    TheTurtleGame/TheTurtleGame/StateMachine.cpp
    TheTurtleGame/TheTurtleGame/StateMachine.hpp
    TheTurtleGame/TheTurtleGame/SplashState.cpp
    TheTurtleGame/TheTurtleGame/SplashState.hpp
    TheTurtleGame/TheTurtleGame/MainMenuState.cpp
    TheTurtleGame/TheTurtleGame/MainMenuState.hpp
    TheTurtleGame/TheTurtleGame/SetupState.cpp
    TheTurtleGame/TheTurtleGame/SetupState.hpp
    TheTurtleGame/TheTurtleGame/ArcadeGameState.cpp
    TheTurtleGame/TheTurtleGame/ArcadeGameState.hpp
    TheTurtleGame/TheTurtleGame/SurvivalGameState.cpp
    TheTurtleGame/TheTurtleGame/SurvivalGameState.hpp
    TheTurtleGame/TheTurtleGame/GameOverState.cpp
    TheTurtleGame/TheTurtleGame/GameOverState.hpp
    TheTurtleGame/TheTurtleGame/CreditsState.cpp
    TheTurtleGame/TheTurtleGame/CreditsState.hpp
    TheTurtleGame/TheTurtleGame/Button.cpp
    TheTurtleGame/TheTurtleGame/Button.hpp
    TheTurtleGame/TheTurtleGame/Keypad.cpp
    TheTurtleGame/TheTurtleGame/Keypad.hpp
    TheTurtleGame/TheTurtleGame/Number.cpp
    TheTurtleGame/TheTurtleGame/Number.hpp
    TheTurtleGame/TheTurtleGame/Turtle.cpp
    TheTurtleGame/TheTurtleGame/Turtle.hpp
    TheTurtleGame/TheTurtleGame/Coin.cpp
    TheTurtleGame/TheTurtleGame/Coin.hpp
    TheTurtleGame/TheTurtleGame/TileMap.cpp
    TheTurtleGame/TheTurtleGame/TileMap.hpp
    TheTurtleGame/TheTurtleGame/Definitions.hpp
    TheTurtleGame/TheTurtleGame/Maths.hpp
    TheTurtleGame/TheTurtleGame/MapGenerator.hpp
    TheTurtleGame/TheTurtleGame/MiniMap.hpp
    TheTurtleGame/TheTurtleGame/ItemSelector.hpp
)

# Link libraries
link_directories(${SFML_LIBRARY_DIR})
target_link_libraries(TheTurtleGame 
    ${SFML_LIBRARY_DIR}/libsfml-graphics.dylib
    ${SFML_LIBRARY_DIR}/libsfml-window.dylib
    ${SFML_LIBRARY_DIR}/libsfml-system.dylib
    ${SFML_LIBRARY_DIR}/libsfml-audio.dylib
)

# Copy resources to build directory
file(COPY TheTurtleGame/TheTurtleGame/ DESTINATION ${CMAKE_BINARY_DIR}/resources/
     FILES_MATCHING PATTERN "*.png" PATTERN "*.ogg" PATTERN "*.ico"
)

# Set working directory for the executable
set_target_properties(TheTurtleGame PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/resources"
)