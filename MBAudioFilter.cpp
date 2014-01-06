

#include <MBAudioFilter.h>

#define M_PI 3.14159265359


MBAudioFilter::MBAudioFilter()
{
	this->sampleRate = 0;
	this->a = this->b = this->c = NULL;
}

//clean up hurrrrey ;)
MBaudioFilter::~MBAudioFilter()
{
	delete this->buffer;
}

void MBAudioFilter::build(const int bufferSize)
{
	this->miniBuffer = new double[bufferSize];
}

void resetTemps(const int size)
{
	if(this->temps != NULL)
		free(this->temps);
		
	this->temps = new double[size];
}

long MBAudioFilter::simpleLowPass(const double data)
{
	long y;
	this->miniBuffer[0] = data;
	y = this->miniBuffer[1] + this->cutOff * (this->miniBuffer[0] - this->miniBuffer[1]);
	this->miniBuffer[1] = this->miniBuffer[0];
}

void MBAudioFilter::initLowPassResonance()
{
	this->resetTemps(3);
	this->temps[0] = 2 - 2 * cos(2 * M_PI * this->resonance / this->sampleRate);
	this->temps[1] = 0;
	this->temps[2] = 0;
}

double MBAudioFilter::lowPassResonance(const double data)
{
	assert(this->temps[0] == NULL);
	this->temps[1] += (data - this->temps[2]) * this->temps[0];
    this->temps[2] += this->temps[1]
    this->temps[1] *= this->resonance;
    return this->temps[2];
}

void MBAudioFilter::initNotch()
{
	this->resetTemps(5);
	this->temps[0] = cos(2 * M_PI * this->cutOff / this->samplRate);
	this->temps[1] = pow((1 - this->resonance), 2) / (2 * (this->temps[0] + 1)) + this->resonance;
	this->temps[2] = -2 * this->temps[0] * this->temps[1];
	this->temps[3] = 2 * this->temps[0] * this->resonance;
	this->temps[4] = -this->resonance * this->resonance;
}

double MBAudioFilter::notch(const double& data)
{
	long y;
	this->miniBuffer[0] = data;

}


