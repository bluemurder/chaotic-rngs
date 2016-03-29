/************************************************************

Program that changes the template.vhd code into "CaosAlAl.vhd"
code in order to change two parameters; these params are given 
as commandline parameters

*************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define BUFLEN 2000

int main(int argc, char** argv)
{
    int bits;
    int skip;
    ifstream infile;
    ofstream outfile;
    string line;
    string pattern1("constant nbit : integer :=");
    string pattern2("constant skip : integer :=");
    size_t found;
    char buffer[BUFLEN];

    /// Check usage
    if(argc != 3)
    {
        cout<<"Usage: vhdlparams <bits> <skip>\n    <bits> number of bits of the state register\n  <skip> how many bits skip between outputs"<<endl;
        return 1;
    }

    /// Read parameters
    bits = atoi(argv[1]);
    skip = atoi(argv[2]);

    /// Open files
    infile.open("template.vhd",ios::in);
    outfile.open("CaosAlAl.vhd", ios::out);

    /// Read and write cycle
    while(!infile.eof())
    {
        /// - Read a line;
        infile.getline(buffer,BUFLEN);
        line = buffer;
        /// - If line is one of the two parameter lines, substitute it
        found = line.find(pattern1);
        if(found != string::npos)
        {
            line = pattern1 + " " + argv[1] + ";";
        }
        found = line.find(pattern2);
        if(found != string::npos)
        {
            line = pattern2 + " " + argv[2] + ";";
        }
        /// - writing line
        outfile << line << endl;
    }

    /// Closing files
    infile.close();
    outfile.close();

    return 1;
}