
/*
MBAudioBuffer

Speichert den Audiostream zwischen. 

*/
class MBAudioBuffer
{
private:
	int size;
	int sampleRate;
	long *buffer
	int idx;
	
public:	
	MBAudioBuffer(); 
	MBAudioBuffer(const MBAudioBuffer& a); 
	MBAudioBuffer(int sz, int sRate);
	~MBAudioBuffer(); 
	
	void setSize(const int size);
	void setSampleRata(const int sRate);
	
	void addData(const long& data);
	void addData(const float& data);
	
	long convertFloatToLong(float a);
	
	void initZeroBuffer();
	
	long& getChunck(int chunkSize);
}