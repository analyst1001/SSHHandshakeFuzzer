#include "SSHKexDHInitPGen.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"
#include <ctime>
#include <cstdlib>

BPPMessageBuffer *SSHKexDHInitPacketGenerator::generatePacket(MessageBuffer *prevOutput) {
    srand(time(NULL));
    if (getGenerateValid()) {
        return generateValidPacket();
    }
    else {
        return generateRandomPacket();
    }
}

BPPMessageBuffer *SSHKexDHInitPacketGenerator::generateRandomPacket() {
    bool correctLengths = (rand() % 2 == 0);
    BPPMessageBuffer *packet = new BPPMessageBuffer();

    BPPMessageBuffer *pktType = generateRandomPacketType();
    packet->append(pktType);
    delete pktType;

    BPPMessageBuffer *randMPInt = generateRandomMPInt();
    unsigned int mpintSize = correctLengths ? randMPInt->length() : rand(); 
    packet->append(mpintSize);
    packet->append(randMPInt);
    delete randMPInt;

    return packet;
}

BPPMessageBuffer *SSHKexDHInitPacketGenerator::generateValidPacket() {
    BPPMessageBuffer *packet = new BPPMessageBuffer();

    BPPMessageBuffer *pktType = generateValidPacketType();
    packet->append(pktType);
    delete pktType;

    BPPMessageBuffer *validMPInt = generateValidMPInt();
    unsigned int mpintSize = validMPInt->length();
    packet->append(mpintSize);
    packet->append(validMPInt);
    delete validMPInt;

    return packet;
}

BPPMessageBuffer *SSHKexDHInitPacketGenerator::generateRandomPacketType() {
    BPPMessageBuffer *pktType = new BPPMessageBuffer();
    pktType->push_back(rand() % 256);
    return pktType;
}

BPPMessageBuffer *SSHKexDHInitPacketGenerator::generateRandomMPInt() {
    BPPMessageBuffer *mpintVal = new BPPMessageBuffer();
    int mpintLen = rand() % MAX_MPINT_SIZE;
    for (unsigned int i = 0; i < mpintLen; i++) {
        mpintVal->push_back(rand() % 256);
    }
    return mpintVal;
}

BPPMessageBuffer *SSHKexDHInitPacketGenerator::generateValidPacketType() {
    BPPMessageBuffer *pktType = new BPPMessageBuffer();
    pktType->push_back(30);
    return pktType;
}

BPPMessageBuffer *SSHKexDHInitPacketGenerator::generateValidMPInt() {
    BPPMessageBuffer *mpIntVal = new BPPMessageBuffer();
    
    // for now, we use a predefined e value over the single group we negotiated
    
    unsigned int mpIntSize = 32;
    mpIntVal->append(mpIntSize);
    
    unsigned char e[] = {0x83, 0x8f, 0x2f, 0x07, 0xb6, 0x77, 0xe1, 0xff, 0x39, 0x70, 0xf4, 0x5f, 0x7a, 0xf3, 0xe3, 0x7f, 0xb3, 0xbc, 0xcf, 0x6c, 0xc2, 0x8a, 0x6a, 0x92, 0x4b, 0x0e, 0x49, 0x8a, 0x77, 0x58, 0x70, 0x03};
    for (unsigned int i = 0; i < mpIntSize; i++) {
        mpIntVal->push_back(e[i]);
    }

    return mpIntVal;
}
