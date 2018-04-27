#ifndef STREAM_H
#define STREAM_H
class Stream {
    public:
        virtual void openStream() = 0;
        virtual void closeStream() = 0;
};
#endif
