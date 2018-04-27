#include "MessageBuffer.h"

#ifndef PLAINMSGBUFF_H
#define PLAINMSGBUFF_H
class PlainMessageBuffer : public MessageBuffer {
    public: 
        PlainMessageBuffer();
        PlainMessageBuffer(const char *str);
        PlainMessageBuffer(unsigned char *str, unsigned int len);
        unsigned char* getProcessedMessage(unsigned int &msgLen);
};
#endif
