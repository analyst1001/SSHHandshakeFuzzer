#include "PacketGenerator.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"

#ifndef VERPGEN_H
#define VERPGEN_H

#define MAX_PROTO_VER_LEN 10000
#define MAX_SOFT_VER_LEN 10000
#define MAX_COMMENT_LEN 10000

class SSHVersionPacketGenerator : public PacketGenerator {
    private:
        BPPMessageBuffer *generateValidSSHPrefix();
        BPPMessageBuffer *generateValidProtoVersion();
        BPPMessageBuffer *generateValidSoftwareVersion();

        BPPMessageBuffer *generateRandomSSHPrefix();
        BPPMessageBuffer *generateRandomProtoVersion();
        BPPMessageBuffer *generateRandomSoftwareVersion();
        BPPMessageBuffer *generateRandomComment();

        BPPMessageBuffer *generateValidPacket();
        BPPMessageBuffer *generateRandomPacket();


    public:
        BPPMessageBuffer *generatePacket(MessageBuffer *prevOutput);
};
#endif
