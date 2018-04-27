#include "Fuzzer.h"
#include "../FuzzerStrategies/StepNValidateFuzzStrategy.h"
#include "../Streams/SSHClientIOStream.h"

#ifndef SSHHANDSTEPNVALFUZZ_H
#define SSHHANDSTEPNVALFUZZ_H
class SSHHandshakeStepNValidateFuzzer : public Fuzzer {
    private:
        StepNValidateFuzzStrategy *strategy;
        SSHClientIOStream *stream;
        unsigned int n;
        const char *srvIP;
        unsigned short srvPort;

    public:
        SSHHandshakeStepNValidateFuzzer();
        ~SSHHandshakeStepNValidateFuzzer();
        void fuzz();
        void setSSHServerIPAddr(const char *srvIP);
        void setSSHServerPort(unsigned short port);
        void setN(unsigned int n);
};
#endif
