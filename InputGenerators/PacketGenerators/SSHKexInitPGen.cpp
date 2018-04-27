#include "SSHKexInitPGen.h"
#include "../../MessageBuffers/BPPMessageBuffer.h"
#include <iostream>
#include <cstdio>
#include <arpa/inet.h>

SSHKexInitPacketGenerator::SSHKexInitPacketGenerator() {
    string kexAlgo1("curve25519-sha256");
    this->kexAlgoList.push_back(kexAlgo1);//,"curve25619-sha256@libssh.org","ecdh-sha2-nistp521","ecdh-sha2-nistp384","ecdh-sha2-nistp256","diffie-hellman-group14-sha256","diffie-hellman-group14-sha1","diffie-hellman-group1-sha1","kexguess2@matt.ucc.asn.au"];

    string srvHostKeyAlgo1("ecdsa-sha2-nistp256");
    this->srvHostKeyAlgoList.push_back(srvHostKeyAlgo1);//,"ecdsa-sha2-nistp384","ecdsa-sha2-nistp521","ssh-rsa","ssh-dss"];

    string encAlgo1("aes128-ctr");
    this->encAlgoList.push_back(encAlgo1);//,"aes256-ctr","aes128-cbc","aes256-cbc","3des-ctr","3des-cbc"];

    string macAlgo1("hmac-sha1-96");
    this->macAlgoList.push_back(macAlgo1);//,"hmac-sha1","hmac-sha2-256"];

    string compAlgo1("zlib@openssh.com");
    this->compAlgoList.push_back(compAlgo1);
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateCookie() {
    BPPMessageBuffer *cookie = new BPPMessageBuffer();
    for (unsigned int i = 0; i < COOKIE_LEN; i++) {
        cookie->push_back(rand() % 256);
    }
    return cookie;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateRandomAlgorithmName() {
    BPPMessageBuffer *algoName = new BPPMessageBuffer();
    unsigned int algoNameLen = rand() % MAX_ALGO_NAME_LEN;
    for (unsigned int i = 0; i < algoNameLen; i++) {
        algoName->push_back(rand() % 256);
    }
    return algoName;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateRandomAlgorithmList() {
    BPPMessageBuffer *algoList = new BPPMessageBuffer();
    unsigned int listLen = rand() % MAX_ALGO_LIST_LEN;
    for (unsigned int i = 0; i < listLen; i++) {

        BPPMessageBuffer *algoName = generateRandomAlgorithmName();
        algoList->append(algoName);
        cout<<"algolist length "<<algoList->length()<<endl;
        delete algoName;

        algoList->push_back(ALGO_NAME_SEP);
    }
    if (algoList->length() > 0) {
        algoList->pop_back();
    }
    return algoList;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateKexGuessFollows() {
    BPPMessageBuffer *guessFollows = new BPPMessageBuffer();
    guessFollows->push_back(rand() % 2);
    return guessFollows;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateRandomReserved() {
    BPPMessageBuffer *reserved = new BPPMessageBuffer();
    for (unsigned int i = 0; i < 4; i++) {
        reserved->push_back(rand() % 256);
    }
    return reserved;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateRandomPacketType() {
    BPPMessageBuffer *packetType = new BPPMessageBuffer();
    if (rand() % 2) {
        packetType->push_back(20);
    }
    else {
        packetType->push_back(rand() % 256);
    }
    return packetType;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generatePacket(MessageBuffer *prevOutput) {
    srand(time(NULL));
    if (getGenerateValid()) {
        return generateValidPacket();
    }
    else {
        return generateRandomPacket();
    }
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateRandomPacket() {

    bool correctLengths = (rand() % 2 == 0);

    BPPMessageBuffer *packet = new BPPMessageBuffer();

    BPPMessageBuffer *pktType = generateRandomPacketType();
    packet->append(pktType);
    delete pktType;

    BPPMessageBuffer *cookie = generateCookie();
    packet->append(cookie);
    delete cookie;

    BPPMessageBuffer *kexAlgoList = generateRandomAlgorithmList();
    unsigned int kexAlgoListLen = correctLengths == true ? kexAlgoList->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(kexAlgoListLen);
    packet->append(kexAlgoList);
    delete kexAlgoList;

    BPPMessageBuffer *srvHostKeyAlgoList = generateRandomAlgorithmList();
    unsigned int srvHostKeyAlgoListLen = correctLengths == true ? srvHostKeyAlgoList->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(srvHostKeyAlgoListLen);
    packet->append(srvHostKeyAlgoList);
    delete srvHostKeyAlgoList;
    
    BPPMessageBuffer *encAlgoListCS = generateRandomAlgorithmList();
    unsigned int encAlgoListCSLen = correctLengths == true ? encAlgoListCS->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(encAlgoListCSLen);
    packet->append(encAlgoListCS);
    delete encAlgoListCS;

    BPPMessageBuffer *encAlgoListSC = generateRandomAlgorithmList();
    unsigned int encAlgoListSCLen = correctLengths == true ? encAlgoListSC->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(encAlgoListSCLen);
    packet->append(encAlgoListSC);
    delete encAlgoListSC;


    BPPMessageBuffer *macAlgoListCS = generateRandomAlgorithmList();
    unsigned int macAlgoListCSLen = correctLengths == true ? macAlgoListCS->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(macAlgoListCSLen);
    packet->append(macAlgoListCS);
    delete macAlgoListCS;

    BPPMessageBuffer *macAlgoListSC = generateRandomAlgorithmList();
    unsigned int macAlgoListSCLen = correctLengths == true ? macAlgoListSC->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(macAlgoListSCLen);
    packet->append(macAlgoListSC);
    delete macAlgoListSC;

    BPPMessageBuffer *compAlgoListCS = generateRandomAlgorithmList();
    unsigned int compAlgoListCSLen = correctLengths == true ? compAlgoListCS->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(compAlgoListCSLen);
    packet->append(compAlgoListCS);
    delete compAlgoListCS;

    BPPMessageBuffer *compAlgoListSC = generateRandomAlgorithmList();
    unsigned int compAlgoListSCLen = correctLengths == true ? compAlgoListSC->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(compAlgoListSCLen);
    packet->append(compAlgoListSC);
    delete compAlgoListSC;

    BPPMessageBuffer *langListCS = generateRandomAlgorithmList();
    unsigned int langListCSLen = correctLengths == true ? langListCS->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(langListCSLen);
    packet->append(langListCS);
    delete langListCS;

    BPPMessageBuffer *langListSC = generateRandomAlgorithmList();
    unsigned int langListSCLen = correctLengths == true ? langListSC->length() : (rand() % (MAX_ALGO_LIST_LEN * MAX_ALGO_NAME_LEN));
    packet->append(langListSCLen);
    packet->append(langListSC);
    delete langListSC;

    BPPMessageBuffer *kexguess = generateKexGuessFollows();
    packet->append(kexguess);
    delete kexguess;

    BPPMessageBuffer *reserved = generateRandomReserved();
    packet->append(reserved);

    return packet;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateValidPacketType() {
    BPPMessageBuffer *pktType = new BPPMessageBuffer();
    pktType->push_back(20);
    return pktType;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateValidAlgorithmList(unsigned int algoType) {
    unsigned int algoListLen = 0;
    BPPMessageBuffer *algoList = new BPPMessageBuffer();
    switch (algoType) {
        case KEX:
            algoListLen = 1 + (rand() % this->kexAlgoList.size());
            for (unsigned int i = 0; i < algoListLen; i++) {
                algoList->append(this->kexAlgoList[rand() % this->kexAlgoList.size()]);
                algoList->push_back(',');
            }
            algoList->pop_back();
            return algoList;
        case SRV_HOST_KEY:
            algoListLen = 1 + (rand() % this->srvHostKeyAlgoList.size());
            for (unsigned int i = 0; i < algoListLen; i++) {
                algoList->append(this->srvHostKeyAlgoList[rand() % this->srvHostKeyAlgoList.size()]);
                algoList->push_back(',');
            }
            algoList->pop_back();
            return algoList;
        case ENCRYPTION:
            algoListLen = 1 + (rand() % this->encAlgoList.size());
            for (unsigned int i = 0; i < algoListLen; i++) {
                algoList->append(this->encAlgoList[rand() % this->encAlgoList.size()]);
                algoList->push_back(',');
            }
            algoList->pop_back();
            return algoList;
        case MAC:
            algoListLen = 1 + (rand() % this->macAlgoList.size());
            for (unsigned int i = 0; i < algoListLen; i++) {
                algoList->append(this->macAlgoList[rand() % this->macAlgoList.size()]);
                algoList->push_back(',');
            }
            algoList->pop_back();
            return algoList;
        case COMPRESSION:
            algoListLen = 1 + (rand() % this->compAlgoList.size());
            for (unsigned int i = 0; i < algoListLen; i++) {
                algoList->append(this->compAlgoList[rand() % this->compAlgoList.size()]);
                algoList->push_back(',');
            }
            algoList->pop_back();
            return algoList;
    }
    return algoList;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateValidReserved() {
    BPPMessageBuffer *reserved = new BPPMessageBuffer();
    for (unsigned int i = 0; i < 4; i++) {
        reserved->push_back(0);
    }
    return reserved;
}

BPPMessageBuffer *SSHKexInitPacketGenerator::generateValidPacket() {
    BPPMessageBuffer *packet = new BPPMessageBuffer();

    cout<<"Generating Valid packeT"<<endl;
    for (vector<unsigned char>::iterator it = packet->buffer.begin(); it != packet->buffer.end(); it++) {
        printf("%x ", *it);
    }
    printf("\n");

    BPPMessageBuffer *pktType = generateValidPacketType();
    packet->append(pktType);
    delete pktType;
    for (vector<unsigned char>::iterator it = packet->buffer.begin(); it != packet->buffer.end(); it++) {
        printf("%x ", *it);
    }
    printf("\n");

    BPPMessageBuffer *cookie = generateCookie();
    packet->append(cookie);
    delete cookie;
    for (vector<unsigned char>::iterator it = packet->buffer.begin(); it != packet->buffer.end(); it++) {
        printf("%x ", *it);
    }
    printf("\n");
    
    BPPMessageBuffer *kexAlgoList = generateValidAlgorithmList(KEX);
    unsigned int kexAlgoListLen = kexAlgoList->length();
    packet->append(htonl(kexAlgoListLen));
    packet->append(kexAlgoList);
    delete kexAlgoList;
    for (vector<unsigned char>::iterator it = packet->buffer.begin(); it != packet->buffer.end(); it++) {
        printf("%x ", *it);
    }
    printf("\n");

    BPPMessageBuffer *srvHostKeyAlgoList = generateValidAlgorithmList(SRV_HOST_KEY);
    unsigned int srvHostKeyAlgoListLen = srvHostKeyAlgoList->length();
    packet->append(htonl(srvHostKeyAlgoListLen));
    packet->append(srvHostKeyAlgoList);
    delete srvHostKeyAlgoList;
    for (vector<unsigned char>::iterator it = packet->buffer.begin(); it != packet->buffer.end(); it++) {
        printf("%x ", *it);
    }
    printf("\n");

    BPPMessageBuffer *encAlgoListCS = generateValidAlgorithmList(ENCRYPTION);
    unsigned int encAlgoListCSLen = encAlgoListCS->length();
    packet->append(htonl(encAlgoListCSLen));
    packet->append(encAlgoListCS);
    delete encAlgoListCS;

    BPPMessageBuffer *encAlgoListSC = generateValidAlgorithmList(ENCRYPTION);
    unsigned int encAlgoListSCLen = encAlgoListSC->length();
    packet->append(htonl(encAlgoListSCLen));
    packet->append(encAlgoListSC);
    delete encAlgoListSC;
    
    BPPMessageBuffer *macAlgoListCS = generateValidAlgorithmList(MAC);
    unsigned int macAlgoListCSLen = macAlgoListCS->length();
    packet->append(htonl(macAlgoListCSLen));
    packet->append(macAlgoListCS);
    delete macAlgoListCS;

    BPPMessageBuffer *macAlgoListSC = generateValidAlgorithmList(MAC);
    unsigned int macAlgoListSCLen = macAlgoListSC->length();
    packet->append(htonl(macAlgoListSCLen));
    packet->append(macAlgoListSC);
    delete macAlgoListSC;
    
    BPPMessageBuffer *compAlgoListCS = generateValidAlgorithmList(COMPRESSION);
    unsigned int compAlgoListCSLen = compAlgoListCS->length();
    packet->append(htonl(compAlgoListCSLen));
    packet->append(compAlgoListCS);
    delete compAlgoListCS;

    BPPMessageBuffer *compAlgoListSC = generateValidAlgorithmList(COMPRESSION);
    unsigned int compAlgoListSCLen = compAlgoListSC->length();
    packet->append(htonl(compAlgoListSCLen));
    packet->append(compAlgoListSC);
    delete compAlgoListSC;

    
    unsigned int langListCSLen = 0;
    packet->append(htonl(langListCSLen));

    unsigned int langListSCLen = 0;
    packet->append(htonl(langListSCLen));

    // we will not send kex guess message for valid case
    packet->push_back(0);

    BPPMessageBuffer *reserved = generateValidReserved();
    packet->append(reserved);
    delete reserved;

    for (vector<unsigned char>::iterator it = packet->buffer.begin(); it != packet->buffer.end(); it++) {
        printf("%x ", *it);
    }
    printf("\n");

    return packet;
}
