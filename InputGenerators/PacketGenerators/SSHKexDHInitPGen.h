#include "PacketGenerator.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"

#ifndef SSHKEXDHINIT_H
#define SSHKEXDHINIT_H

#define MAX_MPINT_SIZE 100

class SSHKexDHInitPacketGenerator : public PacketGenerator {
    private:

        BPPMessageBuffer *generateValidPacket();
        BPPMessageBuffer *generateRandomPacket();

        BPPMessageBuffer *generateValidPacketType();
        BPPMessageBuffer *generateRandomPacketType();
        BPPMessageBuffer *generateRandomMPInt();
        BPPMessageBuffer *generateValidMPInt();

    public:
        BPPMessageBuffer *generatePacket(MessageBuffer *prevOutput);

};
#endif
