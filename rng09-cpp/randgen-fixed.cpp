/****************************************************************************/
/**
	@file		randgen-fixed.cpp
	@author	Alessio Leoncini
	@brief	Random number generator based on digitalization of chaotic map state
*/ 
/****************************************************************************/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FixedPointNumber.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
inline double TwoPowers(int exponent)
{
	int i;
	double result;

	/// If exponent is zero, return 1
	if(exponent==0)
	{
		return 1.;
	}
	/// Else, if exponent positive, multiply 2 how many times equals to exponent
	else if(exponent > 0)
	{
		result=1.;
		for(i=0; i<exponent; i++)
		{
			result = result * 2;
		}
		return result;
	}
	/// Else, divide by two how many times equals to exponent
	else
	{
		result=1.;
		for(i=0; i>exponent; i--)
		{
			result = result / 2;
		}
		return result;
	}
}

//////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) 
{
  char usage [] = "Usage: randgen-fixed <N> <outfile> <state bits> <frac bits> <skip>\n  where N is the number of iterations of the map\n  outfile is the list of signs in binary format\n  skip is the number of map iterations to skip while writing output\n  state bits is the number of bits used to represent the state\n  int bits is the number of bits for integer part of the state\n  and the map, with x0=0.5, is\n   x(k+1) = 1.875 * x(k) + 1 if x(k) < 0\n  x(k+1) = 1.875 * x(k) - 1 otherwise\n\n";

  ofstream outfile;
  long unsigned int i,N;
  int k,q,skip;
  char sum;
	FixedPointNumber x;
	FixedPointNumber one;
	FixedPointNumber minusone;
	int totalBits;
	int fracBits;

  /// Read parameters number
  if (argc != 6)  
  {
    cout << usage;
    return -1;
  }
	/// Read params
  N = atoi(argv[1]);
	totalBits = atoi(argv[3]);
	fracBits = atoi(argv[4]); 
  skip = atoi(argv[5]);
  /// Open output file
  outfile.open(argv[2],ios::out);
	/// Writing starting conditions
	/// x = 0.5
	x.Init(totalBits,fracBits,true);
	x.SetBit(fracBits-1,true);
	/// one = 1;
	one.Init(totalBits,fracBits,true);
	one.SetBit(fracBits,true);
	/// minusone = 0 - 1;
	minusone.Init(totalBits,fracBits,true);
	minusone = minusone - one;

//	x->Dump();/////////////////////////////////////////////////////
//	one->Dump();/////////////////////////////////////////////////////
//	minusone->Dump();/////////////////////////////////////////////////////

  sum = 0;
	/// Main binary cycle
	for(i=0,k=0; i<N; i++,k++)
	{
		/// - skip cycle
		for(q=0; q<skip; q++)
		{
			/// -- If MSB is one, number is negative
			if(x.GetBit(totalBits-1))
				x = (x << 1) - (x >> 3) + one;
			else
				x = (x << 1) - (x >> 3) + minusone;

			//x->Dump();/////////////////////////////////////////////////////
		}
		/// - print byte
		if(k==8)
		{
			outfile<<sum;
			sum = 0;
			k = 0;
		}
		/// - map
		if (x.GetBit(totalBits-1))
		{
			sum += TwoPowers(7-k);
			x = (x << 1) - (x >> 3) + one;
		}
		else
		{
			x = (x << 1) - (x >> 3) + minusone;
		}
		//x->Dump();/////////////////////////////////////////////////////////
	}
  /// Closing file
  outfile.close();
}