
/*
MBAudioBuffer

Speichert den Audiostream zwischen. 
Stereo (und mehr) hier gilt folgende Speicherorder im Array:

Idx Value 
0	Sample Channel 0
1 	Sample Channel 1
2 	Sample Channel 0
3 	Sample Channel 1
.. 

so können beliebig viele Kanäle abgebildet werden.


*/
class MBAudioBuffer
{
public:
	int size;
	int sampleRate;
	long *buffer
	int lastUsedChannel;
	int idx;
	
	MBAudioBuffer(); 
	MBAudioBuffer(const MBAudioBuffer& a); 
	MBAudioBuffer(int sz, int sRate);
	~MBAudioBuffer(); 
	
	void addData(const long& data);
	void addData(const float& data);
	
	long convertFloatToLong(float a);
	
	void initZeroBuffer();
	
	long& getChunck(int chunkSize);
}