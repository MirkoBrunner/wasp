

#include <MBAudioBuffer.h>
#include <assert.h>     /* assert */


MBAudioBuffer::MBAudioBuffer()
{
	this->size = 0;
	this->sampleRate = 0;
	this->buffer = NULL;
}

//copy constuctor
MBAudioBuffer:MBAudioBuffer(const MBAudioBuffer& a)
{
	this->size = a->size;
	this->sampleRate = a->sampleRate;
	
	if(this->buffer!=NULL) 
		free(this->buffer);
		
	this->buffer = new double[this->size];
	
	for(int i=0; i < this->size; i++)
	{
		this->buffer[i] = a->buffer[i];
	}
}

MBAudioBuffer::MBAudioBuffer(int sz, int sRate)
: MBAudioBuffer()
{
	this->sampleRate = sRate;
	this->size = this->sampleRate;
	this->buffer = new double[this->size];
	this->initBufferWithZero();
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

void MBAudioBuffer::initBufferWithZero()
{
	for(int i=0; i < this->size; ++i)
		this->buffer[i] = 0;
}

long MBAudioBuffer::convertFloatToLong(const float a)
{
	return (long)a * 100000000;
}

void MBAudioBuffer::addData(const double& data)
{		
	this->buffer[0] = data;
	
	//array shift
	for(int i = 1; i != this->size-1; i++)
		this->buffer[i] = this->buffer[i+1];
}

