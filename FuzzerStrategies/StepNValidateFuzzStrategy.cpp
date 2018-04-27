#include <cstdlib>
#include <ctime>
#include "StepNValidateFuzzStrategy.h"

StepNValidateFuzzStrategy::StepNValidateFuzzStrategy() {
    this->n = 0;
    this->verify = NULL;
}

unsigned int StepNValidateFuzzStrategy::getN() {
    return this->n;
}

void StepNValidateFuzzStrategy::setN(unsigned int n, vector<OStream*> inputStreams, vector<IStream*> outputStreams, vector<ValidInvalidInputGenerator*> inputGenerators, vector<bool> waitForOutput) {
    this->n = n;
    if (inputStreams.size() >= n && outputStreams.size() >= n && inputGenerators.size() >= n && waitForOutput.size() >= n) {
        this->inputStreams.assign(inputStreams.begin(), inputStreams.end());
        this->inputStreams.resize(n);
        this->outputStreams.assign(outputStreams.begin(), outputStreams.end());
        this->outputStreams.resize(n);
        this->inputGenerators.assign(inputGenerators.begin(), inputGenerators.end());
	this->waitForOutput.assign(waitForOutput.begin(), waitForOutput.end());
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

void StepNValidateFuzzStrategy::applyStrategy() {
    MessageBuffer *msgSend = NULL;
    MessageBuffer *msgRecv = NULL;
    // always sends the input first. This could be parameterized later
    for (unsigned int i = 0; i < (this->n); i++) {
        int inpGen = (i == (this->n) - 1) ? (rand() % this->inputGenerators.size()) : i;
        msgSend = this->inputGenerators[inpGen]->generateInput(msgRecv);
        // delete the previous message read from output
        if (msgRecv) {
            delete msgRecv;
	    msgRecv = NULL;
        }
        this->inputStreams[i]->write(msgSend);
        delete msgSend;

        if (this->waitForOutput[i]) {
            msgRecv = this->outputStreams[i]->read();   
        }
    }
/*    if (!getWaitForOutput() || (this->n == 0)) {
        msgRecv = this->outputStreams[(this->n) - 1]->read();   
    }*/
    // msgRecv should be non NULL here due to tautology if n > 0
    if (verify != NULL) {
        verify(msgRecv);
    }
    if (msgRecv) {
        delete msgRecv;
    }
}
