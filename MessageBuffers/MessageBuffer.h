#include <vector>
#include <string>

using namespace std;

#ifndef MSGBUF_H
#define MSGBUF_H
class MessageBuffer {
    protected:

    public:
        vector<unsigned char> buffer;
        MessageBuffer();
        MessageBuffer(const char *str);
        MessageBuffer(unsigned char *str, unsigned int len);
        void push_back(unsigned char chr);
        void pop_back();
        void append(const char *str);
        void append(MessageBuffer *msg);
        void append(string str);
        void append(unsigned int val);
        unsigned char* getMessage(unsigned int &msgLen);
        unsigned int length();
        virtual unsigned char *getProcessedMessage(unsigned int &msgLen) = 0;
};
#endif
