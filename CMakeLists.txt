cmake_minimum_required(VERSION 3.28)
project(BattleShips)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(BattleShips
        src/Exceptions/SkillException.cpp
        src/Exceptions/AttackCoordsException.cpp
        src/Exceptions/ShipException.cpp
        src/Factories/DoubleDamageFactory.cpp
        src/Factories/ScannerFactory.cpp
        src/Factories/BombingFactory.cpp
        src/Game/Game.h
        src/Game/GameSettings.cpp
        src/Game/GameState.cpp
        src/Game/GameView.h
        src/IO/CLIBoardRenderer.h
        src/IO/CLICommandHandler.h
        src/IO/CLIInputProcessor.h
        src/IO/CLIRenderer.h
        src/Players/ComputerPlayer.cpp
        src/Players/UserPlayer.cpp
        src/Skills/DoubleDamage.cpp
        src/Skills/Scanner.cpp
        src/Skills/Bombing.cpp
        src/Cell.cpp
        src/GameBoard.cpp
        src/GameController.h
        src/main.cpp
        src/Ship.cpp
        src/ShipManager.cpp
        src/SkillManager.cpp)
