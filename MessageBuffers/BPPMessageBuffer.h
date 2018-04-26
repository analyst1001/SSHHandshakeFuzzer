#include "MessageBuffer.h"

#ifndef BPPMSGBUFF_H
#define BPPMSGBUFF_H
class BPPMessageBuffer : public MessageBuffer {
    public:
        BPPMessageBuffer();
        BPPMessageBuffer(const char *str);
        unsigned char* getProcessedMessage(unsigned int &msgLen);
};
#endif

