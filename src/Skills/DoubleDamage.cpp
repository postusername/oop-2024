#include "DoubleDamage.h"

DoubleDamage::DoubleDamage(){};

void DoubleDamage::apply(){
    oldOutputProcessor::showMessage("Double Damage ability applied");
    inputProcessor.getFlag(flagType::DoubleDamage) = true;
}

std::string DoubleDamage::getName() {
    return "DoubleDamage";
}
