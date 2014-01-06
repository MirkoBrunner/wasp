
/*
MBAudioFilter

Filterbox mit den gängisten AudioFilter:
Bandpass(1p..4p), Notch(1p..4p), Tiefpass (1p..4p), Hochpass(1p..4p), All-Pass

Die Filter arbeiten alle Mono, wenn Stereo Streams verwendet werden muss der Filter auf jeden Kanal einzeln angewendet werden.

*/
class MBAudioFilterLo
{
public:
	MBAudioFilter();
	~MBAudioFilter(); 

	MBAudioBuffer *buffer;
	
	double *miniBuffer;
	int sampleRate;
	float cutOff;
	float resonance;
	
	//temporary helper
	double *temps;
	
	void build();
	
	//simplest lowpass filter ever ;)
	long simpleLowPass(const double& data);
	
	void initLowPassResonance();
	double lowPassResonance(const double& data);
	
	
	void initNotch
	double notch(const double& data);
	
}







