

#include "MBAudioFilter.h"
#include <math.h>
#include <stdio.h>

using namespace std;

MBAudioFilter::MBAudioFilter()
{
	this->filterType = -1;
	this->cutOff = 0;
	this->resonance = 0;
    
    this->a1 = 0;
    this->a2 = 0;
}

//clean up hurrrrey ;)
MBAudioFilter::~MBAudioFilter()
{
    this->miniBuffer = new float[6];
    this->temps = new float[6];
    
}

MBAudioFilter::MBAudioFilter(const MBAudioFilter& a)
{
	this->cutOff = a.cutOff;
	this->resonance = a.resonance;
	this->filterType = a.filterType;
	int c;
	
	if(a.temps != nullptr){
        
		c = sizeof(a.temps) / sizeof(float);
		
		//this->resetTemps[c];
		
		for(int i=0;i<c;i++)
			this->temps[i] = a.temps[i];
	}
	
	if(a.miniBuffer != nullptr){
        
		c = sizeof(a.miniBuffer) / sizeof(float);
		
		this->resetMiniBuffer(c);
		
		for(int i=0;i<c;i++)
			this->temps[i] = a.temps[i];
	}

}

void MBAudioFilter::build(const int bufferSize)
{
	this->miniBuffer = new float[bufferSize];
}

void MBAudioFilter::resetTemps(const int size)
{
	if(size == 0){
//		free(this->temps);
		return;
	}
	
    //	if(this->temps != NULL)
    //		free(this->temps);
    
	this->temps = new float[size];
    
    for(int i=0;i<size;i++)
        this->temps[i] = 0.0;
}

void MBAudioFilter::resetMiniBuffer(const int size)
{
	if(size == 0){
        //	free(this->miniBuffer);
		return;
	}
	
	//if(this->miniBuffer != NULL)
	//	free(this->miniBuffer);
    
	this->miniBuffer = new float[size];
    
    for(int i=0;i<size;i++)
        this->miniBuffer[i] = 0.0;
}

float MBAudioFilter::simpleLowPass(float data)
{
    float y;
	this->a1 = data;
	y = this->a2 + this->cutOff * (this->a1 - this->a2);
	this->a2 = this->a1;
    
   
    return y;
}

void MBAudioFilter::initLowPassResonance()
{
	this->filterType = 1;
	this->resetTemps(3);
	this->temps[0] = 2 - 2 * cos(2 * M_PI * this->resonance / this->sampleRate);
	this->temps[1] = 0;
	this->temps[2] = 0;
}


float MBAudioFilter::lowPassResonance(float data)
{
	this->temps[1] += (data - this->temps[2]) * this->temps[0];
    this->temps[2] += this->temps[1];
    this->temps[1] *= this->resonance;
    return this->temps[2];
}

void MBAudioFilter::initLowPassResonance2(float amp)
{
	this->filterType = 2;
	this->resetTemps(5);
	this->resetMiniBuffer(1);
	
	this->temps[0] = cos(((2 * M_PI) * this->resonance) / this->sampleRate);
	this->temps[1] = 2-2*this->temps[0];
    
    
    printf("0 %f\n",this->temps[0]);
    printf("1 %f\n",this->temps[0]);
    
	//r
	float a = pow(-(this->temps[0]-1),2);
	float b = a + amp*this->temps[0];
	float c = amp * (this->temps[0]);
	
	this->temps[2] = (sqrt(2)*sqrt(b)) / c;
	this->temps[3] = 0;
	this->temps[4] = 0;
    
    printf("a %f\n",a);
    printf("b %f\n",b);
    printf("c %f\n",c);
}

float MBAudioFilter::lowPassResonance2(float data)
{
	this->temps[4] = this->temps[4] + (data - this->temps[3]) * this->temps[2];
	this->temps[3] = this->temps[3] + this->temps[4];
	this->temps[4] = this->temps[4] * this->temps[2];
    
	return this->temps[3];
}


void MBAudioFilter::initSinpleHighPass()
{
	this->resetMiniBuffer(3);
}


float MBAudioFilter::simpleHighPass(float data)
{
	this->miniBuffer[0] = data - (this->miniBuffer[1] + this->cutOff * (data - this->miniBuffer[1])) - (this->miniBuffer[2] + this->cutOff * (this->miniBuffer[1] - this->miniBuffer[2]));
	this->miniBuffer[2] = this->miniBuffer[1];
    this->miniBuffer[1] = this->miniBuffer[0];

	return this->miniBuffer[0];
}

void MBAudioFilter::initNotch()
{
	this->filterType = 3;
	//this->resetTemps(6);
	//this->resetMiniBuffer(6);
    
    this->temps = new float[6];
    this->miniBuffer = new float[6];
    
	this->temps[0] = cos(2 * M_PI * this->cutOff / this->sampleRate);
	this->temps[1] = pow((1 - this->resonance), 2) / (2 * (this->temps[0] + 1)) + this->resonance;
	this->temps[2] = -2 * this->temps[0] * this->temps[1];
	this->temps[3] = 2 * this->temps[0] * this->resonance;
	this->temps[4] = -this->resonance * this->resonance;
	this->temps[5] = 0;
}


float MBAudioFilter::notch(float data)
{
	//input buffer 3 sample
	this->miniBuffer[2] = this->miniBuffer[1];
	this->miniBuffer[1] = this->miniBuffer[0];
	this->miniBuffer[0] = data;
	
	this->temps[5] = this->temps[1] * ((this->miniBuffer[0] + this->miniBuffer[2]) + this->temps[2]) * (this->miniBuffer[1] + this->temps[3]) * (this->miniBuffer[4] + this->temps[4]) * this->miniBuffer[5];
	
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
    

	this->temps[0] = cos(2 * M_PI * this->cutOff / this->sampleRate);
	this->temps[1] = (1 - this->resonance)*sqrt(this->resonance*(this->resonance-4*pow(this->temps[0],2)+2)+1);
	this->temps[2] = 2 * this->temps[0] * this->resonance;
	this->temps[3] = pow(-this->resonance,2);
	this->temps[4] = 0;
}

float MBAudioFilter::fBandPass(float data)
{
	this->miniBuffer[0] = data;
	this->temps[4] = this->temps[1] * this->miniBuffer[0] + this->temps[2] * this->miniBuffer[1] + this->temps[3] * this->miniBuffer[2];
	
	this->miniBuffer[2] = this->miniBuffer[1];
	this->miniBuffer[1] = this->miniBuffer[0];
	
	return this->temps[4];
}

void MBAudioFilter::initDCRemoval()
{
	this->resetTemps(2);
    
    for(int i=0;i<2;i++){
        this->temps[i] = 0.0;
    }
    
	this->temps[0] = this->temps[1] = this->temps[2] = 0;
}

float MBAudioFilter::dCRemoval(float data)
{
	this->temps[2] = data - this->temps[1];
	this->temps[0] = this->temps[0] + (data - this->temps[1]) * 0.000004567;
	this->temps[1] = this->temps[1] + this->temps[0];
	this->temps[0] = this->temps[0] * 0.96;
	return this->temps[2];
}

void MBAudioFilter::initIIRTest(){
    this->temps = new float[4];
    this->miniBuffer = new float[6];
    
    this->a1 = 0.0001;
    this->a2 = 0.04525;
    this->a3 = 0.0001;
    
    this->temps[0] = 0.0;
    this->temps[1] = 0.00;
    this->temps[2] = 0.0233;
    this->temps[3] = 0.0001;
    
    for(int i=0;i<6;i++){
        this->miniBuffer[i] = 0.0;
    }
}

float MBAudioFilter::iIRTest(float data){
    
    //input buffer 3 sample
	this->miniBuffer[2] = this->miniBuffer[1];
	this->miniBuffer[1] = this->miniBuffer[0];
	this->miniBuffer[0] = data;
   
    this->temps[0] = (this->a1 * this->miniBuffer[0]) + (this->a2 * this->miniBuffer[1]) + (this->a3 * this->miniBuffer[2]) + (this->temps[1] * this->miniBuffer[3]) + (this->temps[2] * this->miniBuffer[4]) + (this->temps[3] * this->miniBuffer[5]);
    
    //output buffer 3 sample
	this->miniBuffer[5] = this->miniBuffer[4];
	this->miniBuffer[4] = this->miniBuffer[3];
	this->miniBuffer[3] = this->temps[0];
	
    return this->temps[0];
}



void MBAudioFilter::initLowPass24dbOct(float passBandRipple){
    
    this->resetTemps(12);
    this->resetMiniBuffer(5);
    
    float *coeff = new float[4];
    float K , sg, cg;
    K = sg = cg = 0.0;

    
    // first calculate the prewarped digital frequency:
    
    K = tan(M_PI * this->cutOff / this->sampleRate);
    
    printf("K %f\n", K);
    
    // now we calc some Coefficients:
    
    sg = sinhf(passBandRipple);
    cg = coshf(passBandRipple);
    cg *= cg;
    
    printf("sg %f\n", sg);
    printf("cg %f\n", cg);
    
    coeff[0] = 1 / (cg-0.85355339059327376220042218105097);
    coeff[1] = K * coeff[0]*sg*1.847759065022573512256366378792;
    coeff[2] = 1 / (cg-0.14644660940672623779957781894758);
    coeff[3] = K * coeff[2]*sg*0.76536686473017954345691996806;
    
    K *= K;
    
    // calculate the first biquad
    
    this->temps[0] = 1/(coeff[1]+K+coeff[0]);
    this->temps[1] = 2*(coeff[0]-K)*this->temps[0];
    this->temps[2] =   (coeff[1]-K-coeff[0])*this->temps[0];
    this->temps[3] = this->temps[0]*K;
    this->temps[4] = 2*this->temps[3];
    this->temps[5] = this->temps[3];
    
    // calculate the second biquad:
    
    this->temps[6] = 1/(coeff[3]+K+coeff[2]);
    this->temps[7] = 2*(coeff[2]-K)*this->temps[6];
    this->temps[8] =   (coeff[3]-K-coeff[2])*this->temps[6];
    this->temps[9] = this->temps[6]*K;
    this->temps[10] = 2*this->temps[9];
    this->temps[11] = this->temps[9];
    
    int i = 0;
    
    this->miniBuffer[4] = 0.7;  //Resonance
    
    for(i=0;i<12;i++)
        printf("%i %f\n", i, this->temps[i]);

}


float MBAudioFilter::lowPass24dbOct(float data){
    
    float output;
    a0 = this->miniBuffer[0] * this->miniBuffer[4];
    a1 = this->miniBuffer[1] * this->miniBuffer[4];
    a2 = this->miniBuffer[2] * this->miniBuffer[4];
    a3 = this->miniBuffer[3] * this->miniBuffer[4];
    
    a1 = this->temps[3]*data + a0;
    a0 = this->temps[4]*data + this->temps[1]*a1 + a1;
    a1 = this->temps[5]*data + this->temps[2]*a1;
    
    output = this->temps[9]*a1 + a2;
    a2 = this->temps[10]*a1 + this->temps[7]*output + a3;
    a3 = this->temps[11]*a1 + this->temps[8]*output;

    this->miniBuffer[0] = a0;
    this->miniBuffer[1] = a1;
    this->miniBuffer[2] = a2;
    this->miniBuffer[3] = a3;
    
    return output;
}


