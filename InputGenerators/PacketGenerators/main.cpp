#include <iostream>
#include "SSHVersionPGen.h"

int main() {
    PacketGenerator *verPG = new SSHVersionPacketGenerator();
    MessageBuffer *packet = verPG->generatePacket(NULL);
    unsigned int msgLen = 0;
    cout<<packet->getMessage(msgLen);
    delete packet;
    return 0;
}
