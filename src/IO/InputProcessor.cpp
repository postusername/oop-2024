#include "InputProcessor.h"

std::pair<size_t, size_t> InputProcessor::readCoords() {
    size_t x, y;
    oldOutputProcessor::showMessage("Enter x, y coordinates:");
    
    while (true) {
        std::cin >> x >> y;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Invalid input. Please enter valid coordinates." << std::endl;
            continue;
        }
        return std::pair<size_t, size_t>{x - 1, y - 1};
    }
}

GameSettings* InputProcessor::readGameMode() {
    while (true) {
        try {
            oldOutputProcessor::showMessage("Enter game mode (1 for easy, 2 for hard, 3 for test):");
            
            int mode;
            std::cin >> mode;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }

            switch (mode) {
                case 1:
                    return new GameSettings(10, std::vector<unsigned short>{3, 2, 2, 1, 1});
                case 2:
                    return new GameSettings(7, std::vector<unsigned short>{4, 3, 2, 1});
                case 3:
                    return new GameSettings(4, std::vector<unsigned short>{2, 1});
                default:
                    throw std::invalid_argument("Invalid game mode. Please enter 1, 2 or 3.");
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

bool InputProcessor::readStartNewGame() {
    oldOutputProcessor::showMessage("Start new game? (y/n)");
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

Orientation InputProcessor::readShipOrientation() {
    char orientationInput;
    oldOutputProcessor::showMessage("Enter orientation (H for Horizontal, V for Vertical): ");
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

Option InputProcessor::readOption() {
    oldOutputProcessor::showMessage("Choose an option:");
    oldOutputProcessor::showMessage("1. Shoot");
    oldOutputProcessor::showMessage("2. Use ability and shoot");
    oldOutputProcessor::showMessage("3. Save game");
    oldOutputProcessor::showMessage("4. Exit");
    oldOutputProcessor::showMessage("5. Load game");
    oldOutputProcessor::showMessage("Your choice:");
    
    while (true) {
        try {
            int choice;
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Invalid input. Please enter a number between 1 and 5.");
            }

            if (choice < 1 || choice > 5) {
                throw std::invalid_argument("Invalid choice. Please enter a number between 1 and 5.");
            } else {
                return static_cast<Option>(choice);
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

bool &InputProcessor::getFlag(flagType flagName) {
    return flags[flagName];
}

void InputProcessor::resetFlags() {
    for (auto &flag : flags) {
        flag.second = false;
    }
}
