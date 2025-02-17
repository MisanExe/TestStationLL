#include "ringbuffer.h"

RingBuffer::RingBuffer()
{
	write_ptr = read_ptr = 0;
}

void RingBuffer::write(char dat)
{
	_buffer[write_ptr] = dat;
	_increment(write_ptr);
}

char RingBuffer::read()
{
	if(_isEmpty())
	{
		return '\0';
	}

	char dat = _buffer[read_ptr];
	_increment(read_ptr);
	return dat;
}

bool RingBuffer::_isFull()
{
   return write_ptr == (read_ptr + 1) ? true : false; //correct for complete wrapping behavour
}
bool RingBuffer::_isEmpty()
{
   return write_ptr == read_ptr? true : false;
}

void RingBuffer::_increment(int &ptr)
{
   ptr = (ptr + 1) % bufferSize;
}

bool RingBuffer::bufferEmpty()
{
	return _isEmpty();
}

bool RingBuffer::bufferFull()
{
	return _isFull();
}
