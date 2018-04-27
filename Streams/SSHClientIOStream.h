#include "TCPClientNetworkIOStream.h"
#include "../MessageBuffers/BPPMessageBuffer.h"
#include <netinet/in.h>

#ifndef SSHCLIIOSTREAM_H
#define SSHCLIIOSTREAM_H

#define INVALID_FD -1
#define MAX_TCP_PKT_LEN 65536
class SSHClientIOStream : public TCPClientNetworkIOStream {
    private:
        int sockfd;
        struct sockaddr_in *srvAddr;

    public:
        SSHClientIOStream();
        ~SSHClientIOStream();
        void openStream();
        void closeStream();
        BPPMessageBuffer *read();
        void write(MessageBuffer *);
        void setSSHServerAddr(const char *srvIPAddr);
        char *getSSHServerAddr();
        void setSSHServerPort(unsigned short port);
        unsigned short getSSHServerPort();

};
#endif
