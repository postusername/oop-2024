#pragma once

#include <unordered_map>
#include <string>

enum class Command {
    Shoot,
    UseAbility,
    Save,
    Load,
    Exit
};

class CLICommandHandler {
private:
    std::unordered_map<char, Command> keyToCommand;
    bool loadFromFile(const std::string& filePath);
public:
    CLICommandHandler(const std::string& configFilePath = "");
    Command getCommand(char key);
};
