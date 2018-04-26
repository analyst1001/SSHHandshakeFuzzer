#include "SSHVersionPGen.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"
#include <cstdlib>
#include <ctime>

BPPMessageBuffer *SSHVersionPacketGenerator::generateRandomPacket() {
    BPPMessageBuffer *packet = new BPPMessageBuffer();

    BPPMessageBuffer *sshPrefix = generateRandomSSHPrefix();
    packet->append(sshPrefix);
    delete sshPrefix;

    packet->push_back('-');

    BPPMessageBuffer *protoVer = generateRandomProtoVersion();
    packet->append(protoVer);
    delete protoVer;

    packet->push_back('-');

    BPPMessageBuffer *softVer = generateRandomSoftwareVersion();
    packet->append(softVer);
    delete softVer;

    if (rand() % 2) {
        packet->push_back(' ');

        BPPMessageBuffer *comment = generateRandomComment();
        packet->append(comment);
        delete comment;
    }
    if (rand() % 2) {
        packet->append("\r\n");
    }
    return packet;

}

BPPMessageBuffer *SSHVersionPacketGenerator::generateValidPacket() {
    BPPMessageBuffer *packet = new BPPMessageBuffer();

    BPPMessageBuffer *sshPrefix = generateValidSSHPrefix();
    packet->append(sshPrefix);
    delete sshPrefix;

    packet->push_back('-');

    BPPMessageBuffer *protoVer = generateValidProtoVersion();
    packet->append(protoVer);
    delete protoVer;

    packet->push_back('-');

    BPPMessageBuffer *softVer = generateValidSoftwareVersion();
    packet->append(softVer);
    delete softVer;

    packet->append("\r\n");
    return packet;

}

BPPMessageBuffer *SSHVersionPacketGenerator::generateValidSSHPrefix() {
    return new BPPMessageBuffer("SSH");
}

BPPMessageBuffer *SSHVersionPacketGenerator::generateRandomSSHPrefix() {
    BPPMessageBuffer *prefix = new BPPMessageBuffer();
    for (unsigned int i = 0; i < 3; i++) {
        prefix->push_back(rand() % 256);
    }
    return prefix;
}

BPPMessageBuffer *SSHVersionPacketGenerator::generateRandomProtoVersion() {
    BPPMessageBuffer *protoVer = new BPPMessageBuffer();
    unsigned int protoVerLen = rand() % MAX_PROTO_VER_LEN;
    for (unsigned int i = 0; i < protoVerLen; i++) {
        protoVer->push_back(rand() % 256);
    }
    return protoVer;
}

BPPMessageBuffer *SSHVersionPacketGenerator::generateValidProtoVersion() {
    return new BPPMessageBuffer("2.0");
}

BPPMessageBuffer *SSHVersionPacketGenerator::generateValidSoftwareVersion() {
    return new BPPMessageBuffer("dropbear_2018.76");
}

BPPMessageBuffer *SSHVersionPacketGenerator::generateRandomSoftwareVersion() {
    unsigned int softVerLen = rand() % MAX_SOFT_VER_LEN;
    BPPMessageBuffer *softVer = new BPPMessageBuffer();
    for (unsigned int i = 0; i < softVerLen; i++) {
        softVer->push_back(rand() % 256);
    }
    return softVer;
}

BPPMessageBuffer *SSHVersionPacketGenerator::generateRandomComment() {
   unsigned int commentLen = rand() % MAX_COMMENT_LEN;
   BPPMessageBuffer *comment = new BPPMessageBuffer();
   for (unsigned int i = 0; i < commentLen; i++) {
       comment->push_back(rand() % 256);
   }
   return comment;
}

BPPMessageBuffer *SSHVersionPacketGenerator::generatePacket(MessageBuffer *prevOutput) {
    srand(time(NULL));
    if (getGenerateValid()) {
        return generateValidPacket();
    }
    else {
        return generateRandomPacket();
    }
}
