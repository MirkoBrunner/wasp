

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

void MBAudioFilter::resetTemps(const int size)
{
	if(this->temps != NULL)
		free(this->temps);
		
	this->temps = new double[size];
}

void MBAudioFilter::resetMiniBuffer(const int size)
{
	if(this->miniBuffer != NULL)
		free(this->miniBuffer);
		
	this->miniBuffer = new double[size];
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

void MBAudioFilter::initLowPassResonance2(const double amp)
{
	this->resetTemps[5];
	this->resetMiniBuffer[1];
	
	this->temps[0] = cos(2 * M_PI * this->resonance / this->sampleRate);
	this->temps[1] = 2-2*this->temps[0];
	
	//r
	double a = pow(-(this->temps[0]-1));
	double b = a + amp*this->temps[0];
	double c = (amp * (this->temps[0]-1);
	
	this->temps[2] = (sqrt(2)*sqrt(b)) / c;
	this->temps[3] = 0;	//p
	this->temps[4] = 0;	//s
}

double MBAudioFilter::lowPassResonance2(const double& data)
{
	this->temps[4] = this->temps[4] + (data - this->this->temps[3]) * this->temps[2];
	this->temps[3] = this->temps[3] + this->temps[4];
	this->temps[4] = this->temps[4] * this->temps[2];
	
	return this->temps[3];
}

void MBAudioFilter::initNotch()
{
	this->resetTemps(6);
	this->resetMiniBuffer(6);

	this->temps[0] = cos(2 * M_PI * this->cutOff / this->samplRate);
	this->temps[1] = pow((1 - this->resonance), 2) / (2 * (this->temps[0] + 1)) + this->resonance;
	this->temps[2] = -2 * this->temps[0] * this->temps[1];
	this->temps[3] = 2 * this->temps[0] * this->resonance;
	this->temps[4] = -this->resonance * this->resonance;
	this->temps[5] = 0;
}

double MBAudioFilter::notch(const double& data)
{
	//input buffer 3 sample
	this->miniBuffer[2] = this->miniBuffer[1];
	this->miniBuffer[1] = this->miniBuffer[0];
	this->miniBuffer[0] = data;
	
	this->temps[5] = this->temps[1] * (this->miniBuffer[0] + this->miniBuffer[2]) + this->temps[2] * this->miniBuffer[1] + this->temps[3] * this->miniBuffer[4] + this->temps[4] * this->miniBuffer[5];
	
	//output buffer 3 sample
	this->miniBuffer[5] = this->miniBuffer[4];
	this->miniBuffer[4] = this->miniBuffer[3];
	this->miniBuffer[3] = this->temps[5];
	
	return this->temps[5];
}




