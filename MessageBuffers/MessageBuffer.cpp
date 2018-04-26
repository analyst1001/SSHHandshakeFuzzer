#include "MessageBuffer.h"
#include <cstring>
#include <cstdlib>

MessageBuffer::MessageBuffer() {
}

MessageBuffer::MessageBuffer(const char *str) {
    for (unsigned int i = 0; i < strlen(str); i++) {
        this->buffer.push_back((unsigned char)str[i]);
    }
}

void MessageBuffer::push_back(unsigned char chr) {
    this->buffer.push_back(chr);
}

void MessageBuffer::pop_back() {
    this->buffer.pop_back();
}

void MessageBuffer::append(const char *str) {
    for (unsigned int i = 0; i < strlen(str); i++) {
        this->buffer.push_back((unsigned char)str[i]);
    }
}


unsigned char* MessageBuffer::getMessage(unsigned int &msgLen) {
    msgLen = this->buffer.size();
    unsigned char *buff = (unsigned char *) calloc(msgLen, sizeof(unsigned char));
    unsigned int i = 0;
    for (vector<unsigned char>::iterator it = this->buffer.begin(); it != this->buffer.end(); ++it) {
        buff[i++] = *it;
    }
    return buff;
}

void MessageBuffer::append(string str) {
    for (unsigned int i = 0; i < str.size(); i++) {
        this->buffer.push_back((unsigned char)str[i]);
    }
}

void MessageBuffer::append(MessageBuffer *msg) {
    unsigned int msgLen = 0;
    unsigned char *msgBuff = msg->getMessage(msgLen);
    for (unsigned int i = 0; i < msgLen; i++) {
        this->buffer.push_back(msgBuff[i]);
    }
    free(msgBuff);
    msgBuff = 0;
    msgLen = 0;
}

void MessageBuffer::append(unsigned int val) {
    unsigned char *chr = (unsigned char *)&val;
    for (unsigned int i = 0; i < (sizeof(unsigned int)/sizeof(unsigned char)); i++, chr++) {
        this->buffer.push_back(*chr);
    }
}

unsigned int MessageBuffer::length() {
    return this->buffer.size();
}
