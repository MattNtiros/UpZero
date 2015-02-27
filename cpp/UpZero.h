/**
* Copyright (C) 2013 Axios, Inc.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UPZERO_IMPL_H
#define UPZERO_IMPL_H
#define COMPLEX tmp->SRI.mode

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
	vector<type> dataOut;	//stores real output data
	unsigned long old_upsample_factor;	//stores previous iteration's upsample factor for purpose of checking if it has changed
	bool updateSRI;	//stores whether or not SRI has changed since previous iteration



	template<typename T>
	void addZeros(vector<T> &dataIn, vector<T> &dO)
	{
		typename vector<T>::iterator it;
		typename vector<T>::iterator it2 = dataIn.begin();
		dO.resize(dataIn.size()*old_upsample_factor, 0);
		for(it = dO.begin();it != dO.end();it+=old_upsample_factor, it2++)
			*it = *it2;
	}

};

#endif // UPZERO_IMPL_H
