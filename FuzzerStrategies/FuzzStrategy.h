#include "../MessageBuffers/MessageBuffer.h"

#ifndef FUZZSTRATEGY_H
#define FUZZSTRATEGY_H
class FuzzStrategy {
    public:
        virtual void applyStrategy() = 0;
};
#endif
