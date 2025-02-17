#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_


class RingBuffer
{
    public:

        RingBuffer();
        void write(char dat);
        char read();
        bool bufferEmpty();
        bool bufferFull();

    private :
        int read_ptr;
        int write_ptr;
        static const int bufferSize = 256;
        char _buffer [bufferSize];

        bool _isFull();
        bool _isEmpty();
        void _increment(int &ptr);

};
#endif
