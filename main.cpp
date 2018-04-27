#include <iostream>
#include <cstdlib>
#include "Fuzzers/SSHHandshakeStepNValidateFuzzer.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cout<<"USAGE:"<<argv[0]<<" <server IP> <service port> <N>"<<endl;
    }
    SSHHandshakeStepNValidateFuzzer *fuzzer = new SSHHandshakeStepNValidateFuzzer();
    fuzzer->setSSHServerIPAddr(argv[1]);
    fuzzer->setSSHServerPort(atoi(argv[2]));
    fuzzer->setN(atoi(argv[3]));
    fuzzer->fuzz();
    delete fuzzer;
    return 0;
}
