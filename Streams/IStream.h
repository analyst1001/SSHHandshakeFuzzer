#include "Stream.h"
#include "../MessageBuffers/MessageBuffer.h"

#ifndef ISTREAM_H
#define ISTREAM_H
class IStream : public Stream {
    public:
        virtual MessageBuffer *read() = 0;
};
#endif
