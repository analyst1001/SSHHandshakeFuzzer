#include "PacketGenerator.h"
#include "../../MessageBuffers/PlainMessageBuffer.h"

#ifndef VERPGEN_H
#define VERPGEN_H

#define MAX_PROTO_VER_LEN 10000
#define MAX_SOFT_VER_LEN 10000
#define MAX_COMMENT_LEN 10000

class SSHVersionPacketGenerator : public PacketGenerator {
    private:
        PlainMessageBuffer *generateValidSSHPrefix();
        PlainMessageBuffer *generateValidProtoVersion();
        PlainMessageBuffer *generateValidSoftwareVersion();

        PlainMessageBuffer *generateRandomSSHPrefix();
        PlainMessageBuffer *generateRandomProtoVersion();
        PlainMessageBuffer *generateRandomSoftwareVersion();
        PlainMessageBuffer *generateRandomComment();

        PlainMessageBuffer *generateValidPacket();
        PlainMessageBuffer *generateRandomPacket();


    public:
        PlainMessageBuffer *generatePacket(MessageBuffer *prevOutput);
};
#endif
