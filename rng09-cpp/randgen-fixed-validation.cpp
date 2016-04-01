/****************************************************************************/
/**
    @file   randgen-fixedvalidation.cpp
    @author Alessio Leoncini
    @brief  Chaotic map iterations and print of all the reached states, for 
            validation purposes
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
    FixedPointNumber one;
    FixedPointNumber minusone;
    int totalBits = 75;
    int fracBits = 62;

    /// Read params
  N = 1000;
  /// Open output file
  outfile.open("validation-states.txt",ios::out);
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

    x.Dump();/////////////////////////////////////////////////////
    one.Dump();/////////////////////////////////////////////////////
    minusone.Dump();/////////////////////////////////////////////////////

    /// Main cycle
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
        x.Dump();////*****************************erase!!!!!!!!!!!!!!!!!!
        if (x.GetBit(totalBits-1))
        {
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