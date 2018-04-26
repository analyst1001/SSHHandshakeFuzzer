#include "SSHNewKeysPGen.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"
#include <ctime>
#include <cstdlib>

BPPMessageBuffer *SSHNewKeysPacketGenerator::generatePacket(MessageBuffer *prevOutput) {
    srand(time(NULL));
    if (getGenerateValid()) {
        return generateValidPacket();
    }
    else {
        return generateRandomPacket();
    }
}

BPPMessageBuffer *SSHNewKeysPacketGenerator::generateValidPacketType() {
    BPPMessageBuffer *pktType = new BPPMessageBuffer();
    pktType->push_back(21);
    return pktType;
}

BPPMessageBuffer *SSHNewKeysPacketGenerator::generateRandomPacketType() {
    BPPMessageBuffer *pktType = new BPPMessageBuffer();
    pktType->push_back(rand() % 256);
    return pktType;
}

BPPMessageBuffer *SSHNewKeysPacketGenerator::generateValidPacket() {
    BPPMessageBuffer *packet = new BPPMessageBuffer();

    BPPMessageBuffer *pktType = generateValidPacketType();
    packet->append(pktType);
    delete pktType;

    return packet;
}

BPPMessageBuffer *SSHNewKeysPacketGenerator::generateRandomPacket() {
    BPPMessageBuffer *packet = new BPPMessageBuffer();

    BPPMessageBuffer *pktType = generateRandomPacketType();
    packet->append(pktType);
    delete pktType;

    return packet;
}
