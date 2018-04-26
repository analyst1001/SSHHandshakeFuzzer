#include "FuzzStrategy.h"
#include <vector>

#ifndef STEPNVALFUZZSTRATEGY_H
#define STEPNVALFUZZSTRATEGY_H
class StepNValidateFuzzStrategy : public FuzzStrategy {
    private:
        unsigned int n;
        // input stream for the target, i.e. the target reads input from here
        vector<IStream> inputStreams;
        // output stream for the target, i.e. the target writes output here
        vector<OStream> outputStreams;
        Vector<ValidInvalidInputGenerator> inputGenerators;
        void (*verify)(MessageBuffer);

    public:
        void applyStrategy();
        void setN(unsigned int n, vector<IStream> inputStreams, vector<OStream> outputStreams, vector<ValidInvalidInputGenerator> inputGenerators);
        void setVerify(void (*verify)(MessageBuffer));
        unsigned int getN();

};
#endif
