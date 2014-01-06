

#include <MBAudioFilter.h>
#include <math.h> 

#define M_PI 3.14159265359


MBAudioFilter::MBAudioFilter()
{
	this->filterType = -1;
	this->sampleRate = 0;
	this->a = this->b = this->c = NULL;
}

//clean up hurrrrey ;)
MBaudioFilter::~MBAudioFilter()
{
	delete this->buffer;
}

MBAudioBuffer:MBAudioBuffer(const MBAudioBuffer& a)
{
	this->cutOff = a->cutOff;
	this->resonance = a->resonance;
	this->filterType = a->filterType
	int c;
	
	if(a->temps != NULL){
	
		c = sizeof(a->temps) / sizeof(double);
		
		this->resetTemps[c];
		
		for(int i=0;i<c;i++)
			this->temps[i] = a->temps[i];
	}
	
	if(a->miniBuffer != NULL){
	
		c = sizeof(a->miniBuffer) / sizeof(double);
		
		this->resetMiniBuffer[c];
		
		for(int i=0;i<c;i++)
			this->temps[i] = a->temps[i];
	}
	
	free(c);
}

void MBAudioFilter::build(const int bufferSize)
{
	this->miniBuffer = new double[bufferSize];
}

void MBAudioFilter::resetTemps(const int size)
{	
	if(size == 0){
		free(this->temps);
		return;
	}
	
	if(this->temps != NULL)
		free(this->temps);
		
	this->temps = new double[size];
}

void MBAudioFilter::resetMiniBuffer(const int size)
{
	if(size == 0){
		free(this->miniBuffer);
		return;
	}
	
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
	this->filterType = 1;
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
	this->filterType = 2;
	this->resetTemps[5];
	this->resetMiniBuffer[1];
	
	this->temps[0] = cos(2 * M_PI * this->resonance / this->sampleRate);
	this->temps[1] = 2-2*this->temps[0];

	//r
	double a = pow(-(this->temps[0]-1));
	double b = a + amp*this->temps[0];
	double c = (amp * (this->temps[0]-1);
	
	this->temps[2] = (sqrt(2)*sqrt(b)) / c;
	this->temps[3] = 0;
	this->temps[4] = 0;
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
	this->filterType = 3;
	this->resetTemps(6);
	this->resetMiniBuffer(6);

	this->temps[0] = cos(2 * M_PI * this->cutOff / this->samplRate);
	this->temps[1] = pow((1 - this->resonance), 2) / (2 * (this->temps[0] + 1)) + this->resonance;
	this->temps[2] = -2 * this->temps[0] * this->temps[1];
	this->temps[3] = 2 * this->temps[0] * this->resonance;
	this->temps[4] = -this->resonance * this->resonance;
	this->temps[5] = 0;
}

void MBAudioFilter::initSinpleHighPass()
{
	this->resetMiniBuffer(2);
}


void MBAudioFilter::simpleHighPass(const double& data)
{
	this->miniBuffer[0] = data - (this->miniBuffer[1] + this->cutOff * (data - this->miniBuffer[1]));
	this->miniBuffer[1] = this->miniBuffer[0];
	return this->miniBuffer[0];
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

void MBAudioFilter::initFBandPass()
{
	this->filterType = 4;
	this->resetTemps(4);
	this->resetMiniBuffer(3);
	
	this->temps[0] = cos(2 * M_PI * this->cutOff / this->samplRate);
	this->temps[1] = (1 - this->resonance)*sqrt(this->resonance*(this->resonance-4*pow(this->temps[0],2)+2)+1);
	this->temps[2] = 2 * this->temps[0] * this->resonace;
	this->temps[3] = pow(-this->resonace,2);
	this->temps[4] = 0;
}

double MBAudioFilter::fBandPass(const double& data)
{
	this->miniBuffer[0] = data;
	this->temps[4] = this->temps[1] * this->miniBuffer[0] + this->temps[2] * this->miniBuffer[1] + this->temps[3] * this->miniBuffer[2];
	
	this->miniBuffer[2] = this->miniBuffer[1];
	this->miniBuffer[1] = this->miniBuffer[0];
	
	return this->temps[4];
}

void MBAudioFilter::initDCRemoval()
{
	this->resetTemps[2];
	this->temps[0] = this->temps[1] = this->temps[2] = 0;
}

double MBAudioFilter::dCRemoval(const double& data)
{
	this->temps[2] = data - this->temps[1];
	this->temps[0] = this->temps[0] + (data - this->temps[1]) * 0.000004567;
	this->temps[1] = this->temps[1] + this->temps[0];
	this->temps[0] = this->temps[0] * 0.96;
	return (data - this->temps[1]);
}









