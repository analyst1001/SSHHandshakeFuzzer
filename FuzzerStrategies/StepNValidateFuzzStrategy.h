#include <vector>
#include "FuzzStrategy.h"
#include "../InputGenerators/ValidInvalidInputGenerator.h"
#include "../Streams/IStream.h"
#include "../Streams/OStream.h"

#ifndef STEPNVALFUZZSTRATEGY_H
#define STEPNVALFUZZSTRATEGY_H
class StepNValidateFuzzStrategy : public FuzzStrategy {
    private:
        unsigned int n;
        // input stream for the target, i.e. fuzzer writes here and the target reads input from here
        vector<OStream*> inputStreams;
        // output stream for the target, i.e. the target writes output here and fuzzer reads here
        vector<IStream*> outputStreams;
        vector<ValidInvalidInputGenerator*> inputGenerators;
        void (*verify)(MessageBuffer*);
        vector<bool> waitForOutput;

    public:
        StepNValidateFuzzStrategy();
        void applyStrategy();
        void setN(unsigned int n, vector<OStream*> inputStreams, vector<IStream*> outputStreams, vector<ValidInvalidInputGenerator*> inputGenerators, vector<bool> waitForOutput);
        void setVerify(void (*verify)(MessageBuffer*));
        unsigned int getN();

};
#endif
