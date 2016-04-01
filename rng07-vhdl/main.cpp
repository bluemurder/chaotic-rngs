/************************************************************

Program that creates the "randgen_package.vhd" code 
specifying NBITS and SKIP parameters. Such numbers are given 
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
    ofstream outfile;

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
    outfile.open("randgen_package.vhd", ios::out);

    outfile << "library IEEE;\n";
    outfile << "use IEEE.STD_LOGIC_1164.all;\n";
        outfile << "use IEEE.NUMERIC_STD.all;\n";
    outfile << "package randgen_package is\n";

    outfile << "-- Declare constants\n";

    outfile << "    -- Number of bits used for internal register of the chaotic map\n";
    outfile << "    constant N_BIT : integer := "<<bits<<";\n";

    outfile << "    -- Number of bits to skip in the output sequence\n";
    outfile << "    constant SKIP : integer := "<<skip<<";\n";
    
    outfile << "    -- Initial condition for the chaotic map\n";
    outfile << "    constant X0 : signed(N_BIT-1 downto 0) := (N_BIT-3 => '1', others => '0');    -- 0.5\n";
    
    outfile << "    -- Enables the Von Neumann corrector\n";
    outfile << "    constant ENABLE_VON_NEUMANN : boolean := true;\n";
    
    outfile << "    -- Clock period for the simulation\n";
    outfile << "    constant CLK_PERIOD : time := 10 ns;\n";

    outfile << "end randgen_package;\n";

    outfile << "package body randgen_package is\n";

    outfile << "end randgen_package;\n";

    /// Closing files
    outfile.close();

    return 1;
}