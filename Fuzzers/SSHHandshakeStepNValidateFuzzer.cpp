#include "SSHHandshakeStepNValidateFuzzer.h"
#include "../InputGenerators/PacketGenerators/PacketGenerator.h"
#include "../InputGenerators/PacketGenerators/SSHKexInitPGen.h"
#include "../InputGenerators/PacketGenerators/SSHVersionPGen.h"
#include "../InputGenerators/PacketGenerators/SSHKexDHInitPGen.h"
#include "../InputGenerators/PacketGenerators/SSHNewKeysPGen.h"

SSHHandshakeStepNValidateFuzzer::SSHHandshakeStepNValidateFuzzer() {
    this->strategy = new StepNValidateFuzzStrategy();
    this->stream = new SSHClientIOStream();
    this->srvPort = 22;
    this->n = 0;
}

SSHHandshakeStepNValidateFuzzer::~SSHHandshakeStepNValidateFuzzer() {
    delete stream;
    delete strategy;
}

void SSHHandshakeStepNValidateFuzzer::setSSHServerIPAddr(const char *srvIP) {
    this->srvIP = srvIP;
}

void SSHHandshakeStepNValidateFuzzer::setSSHServerPort(unsigned short srvPort) {
    this->srvPort = srvPort;
}

void SSHHandshakeStepNValidateFuzzer::setN(unsigned int n) {
    this->n = n;
}

void SSHHandshakeStepNValidateFuzzer::fuzz() {
    this->stream->setSSHServerAddr(this->srvIP);
    this->stream->setSSHServerPort(srvPort);
    this->stream->openStream(); 
    vector<OStream*> inputStreams(n, this->stream);
    vector<IStream*> outputStreams(n, this->stream);
    
    SSHVersionPacketGenerator *pkt0Gen = new SSHVersionPacketGenerator();
    SSHKexInitPacketGenerator *pkt1Gen = new SSHKexInitPacketGenerator();
    SSHKexDHInitPacketGenerator *pkt2Gen = new SSHKexDHInitPacketGenerator();
    SSHNewKeysPacketGenerator *pkt3Gen = new SSHNewKeysPacketGenerator();
    
    vector<ValidInvalidInputGenerator*> inputGenerators;
    inputGenerators.push_back(pkt0Gen);
    inputGenerators.push_back(pkt1Gen);
    inputGenerators.push_back(pkt2Gen);
    inputGenerators.push_back(pkt3Gen);
    
    vector<bool> waitForOutput;
    waitForOutput.push_back(true);
    waitForOutput.push_back(false);
    waitForOutput.push_back(true);
    waitForOutput.push_back(false);

    this->strategy->setN(this->n, inputStreams, outputStreams, inputGenerators, waitForOutput);
    this->strategy->applyStrategy();

    inputGenerators.clear();
    delete pkt0Gen;
    delete pkt1Gen;
    delete pkt2Gen;
    delete pkt3Gen;
    this->stream->closeStream();
}
