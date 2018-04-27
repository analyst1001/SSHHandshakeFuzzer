#include "SSHVersionPGen.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"
#include <cstdlib>
#include <ctime>

PlainMessageBuffer *SSHVersionPacketGenerator::generateRandomPacket() {
    PlainMessageBuffer *packet = new PlainMessageBuffer();

    PlainMessageBuffer *sshPrefix = generateRandomSSHPrefix();
    packet->append(sshPrefix);
    delete sshPrefix;

    packet->push_back('-');

    PlainMessageBuffer *protoVer = generateRandomProtoVersion();
    packet->append(protoVer);
    delete protoVer;

    packet->push_back('-');

    PlainMessageBuffer *softVer = generateRandomSoftwareVersion();
    packet->append(softVer);
    delete softVer;

    if (rand() % 2) {
        packet->push_back(' ');

        PlainMessageBuffer *comment = generateRandomComment();
        packet->append(comment);
        delete comment;
    }
    if (rand() % 2) {
        packet->append("\r\n");
    }
    return packet;

}

PlainMessageBuffer *SSHVersionPacketGenerator::generateValidPacket() {
    PlainMessageBuffer *packet = new PlainMessageBuffer();

    PlainMessageBuffer *sshPrefix = generateValidSSHPrefix();
    packet->append(sshPrefix);
    delete sshPrefix;

    packet->push_back('-');

    PlainMessageBuffer *protoVer = generateValidProtoVersion();
    packet->append(protoVer);
    delete protoVer;

    packet->push_back('-');

    PlainMessageBuffer *softVer = generateValidSoftwareVersion();
    packet->append(softVer);
    delete softVer;

    packet->append("\r\n");
    return packet;

}

PlainMessageBuffer *SSHVersionPacketGenerator::generateValidSSHPrefix() {
    return new PlainMessageBuffer("SSH");
}

PlainMessageBuffer *SSHVersionPacketGenerator::generateRandomSSHPrefix() {
    PlainMessageBuffer *prefix = new PlainMessageBuffer();
    for (unsigned int i = 0; i < 3; i++) {
        prefix->push_back(rand() % 256);
    }
    return prefix;
}

PlainMessageBuffer *SSHVersionPacketGenerator::generateRandomProtoVersion() {
    PlainMessageBuffer *protoVer = new PlainMessageBuffer();
    unsigned int protoVerLen = rand() % MAX_PROTO_VER_LEN;
    for (unsigned int i = 0; i < protoVerLen; i++) {
        protoVer->push_back(rand() % 256);
    }
    return protoVer;
}

PlainMessageBuffer *SSHVersionPacketGenerator::generateValidProtoVersion() {
    return new PlainMessageBuffer("2.0");
}

PlainMessageBuffer *SSHVersionPacketGenerator::generateValidSoftwareVersion() {
    return new PlainMessageBuffer("dropbear_2018.76");
}

PlainMessageBuffer *SSHVersionPacketGenerator::generateRandomSoftwareVersion() {
    unsigned int softVerLen = rand() % MAX_SOFT_VER_LEN;
    PlainMessageBuffer *softVer = new PlainMessageBuffer();
    for (unsigned int i = 0; i < softVerLen; i++) {
        softVer->push_back(rand() % 256);
    }
    return softVer;
}

PlainMessageBuffer *SSHVersionPacketGenerator::generateRandomComment() {
   unsigned int commentLen = rand() % MAX_COMMENT_LEN;
   PlainMessageBuffer *comment = new PlainMessageBuffer();
   for (unsigned int i = 0; i < commentLen; i++) {
       comment->push_back(rand() % 256);
   }
   return comment;
}

PlainMessageBuffer *SSHVersionPacketGenerator::generatePacket(MessageBuffer *prevOutput) {
    srand(time(NULL));
    if (getGenerateValid()) {
        return generateValidPacket();
    }
    else {
        return generateRandomPacket();
    }
}
