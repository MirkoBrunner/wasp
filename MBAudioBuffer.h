
/*
MBAudioBuffer

Speichert den Audiostream zwischen. 

*/
class MBAudioBuffer
{
private:
	int size;
	int sampleRate;
	double *buffer
	
public:	
	MBAudioBuffer(); 
	MBAudioBuffer(const MBAudioBuffer& a); 
	MBAudioBuffer(int sz, int sRate);
	~MBAudioBuffer(); 
	
	void setSize(const int size);
	void setSampleRata(const int sRate);
	
	void addData(const double& data);
	
	void initBufferWithZero();
	
	long& getChunck(int chunkSize);
}