cmake_minimum_required(VERSION 3.28)
project(BattleShips)

set(CMAKE_CXX_STANDARD 17)

add_executable(BattleShips
        src/Exceptions/SkillException.cpp
        src/Exceptions/AttackCoordsException.cpp
        src/Exceptions/ShipException.cpp
        src/Factories/DoubleDamageFactory.cpp
        src/Factories/ScannerFactory.cpp
        src/Factories/BombingFactory.cpp
        src/Game/Game.cpp
        src/Game/GameSettings.cpp
        src/Game/GameState.cpp
        src/Game/GameView.cpp
        src/IO/CLIBoardRenderer.cpp
        src/IO/CLICommandHandler.cpp
        src/IO/CLIInputProcessor.cpp
        src/IO/CLIRenderer.cpp
        src/Players/ComputerPlayer.cpp
        src/Players/UserPlayer.cpp
        src/Skills/DoubleDamage.cpp
        src/Skills/Scanner.cpp
        src/Skills/Bombing.cpp
        src/Cell.cpp
        src/GameBoard.cpp
        src/GameController.cpp
        src/main.cpp
        src/Ship.cpp
        src/ShipManager.cpp
        src/SkillManager.cpp)
