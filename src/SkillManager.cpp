#include "SkillManager.h"
#include <algorithm>
#include <random>


SkillManager::SkillManager(InputProcessor& inputProcessor, GameBoard& enemyBoard, ShipManager& enemyShipManager)
    : inputProcessor(inputProcessor), enemyBoard(enemyBoard), enemyShipManager(enemyShipManager) {
    factories.push_back(new DoubleDamageFactory());
    factories.push_back(new ScannerFactory());
    factories.push_back(new BombingFactory());

    std::vector<int> abilityTypes = {0, 1, 2};
    std::shuffle(abilityTypes.begin(), abilityTypes.end(), std::mt19937(std::random_device()()));

    for (int type : abilityTypes) {
        abilities.push(factories[type]->createAbility(inputProcessor, enemyBoard, enemyShipManager));
    }
}

void SkillManager::applyAbility()
{
    if (abilities.empty()) {
        throw NoAbilitiesAvailableException();
    }
    abilities.front()->apply();
    delete abilities.front();
    abilities.pop();
}

void SkillManager::addSkill() {
    int randomChoice = rand() % factories.size();
    abilities.push(factories[randomChoice]->createAbility(inputProcessor, enemyBoard, enemyShipManager));
}

SkillManager::~SkillManager() {
    for (auto factory : factories) {
        delete factory;
    }
    clearAbilities();
}

void SkillManager::showAbilities() const {
    std::queue<ISkill*> copy = abilities;
    while (!copy.empty()) {
        std::cout << copy.front()->getName() << std::endl;
        copy.pop();
    }
    std::cout << std::endl;
}

void SkillManager::clearAbilities() {
    while (!abilities.empty()) {
        delete abilities.front();
        abilities.pop();
    }
}

std::istream& operator>>(std::istream& is, SkillManager& manager) {
    int abilityCount;

    is >> abilityCount;
    if (is.fail()) {
        throw std::ios_base::failure("Invalid format for ability count");
    }

    manager.clearAbilities();

    std::string abilityName;
    for (int i = 0; i < abilityCount; ++i) {
        is >> abilityName;
        if (is.fail()) {
            throw std::ios_base::failure("Error reading ability name");
        }

        if (abilityName == "DoubleDamage") {
            manager.abilities.push(new DoubleDamage(manager.inputProcessor));
        } else if (abilityName == "Scanner") {
            manager.abilities.push(new Scanner(manager.enemyBoard, manager.inputProcessor));
        } else if (abilityName == "Bombing") {
            manager.abilities.push(new Bombing(manager.enemyShipManager));
        } else {
            throw std::invalid_argument("Unknown ability: " + abilityName);
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, SkillManager& manager) {
    os << manager.abilities.size() << "\n";

    std::queue<ISkill*> abilities = manager.abilities;
    while (!abilities.empty()) {
        os << abilities.front()->getName() << " ";
        abilities.pop();
    }
    os << "\n";
    return os;
}
