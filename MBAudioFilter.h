
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
	
	MBAudioBuffer bufffer;
	
}







