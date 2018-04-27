#include <cstdlib>
#include <ctime>
#include "StepNValidateFuzzStrategy.h"

StepNValidateFuzzStrategy::StepNValidateFuzzStrategy() {
    this->n = 0;
    this->verify = NULL;
    this->waitForOutput = false;
}

unsigned int StepNValidateFuzzStrategy::getN() {
    return this->n;
}

void StepNValidateFuzzStrategy::setN(unsigned int n, vector<OStream*> inputStreams, vector<IStream*> outputStreams, vector<ValidInvalidInputGenerator*> inputGenerators) {
    this->n = n;
    if (inputStreams.size() >= n && outputStreams.size() >= n) {
        this->inputStreams.assign(inputStreams.begin(), inputStreams.end());
        this->inputStreams.resize(n);
        this->outputStreams.assign(outputStreams.begin(), outputStreams.end());
        this->outputStreams.resize(n);
        this->inputGenerators.assign(inputGenerators.begin(), inputGenerators.end());
        for (unsigned int i = 0; i < n; i++) {
            this->inputGenerators[i]->setGenerateValid(true);
        }
        this->inputGenerators[n-1]->setGenerateValid(false);
    }
    else {
        throw "Too less file descriptors for StepNValidateFuzzStrategy!";
    }
}

void StepNValidateFuzzStrategy::setVerify(void (*verify)(MessageBuffer *)) {
    this->verify = verify;
}

void StepNValidateFuzzStrategy::setWaitForOutput(bool waitForOutput) {
    this->waitForOutput = waitForOutput;
}

bool StepNValidateFuzzStrategy::getWaitForOutput() {
    return this->waitForOutput;
}

void StepNValidateFuzzStrategy::applyStrategy() {
    MessageBuffer *msgSend = NULL;
    MessageBuffer *msgRecv = NULL;
    unsigned int i = 0;
    // always sends the input first. This could be parameterized later
    for (i = 0; i < this->n; i++) {
        int inpGen = (i == (this->n) - 1) ? (rand() % this->inputGenerators.size()) : i;
        msgSend = this->inputGenerators[inpGen]->generateInput(msgRecv);
        // delete the previous message read from output
        if (msgRecv) {
            delete msgRecv;
        }
        this->inputStreams[i]->write(msgSend);
        delete msgSend;

        if (getWaitForOutput()) {
            msgRecv = this->outputStreams[i]->read();   
        }
    }
    // if we didn't read outputs earlier, read the output now to pass it for verification
    if (!getWaitForOutput() || (this->n == 0)) {
        msgRecv = this->outputStreams[i]->read();   
    }
    // msgRecv should be non NULL here due to tautology if n > 0
    if (verify != NULL) {
        verify(msgRecv);
    }
    delete msgRecv;
}
