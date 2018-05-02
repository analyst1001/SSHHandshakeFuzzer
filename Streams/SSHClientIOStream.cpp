#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <arpa/inet.h>
#include "SSHClientIOStream.h"

SSHClientIOStream::SSHClientIOStream() {
    this->sockfd = INVALID_FD;
    this->srvAddr = (struct sockaddr_in *) calloc(1, sizeof(struct sockaddr_in));
    this->srvAddr->sin_family = AF_INET;
}

SSHClientIOStream::~SSHClientIOStream() {
    if (this->sockfd != INVALID_FD) {
        closeStream();
    	this->sockfd = INVALID_FD;
    }
    if (this->srvAddr) {
        free(this->srvAddr);
    }
}

void SSHClientIOStream::setSSHServerPort(unsigned short port) {
    this->srvAddr->sin_port = htons(port);
}

unsigned short SSHClientIOStream::getSSHServerPort() {
    return ntohs(this->srvAddr->sin_port);
}

void SSHClientIOStream::setSSHServerAddr(const char *srvIPAddr) {
    if (inet_aton(srvIPAddr, &(this->srvAddr->sin_addr)) < 0) {
        perror("inet_aton");
        throw "Error converting IP address to byte format in SSH client stream";
    }
}

char *SSHClientIOStream::getSSHServerAddr() {
    return inet_ntoa(this->srvAddr->sin_addr);
}

void SSHClientIOStream::openStream() {
    if ((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        throw "Error creating socket for SSH client connection";
    }
    if (connect(this->sockfd, (struct sockaddr *)this->srvAddr, sizeof(struct sockaddr)) < 0) {
        perror("connect");
        throw "Error while connecting SSH Client to SSH server";
    }
}

void SSHClientIOStream::write(MessageBuffer *msg) {
    unsigned int msgLen = 0;
    unsigned char *msgBuff = msg->getProcessedMessage(msgLen);
    if (send(this->sockfd, msgBuff, msgLen, 0) < 0) {
        perror("send");
        throw "Error sending data in SSH client stream";
    }
} 

BPPMessageBuffer *SSHClientIOStream::read() {
    unsigned char msgBuff[MAX_TCP_PKT_LEN] = {0};
    unsigned int msgLen = 0;
    if (msgLen = recv(this->sockfd, msgBuff, MAX_TCP_PKT_LEN, 0) < 0) {
        perror("recv");
        throw "Error receiving data in SSH client stream";
    }

    return new BPPMessageBuffer(msgBuff, msgLen);
}

void SSHClientIOStream::closeStream() {
    close((int)this->sockfd);
}
