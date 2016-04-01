/****************************************************************************/
/**
    @file   randgen-fixedvalidation.cpp
    @author Alessio Leoncini
    @brief  Shift and sum stress, for validation purposes
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
  ofstream outfile;
  long unsigned int i,N;
    int j;
    FixedPointNumber x;
    FixedPointNumber x0;
    int totalBits = 145;
    int fracBits = 1;

    /// Read params
  N = 5;
  /// Open output file
  outfile.open("validation2-states.txt",ios::out);
    /// Writing starting conditions
    /// x = 0.5
    x0.Init(totalBits,fracBits,true);
    x0.SetBit(fracBits-1,true);

    x0.Dump();/////////////////////////////////////////////////////

    /// Main cycle
    x=x0;
    for(i=0; i<N; i++)
    {
        /// - print state
        for(j=totalBits-1; j>=0; j--)
        {
            if(x.GetBit(j))
            {
                outfile << 1;
            }
            else
            {
                outfile << 0;
            }
        }
        outfile << "\n";
        /// - map
        x = (x << 33);
    }


    /// Second cycle
    x=x0;
    for(i=0; i<N; i++)
    {
        /// - print state
        for(j=totalBits-1; j>=0; j--)
        {
            if(x.GetBit(j))
            {
                outfile << 1;
            }
            else
            {
                outfile << 0;
            }
        }
        outfile << "\n";
        /// - map
        x = (x >> 33);
    }
  /// Closing file
  outfile.close();
}