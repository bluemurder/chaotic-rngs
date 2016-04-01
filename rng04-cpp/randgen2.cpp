#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

int TwoPowers(int exponent)
{
    int i;
    int result;

    if(exponent==0)
    {
        return 1;
    }
    else
    {
        result=1;
        for(i=0; i<exponent; i++)
        {
            result = result * 2;
        }
        return result;
    }
}

int main(int argc, char **argv) 
{
    char usage [] = "Usage: randGen <k1> <k2> <x0> <N> <outfile> <ascii/bin> <skip>\n  where N is the number of iterations of the map\n  outfile is the list of signs in requested format (ascii-binary)\n  skip is the number of map iterations to skip while writing output\n  and the map is\n  - x(k+1) = k1 * x(k) + 1 if x(k) < 0\n  - k2 * x(k) - 1 otherwise\n\n";

    double k1, k2, x0, x;
    ofstream outfile;
    long unsigned int i,N;
    int j,k,q,format,skip;
    char sum;

    /// Read parameters
    if (argc != 8)  
    {
        cout << usage;
        return -1;
    }

    k1 = atof(argv[1]);
    k2 = atof(argv[2]);
    x0 = atof(argv[3]);
    N = atoi(argv[4]);
    skip = atoi(argv[7]);
    if(strcmp(argv[6],"ascii")==0)
    {
        format=1;
    }
    else if(strcmp(argv[6],"bin")==0)
    { 
        format=2;
    }
    else
    {
        cout<<"Error in given parameters"<<endl;
        cout<<usage<<endl;
        return -1;
    }

    /// Open output file
    outfile.open(argv[5],ios::out);

    x = x0;
    sum = 0;

    if(format==1)
    { 
        /// main ASCII cycle
        for (i=0,j=0; i<N; i++,j++) 
        {  
            /// - skip cycle
            for(q=0; q<skip; q++)
            {
                if(x<0){x = k1*x+1;}
                else{x = k2*x-1;}
            }
            /// - map
            if (x<0)
            {
                outfile << '0';
                x = k1*x+1;
            }
            else
            {
                outfile << '1';
                x = k2*x-1;
            }
        }
    }
    else
    {
        /// Main binary cycle
        for(i=0,k=0; i<N; i++,k++)
        {
            /// - skip cycle
            for(q=0; q<skip; q++)
            {
                if(x<0){x = k1*x+1;}
                else{x = k2*x-1;}
            }
            /// - print byte
            if(k==8)
            {
                outfile<<sum;
                sum = 0;
                k = 0;
            }
            /// - map
            if (x<0)
            {
                //outfile << '0';
                x = k1*x+1;
            }
            else
            {
                sum += TwoPowers(7-k);
                //outfile << '1';
                x = k2*x-1;
            }
        }
    }

    cout<<"\n";
    outfile.close();
}
