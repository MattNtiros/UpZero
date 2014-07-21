#ifndef UPZERO_IMPL_H
#define UPZERO_IMPL_H

#include "UpZero_base.h"

using std::vector;
using std::complex;
using std::cout;
using std::endl;

typedef float type;

class UpZero_i : public UpZero_base
{
	ENABLE_LOGGING
public:
	UpZero_i(const char *uuid, const char *label);
	~UpZero_i();
	int serviceFunction();

private:
	vector<type> dataOut;
	vector<complex<type> > dataOut_complex;
	unsigned long old_upsample_factor;
	bool updateSRI;


	template<typename T>
	void addZeros(vector<T> &dataIn, vector<T> &dO)
	{
		dO.resize(dataIn.size()*upsample_factor);
		for(unsigned int i=0;i<dO.size();i=i+upsample_factor)
		{
			dO[i] = dataIn[i/upsample_factor];
		}
	}

};

#endif // UPZERO_IMPL_H
