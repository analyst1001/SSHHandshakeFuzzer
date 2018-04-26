#include "PacketGenerator.h"

MessageBuffer *PacketGenerator::generateInput(MessageBuffer *prevOutput) {
    return generatePacket(prevOutput);
}
