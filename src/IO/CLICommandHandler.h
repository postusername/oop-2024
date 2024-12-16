#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include <stdexcept>

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
    std::string command2str(Command command);
public:
    CLICommandHandler(const std::string& configFilePath = "");
    Command getCommand(char key);
    std::string list_commands();
};
