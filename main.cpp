#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "Fuzzers/SSHHandshakeStepNValidateFuzzer.h"

using namespace std;

int main(int argc, char *argv[]) {
    signal(SIGPIPE, SIG_IGN);
    if (argc < 4) {
        cout<<"USAGE:"<<argv[0]<<" <server IP> <service port> <N>"<<endl;
        return 1;
    }
    SSHHandshakeStepNValidateFuzzer *fuzzer = new SSHHandshakeStepNValidateFuzzer();
    fuzzer->setSSHServerIPAddr(argv[1]);
    fuzzer->setSSHServerPort(atoi(argv[2]));
    fuzzer->setN(atoi(argv[3]));
    while (true) {
	try {
    	    fuzzer->fuzz();
        }
        catch (...) {
            continue;
        }
    }
    delete fuzzer;
    
    return 0;
}
