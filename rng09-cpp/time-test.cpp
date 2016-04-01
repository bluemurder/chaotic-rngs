/****************************************************************************/
/**
    @file   time-test.cpp
    @author Alessio Leoncini
    @brief  Time test: assembly vs C bitwise operations
*/ 
/****************************************************************************/
#include <iostream>
#include <time.h>

using namespace std;
#define ITERATIONS 100000000

//////////////////////////////////////////////////////////////////////////////
/// Assembly procedure
bool TestBit_assembly(int _byte, int pos)
{
    __asm    mov eax, _byte;
    __asm    mov ebx, pos;
    __asm bt eax,ebx;
    __asm jnc skip;
    return true;
    __asm skip: ;
    return false;
}

//////////////////////////////////////////////////////////////////////////////
/// C procedure
bool TestBit_bitwise(int _byte, int pos)
{
    return (_byte & (1<<pos)) > 0;
}

//////////////////////////////////////////////////////////////////////////////
/// Main program
int main()
{
    int byte = 0xf6;
    int i;
    clock_t start;

    /// First test
    start = clock();
    for(i=0; i<ITERATIONS; i++)
    {
        TestBit_assembly(byte,i%7);
    }
    cout<<"First test:"<<clock()-start<<" time"<<endl;
    /// Second test
    start = clock();
    for(i=0; i<ITERATIONS; i++)
    {
        TestBit_bitwise(byte,i%7);
    }
    cout<<"Second test:"<<clock()-start<<" time"<<endl;
}