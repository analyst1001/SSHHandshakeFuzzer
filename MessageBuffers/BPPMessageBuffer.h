#include "MessageBuffer.h"

#ifndef BPPMSGBUFF_H
#define BPPMSGBUFF_H
class BPPMessageBuffer : public MessageBuffer {
    public:
        BPPMessageBuffer();
        BPPMessageBuffer(const char *str);
        BPPMessageBuffer(unsigned char *str, unsigned int len);
        unsigned char* getProcessedMessage(unsigned int &msgLen);
};
#endif

