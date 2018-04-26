#include "StepNValidateFuzzStrategy.h"

unsigned int StepNValidateFuzzStrategy::getN() {
    return this->n;
}

void StepNValidateFuzzStrategy::setN(unsigned int n, vector<IStream> inputStreams, vector<OStream> outputStreams, vector<ValidInvalidInputGenerator> inputGenerators) {
    this->n = n;
    if (inputFDs.size() >= n && outputFDs.size() >= n) {
        this->inputStreams.assign(inputStreams.begin(), inputStreams.end());
        this->inputStreams.resize(n);
        this->outputStreams.assign(outputStreams.begin(), outputStreams.end());
        this->outputStreams.resize(n);
        this->inputGenerators.assign(inputGenerators);
        this->inputGenerators.resize(n);
        for (unsigned int i = 0; i < n; i++) {
            this->inputGenerators[i].setGenerateValid(true);
        }
        this->inputGenerators[n-1].setGenerateValid(false);
    }
    else {
        throw "Too less file descriptors for StepNValidateFuzzStrategy!";
    }
}

void StepNValidateFuzzStrategy::setVerify(void (*verify)(MessageBuffer)) {
    this->verify = verify;
}


void StepNValidateFuzzStrategy::applyStrategy() {
    // always sends the input first
    for (unsigned int i = 0; i < n-1; i++) {
        MessageBuffer msg = inputGenerators[i].gene
    }
}
