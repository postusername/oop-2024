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


#include "CLICommandHandler.h"


CLICommandHandler::CLICommandHandler(const std::string &configFilePath) {
    if (!configFilePath.empty() && loadFromFile(configFilePath)) {
        return;
    }

    keyToCommand['s'] = Command::Shoot;
    keyToCommand['a'] = Command::UseAbility;
    keyToCommand['e'] = Command::Save;
    keyToCommand['q'] = Command::Exit;
    keyToCommand['d'] = Command::Load;
}

bool CLICommandHandler::loadFromFile(const std::string &filePath) {
    return false;
}

std::string CLICommandHandler::command2str(Command command)
{
    switch (command) {
        case Command::Shoot:
            return "Атака";
        case Command::UseAbility:
            return "Использовать способность";
        case Command::Save:
            return "Сохранить игру";
        case Command::Exit:
            return "Выход";
        case Command::Load:
            return "Загрузить с сохранения";
        default:
            throw std::invalid_argument("Invalid command");
    }
}

Command CLICommandHandler::getCommand(char key) {
    if (keyToCommand.find(key) == keyToCommand.end()){
        throw std::invalid_argument("Invalid key");
    }
    return keyToCommand[key];
}

std::string CLICommandHandler::list_commands() {
    std::stringstream ss;

    ss << "Введите команду:" << std::endl;
    for (auto const& x : keyToCommand) {
        ss << x.first << " - " << this->command2str(x.second) << std::endl;
    }

    return ss.str();
}
