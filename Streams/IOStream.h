#include "IStream.h"
#include "OStream.h"

#ifndef IOSTREAM_H
#define IOSTREAM_H
class IOStream : public IStream, public OStream {
};
#endif
