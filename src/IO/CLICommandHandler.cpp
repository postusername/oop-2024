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

Command CLICommandHandler::getCommand(char key) {
    if (keyToCommand.find(key) == keyToCommand.end()){
        throw std::invalid_argument("Invalid key");
    }
    return keyToCommand[key];
}
