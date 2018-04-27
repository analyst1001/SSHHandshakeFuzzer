#include "PlainMessageBuffer.h"
#include <cstdlib>
#include <cstring>

unsigned char* PlainMessageBuffer::getProcessedMessage(unsigned int &msgLen) {
    return this->getMessage(msgLen);
}

PlainMessageBuffer::PlainMessageBuffer() {
}

PlainMessageBuffer::PlainMessageBuffer(const char *str) {
    for (unsigned int i = 0; i < strlen(str); i++) {
        this->buffer.push_back((unsigned char)str[i]);
    }
}

PlainMessageBuffer::PlainMessageBuffer(unsigned char *str, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        this->buffer.push_back((unsigned char)str[i]);
    }
}
