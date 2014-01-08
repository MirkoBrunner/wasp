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

	MBAudioBuffer *buffer;
	
	double *miniBuffer;
	int filterType;
	float cutOff;
	float resonance;
    int sampleRate;
	
	//temporary helper
	double *temps;
	
	void build(const int bufferSize);
	
    void resetTemps(const int size);
    void resetMiniBuffer(const int size);
    
	//simplest lowpass filter ever ;)
	double simpleLowPass(const double& data);
	
	//lowpass 1p 
	void initLowPassResonance();
	double lowPassResonance(const double& data);
	
	//lowpass v2
	// amp magnitude at the resonation frequency
	void initLowPassResonance2(const double amp);
	double lowPassResonance2(const double& data);
	
	//high 
	void initSinpleHighPass();
	double simpleHighPass(const double& data);
	
	//notch
	void initNotch();
	double notch(const double& data);
	
	//fast bandpass
	void initFBandPass();
	double fBandPass(const double& data);
	
	//dc removal
	void initDCRemoval();
	double dCRemoval(const double& data);
};







