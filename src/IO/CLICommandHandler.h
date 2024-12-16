#pragma once

#include <unordered_map>
#include "../GameController.h"

class CLICommandHandler {
private:
    std::unordered_map<char, Command> keyToCommand;
    bool loadFromFile(const std::string& filePath);
public:
    CLICommandHandler(const std::string& configFilePath = "");
    Command getCommand(char key);
};
