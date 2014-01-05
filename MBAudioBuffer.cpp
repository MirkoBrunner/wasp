

#include <MBAudioBuffer.h>

MBAudioBuffer::MBAudioBuffer()
{
	this->idx = 0;
	this->size = 0;
	this->sampleRate = 0;
	this->buffer = NULL;
}

//copy constuctor
MBAudioBuffer:MBAudioBuffer(const MBAudioBuffer& a)
{
	this->idx = a->idx;
	this->size = a->size;
	this->sampleRate = a->sampleRate;
	
	if(this->buffer!=NULL) 
		free(this->buffer);
		
	this->buffer = new int32[this->size];
	
	for(int i=0; i < this->size; ++i)
	{
		this->buffer[i] = a->buffer[i];
	}
}

MBAudioBuffer::MBAudioBuffer(int sz, int sRate)
: MBAudioBuffer()
{
	this->idx = 0;
	this->sampleRate = sRate;
	this->size = this->sampleRate;
	this->buffer = new int32[this->size];
	this->initZeroBuffer();
}

MBAudioBuffer::~MBAudioBuffer
{
	free(this->buffer);
}

MBAudioBuffer::initZeroBuffer()
{
	for(int i=0; i < this->size; ++i)
		this->buffer[i] = 0;
}

int32 MBAudioBuffer::convertFloatToLong(const float a)
{
	return (long)a * 100000000;
}

MBAudioBuffer::addData(const long& data)
{
	if((this->idx + 1) < this->size)
	{
		this->buffer[this->idx+1] = data;
		this->idx++;
	}
}

MBAudioBuffer::addData(const float& data)
{
	if((this->idx + 1) < this->size)
	{
		this->buffer[this->idx+1] = this->convertFloatToLong(data);
		this->idx++;
	}
}

M