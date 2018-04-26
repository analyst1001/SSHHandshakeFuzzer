#include "PacketGenerator.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"

#ifndef SSHNEWKEYS_H
#define SSHNEWKEYS_H
class SSHNewKeysPacketGenerator : public PacketGenerator {
    private:
        BPPMessageBuffer *generateValidPacket();
        BPPMessageBuffer *generateRandomPacket();
        BPPMessageBuffer *generateValidPacketType();
        BPPMessageBuffer *generateRandomPacketType();


    public:
        BPPMessageBuffer *generatePacket(MessageBuffer *prevOutput);
};
#endif
