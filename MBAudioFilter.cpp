

#include <MBAudioFilter.h>

MBAudioFilter::MBAudioFilter()
{
	this->sampleRate = 0;
}

//clean up hurrrrey ;)
MBaudioFilter::~MBAudioFilter()
{
	delete this->buffer;
}

void MBAudioFilter::configureFilter(const int sRate, const int size)
{
	this->sampleRate = sRate;
	
	if(this->buffer != NULL)
		delete this->buffer;
	
	//erstmal nur den mini buffer nutzen
	this->miniBuffer = new long[size];
}

long MBAudioFilter::simpleLowPass(const long data, const long& cutoff)
{
	long y;
	this->miniBuffer[0] = data;
	y = this->miniBuffer[1] + cutOff * (this->miniBuffer[0] - this->miniBuffer[1]);
	this->miniBuffer[1] = this->miniBuffer[0];
}