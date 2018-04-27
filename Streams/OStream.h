#include "Stream.h"
#include "../MessageBuffers/MessageBuffer.h"

#ifndef OSTREAM_H
#define OSTREAM_H
class OStream : public Stream {
    public:
        virtual void write(MessageBuffer *) = 0;
};
#endif
