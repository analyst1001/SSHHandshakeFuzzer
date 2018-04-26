#include "../MessageBuffers/MessageBuffer.h"

#ifndef INPUTGEN_H
#define INPUTGEN_H
class InputGenerator {
    public:
        virtual MessageBuffer *generateInput(MessageBuffer *prevOutput) = 0;
};
#endif
