#include "DoubleDamage.h"

DoubleDamage::DoubleDamage(InputProcessor& inputProcessor) :
    inputProcessor(inputProcessor) {};

void DoubleDamage::apply(){
    OutputProcessor::showMessage("Double Damage ability applied");
    inputProcessor.getFlag(flagType::DoubleDamage) = true;
}

std::string DoubleDamage::getName() {
    return "DoubleDamage";
}
