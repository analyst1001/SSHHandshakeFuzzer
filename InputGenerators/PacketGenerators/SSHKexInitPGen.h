#include "PacketGenerator.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#ifndef SSHKEXINIT_H
#define SSHKEXINIT_H

#define COOKIE_LEN 16
#define MAX_ALGO_NAME_LEN 20
#define MAX_ALGO_LIST_LEN 10
#define ALGO_NAME_SEP ','

#define KEX 0
#define SRV_HOST_KEY 1
#define ENCRYPTION 2
#define MAC 3
#define COMPRESSION 4

class SSHKexInitPacketGenerator : public PacketGenerator {
    private:
        BPPMessageBuffer *generateRandomPacketType();
        BPPMessageBuffer *generateCookie();
        BPPMessageBuffer *generateRandomAlgorithmName();
        BPPMessageBuffer *generateRandomAlgorithmList();
        BPPMessageBuffer *generateKexGuessFollows();
        BPPMessageBuffer *generateRandomReserved();

        BPPMessageBuffer *generateValidPacketType();
        BPPMessageBuffer *generateValidAlgorithmList(unsigned int algoType);
        BPPMessageBuffer *generateValidReserved();

        BPPMessageBuffer *generateValidPacket();
        BPPMessageBuffer *generateRandomPacket();

        vector<string> kexAlgoList;
        vector<string> srvHostKeyAlgoList;
        vector<string> encAlgoList;
        vector<string> macAlgoList;
        vector<string> compAlgoList; 

    public:
        SSHKexInitPacketGenerator();
        BPPMessageBuffer *generatePacket(MessageBuffer *prevOutput);
};
#endif
