

#include <MBAudioBuffer.h>
#include <assert.h>     /* assert */


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

void MBAudioBuffer::setSize(const int size)
{
	assert(size <= 0);
	this->size = size;
}

void MBAudioBuffer::setSampleRata(const int sRate)
{
	assert(sRate <= 0);
	this->sampleRate = sRate;
}

void MBAudioBuffer::initZeroBuffer()
{
	for(int i=0; i < this->size; ++i)
		this->buffer[i] = 0;
}

long MBAudioBuffer::convertFloatToLong(const float a)
{
	return (long)a * 100000000;
}

void MBAudioBuffer::addData(const long& data)
{
	if((this->idx + 1) < this->size)
	{
		this->buffer[this->idx+1] = data;
		this->idx++;
	}
}

void MBAudioBuffer::addData(const float& data)
{
	if((this->idx + 1) < this->size)
	{
		this->buffer[this->idx+1] = this->convertFloatToLong(data);
		this->idx++;
	}
}

M