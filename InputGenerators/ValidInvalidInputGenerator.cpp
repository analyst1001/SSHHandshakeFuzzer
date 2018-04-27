#include "ValidInvalidInputGenerator.h"

void ValidInvalidInputGenerator::setGenerateValid(bool valid) {
    this->generateValid = valid;
}

bool ValidInvalidInputGenerator::getGenerateValid() {
    return this->generateValid;
}

ValidInvalidInputGenerator::ValidInvalidInputGenerator() {
    this->generateValid = false;
}
