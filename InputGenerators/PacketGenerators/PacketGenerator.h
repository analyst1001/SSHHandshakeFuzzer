#include "../ValidInvalidInputGenerator.h"

#ifndef PGEN_H
#define PGEN_H
class PacketGenerator : public ValidInvalidInputGenerator{
    public:
        virtual MessageBuffer *generatePacket(MessageBuffer *prevOutput) = 0;
        MessageBuffer *generateInput(MessageBuffer *prevOutput);
};
#endif
