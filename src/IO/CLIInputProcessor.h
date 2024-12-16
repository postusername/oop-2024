#pragma once

#include <unordered_map>
#include <cstddef>
#include <limits>
#include "../Ship.h"
#include "../Game/GameSettings.h"
#include "CLICommandHandler.h"


template <typename CommandHandlerT>
class CLIInputProcessor {
private:
    CommandHandlerT command_handler;

    Orientation readShipOrientation();
    std::pair<size_t, size_t> readCoords(GameSettings& settings);
public:
    CLIInputProcessor() : command_handler(CommandHandlerT()) { }
    bool askForReset();
    Command askForCommand();
    std::pair<size_t, size_t> askForFirePoint(GameSettings& settings);
    std::pair<size_t, size_t> askForAbilityPoint(GameSettings& settings);
    GameSettings getGameMode();
    std::string askForFilename();
    std::pair<std::vector <Orientation>, std::vector<std::pair<size_t, size_t>>> getInitialShips(GameSettings& settings);
};


template <typename CommandHandlerT>
GameSettings CLIInputProcessor<CommandHandlerT>::getGameMode() {
    while (true) {
        try {
            std::cout << "Enter game mode (1 for easy, 2 for hard, 3 for test):" << std::endl;
            
            int mode;
            std::cin >> mode;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }

            switch (mode) {
                case 1:
                    return GameSettings(10, std::vector<unsigned short>{3, 2, 2, 1, 1});
                case 2:
                    return GameSettings(7, std::vector<unsigned short>{4, 3, 2, 1});
                case 3:
                    return GameSettings(4, std::vector<unsigned short>{2, 1});
                default:
                    throw std::invalid_argument("Invalid game mode. Please enter 1, 2 or 3.");
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

template <typename CommandHandlerT>
std::string CLIInputProcessor<CommandHandlerT>::askForFilename()
{
    std::cout << "Enter filename:" << std::endl;
    std::string s; std::cin >> s;
    return s;
}

template <typename CommandHandlerT>
bool CLIInputProcessor<CommandHandlerT>::askForReset()
{
    std::cout << "Start new game? (y/n)" << std::endl;
    std::string answer;
    while (true) {
        std::cin >> answer;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Invalid input. Please enter 'y' or 'n'." << std::endl;
            continue;
        }

        if (answer == "y" || answer == "Y") {
            return true;
        } else if (answer == "n" || answer == "N") {
            return false;
        } else {
            std::cerr << "Error: Invalid answer. Please enter 'y' or 'n'." << std::endl;
        }
    }
}

template <typename CommandHandlerT>
Command CLIInputProcessor<CommandHandlerT>::askForCommand() {
    std::cout << command_handler.list_commands() << std::endl;
    
    while (true) {
        try {
            char choice;
            std::cin >> choice;
            Command command = this->command_handler.getCommand(choice);
            return command;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

template <typename CommandHandlerT>
std::pair<size_t, size_t> CLIInputProcessor<CommandHandlerT>::askForFirePoint(GameSettings& settings) {
    std::cout << "Enter x, y coordinates for ATTACK: " << std::endl;
    return readCoords(settings);
}

template <typename CommandHandlerT>
std::pair<size_t, size_t> CLIInputProcessor<CommandHandlerT>::askForAbilityPoint(GameSettings& settings) {
    std::cout << "Enter x, y coordinates for SKILL: " << std::endl;
    return readCoords(settings);
}

template <typename CommandHandlerT>
std::pair<std::vector<Orientation>, std::vector<std::pair<size_t, size_t>>> CLIInputProcessor<CommandHandlerT>::getInitialShips(GameSettings& settings) {
    std::vector<Orientation> orientations;
    std::vector<std::pair<size_t, size_t>> coords;
    for (size_t i = 0; i < settings.shipLengths.size(); i++)
    {
        orientations.push_back(readShipOrientation());
        std::cout << "Enter coordinates for ship " << i + 1 << ": " << std::endl;
        coords.push_back(readCoords(settings));
    }
    return std::make_pair(orientations, coords);
}

template <typename CommandHandlerT>
Orientation CLIInputProcessor<CommandHandlerT>::readShipOrientation() {
    char orientationInput;
    std::cout << "Enter orientation (H for Horizontal, V for Vertical): " << std::endl;
    while (true) {
        std::cin >> orientationInput;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Invalid input. Please enter 'H' or 'V'." << std::endl;
            continue;
        }

        if (orientationInput == 'H' || orientationInput == 'h') {
            return Orientation::Horizontal;
        } else if (orientationInput == 'V' || orientationInput == 'v') {
            return Orientation::Vertical;
        } else {
            std::cerr << "Error: Invalid orientation. Please enter 'H' or 'V'." << std::endl;
        }
    }
}

template <typename CommandHandlerT>
std::pair<size_t, size_t> CLIInputProcessor<CommandHandlerT>::readCoords(GameSettings& settings) {
    size_t x, y;
    while (true) {
        std::cin >> x >> y;
        if (std::cin.fail() || x > settings.boardSize || y > settings.boardSize || x < 1 || y < 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Invalid input. Please enter valid coordinates." << std::endl;
            continue;
        }
        return std::pair<size_t, size_t>{x - 1, y - 1};
    }
}