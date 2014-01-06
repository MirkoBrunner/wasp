
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
	
	long *miniBuffer;
	int sampleRate;
	int cutOff;
	
	
	//configure filter 
	void configureFilter(const int sRate, const int bufferSize);

	
	//simplest lowpass filter ever ;)
	long simpleLowPass(const long data, const long& cutoff);
	
	
}







