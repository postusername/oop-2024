#include "InputProcessor.h"
#include "CLIInputProcessor.h"





GameSettings& InputProcessor::getGameMode() {
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

bool InputProcessor::askForReset() {
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

std::pair<size_t, size_t> InputProcessor::askForFirePoint(GameSettings &settings) {
    std::cout << "Enter x, y coordinates for ATTACK: " << std::endl;
    return readCoords(settings);
}

std::pair<size_t, size_t> InputProcessor::askForAbilityPoint(GameSettings &settings) {
    std::cout << "Enter x, y coordinates for SKILL: " << std::endl;
    return readCoords(settings);
}

std::pair<std::vector<Orientation>, std::vector<std::pair<size_t, size_t>>> InputProcessor::getInitialShips(GameSettings settings) {
    std::vector<Orientation> orientations;
    std::vector<std::pair<size_t, size_t>> coords;
    for (size_t i = 0; i < gameMode.shipLengths.size(); i++)
    {
        orientations.push_back(readShipOrientation());
        std::cout << "Enter coordinates for ship " << i + 1 << ": " << std::endl;
        coords.push_back(readCoords(settings));
    }
    return std::make_pair(orientations, coords);
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

std::pair<size_t, size_t> InputProcessor::readCoords(GameSettings settings) {
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