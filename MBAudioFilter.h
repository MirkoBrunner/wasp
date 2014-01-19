

/*
 MBAudioFilter
 
 Filterbox mit den gängisten AudioFilter:
 Bandpass(1p..4p), Notch(1p..4p), Tiefpass (1p..4p), Hochpass(1p..4p), All-Pass
 
 Die Filter arbeiten alle Mono, wenn Stereo Streams verwendet werden muss der Filter auf jeden Kanal einzeln angewendet werden.
 
 */
class MBAudioFilter
{
public:
	MBAudioFilter();
	~MBAudioFilter();
	
	MBAudioFilter(const MBAudioFilter& a);
	
	float *miniBuffer;
	int filterType;
	float cutOff;
	float resonance;
    int sampleRate;
    
    float a0;
    float a1;
    float a2;
    float a3;
	
	//temporary helper
	float *temps;
	
	void build(const int bufferSize);
	
    void resetTemps(const int size);
    void resetMiniBuffer(const int size);
    
	//simplest lowpass filter ever ;)
	float simpleLowPass(float data);
	
	//lowpass 1p
	void initLowPassResonance();
	float lowPassResonance(float data);
	
	//lowpass v2
	// amp magnitude at the resonation frequency
	void initLowPassResonance2(float amp);
	float lowPassResonance2(float data);
	
	//high
	void initSinpleHighPass();
	float simpleHighPass(float data);
	
	//notch
	void initNotch();
	float notch(float data);
	
	//fast bandpass
	void initFBandPass();
	float fBandPass(float data);
	
	//dc removal
	void initDCRemoval();
	float dCRemoval(float data);
    
    void initIIRTest();
    float iIRTest(float data);
    
    
    
    //new specials:
    void initLowPass24dbOct(float passBandRipple);
    float lowPass24dbOct(float data);
    
};







