#include "BPPMessageBuffer.h"
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <cstdio>


unsigned char* BPPMessageBuffer::getProcessedMessage(unsigned int &msgLen) {
    msgLen = this->buffer.size();
    unsigned int modulo8 = (sizeof(unsigned int) + sizeof(unsigned char) + msgLen) % 8;
    // add padding to make it a multiple of 8
    unsigned char paddingLen = (8 - modulo8) + 8 * (rand() % 30);
    printf("Padding len %x\n", paddingLen);
    unsigned int totalPacketLength = sizeof(unsigned int) + sizeof(unsigned char) + msgLen + paddingLen;
    unsigned int packetLength = sizeof(unsigned char) + msgLen + paddingLen;
    printf("Pkt len %x\n", packetLength);
    unsigned char *buff = (unsigned char *) calloc(totalPacketLength, sizeof(unsigned char));
    unsigned int i = 0;
    unsigned int npacketLength = htonl(packetLength);
    memcpy(buff, &npacketLength, sizeof(unsigned int));
    memcpy(buff + sizeof(unsigned int), &paddingLen, sizeof(unsigned char));
    i += sizeof(unsigned int) + sizeof(unsigned char);
    for (vector<unsigned char>::iterator it = this->buffer.begin(); it != this->buffer.end(); ++it) {
        printf("%x ", *it);
        buff[i++] = *it;
    }
    printf("\n");
    for (unsigned int j = 0; j < paddingLen; j++) {
        buff[i++] = rand() % 256;
    }
    msgLen = totalPacketLength;
    return buff;
}

BPPMessageBuffer::BPPMessageBuffer() {
}

BPPMessageBuffer::BPPMessageBuffer(const char *str) {
    for (unsigned int i = 0; i < strlen(str); i++) {
        this->buffer.push_back((unsigned char)str[i]);
    }
}

BPPMessageBuffer::BPPMessageBuffer(unsigned char *str, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        this->buffer.push_back((unsigned char)str[i]);
    }
}
