/****************************************************************************/
/**
    @file   FixedPointNumber.cpp
    @author Alessio Leoncini
    @brief  Code file with definitions for FixedPointNumber, a class that 
            embeds number and associated operations in a fixed point 
            representation
*/
/****************************************************************************/
 
#include "FixedPointNumber.h"
 
/************************** CONSTRUCTORS/DESTRUCTOR *************************/
//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
FixedPointNumber::FixedPointNumber()
{
    /// First, all pointers to NULL
    _value = NULL;
    /// Initialization
    Init();
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
FixedPointNumber::FixedPointNumber(int totalBits, int fractionBits, bool withSign)
{
    /// First, all pointers to NULL
    _value = NULL;
    /// Initialization with parameters
    Init(totalBits,fractionBits,withSign);
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
FixedPointNumber::FixedPointNumber(int totalBits, int fractionBits, bool withSign, Word * value)
{
    /// First, all pointers to NULL
    _value = NULL;
    /// Initialization with parameters
    Init(totalBits,fractionBits,withSign,value);
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
FixedPointNumber::FixedPointNumber(FixedPointNumber & X)
{
    /// First, all pointers to NULL
    _value = NULL;
    /// Initialization with parameters
    Init(X._totalBits, X._fractionBits, X._withSign, X._value);
}
 
//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
FixedPointNumber::~FixedPointNumber()
{
    Reset();
}
 
/********************************* OPERATORS ********************************/
//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
ostream & operator << ( ostream & o, FixedPointNumber & X)
{
    int i;
    char buffer1[FPNBUFL];
    char buffer2[FPNBUFL];

    o << "FixedPointNumber object start"<<endl;
    /// Total bits print
    o << " Total bits: "<<X._totalBits<<endl;
    /// Fractionary bits print
    o << " Fractionary bits: "<<X._fractionBits<<endl;
    /// Printing if current representation consider sign
    if(X._withSign)
        o << " MSB is the sign bit, number is in two's complement"<<endl;
    else
        o << " Unsigned representation"<<endl;
    /// Printing if the last operation caused overflow
    if(X._overflow)
        o << " Last operation CAUSED overflow"<<endl;
    else
        o << " Last operation DID NOT CAUSE overflow"<<endl;
    /// Words count
    o << " Number is "<<X._words<<" words long, a single word is "<<FPNWORL<<" bits"<<endl;
    /// Represented value print
    o << " Hex value (from MSB to LSB):\n ";
    strcpy_s(buffer1,FPNBUFL,"");
    strcpy_s(buffer2,FPNBUFL,"");
    /// For every word of value:
    for(i=(X._words-1); i>=0; i--)
    {
        /// - Concatenate strings in inverse order
        itoa(X._value[i],buffer1,16);
        strcat_s(buffer1,FPNBUFL," ");
        strcat_s(buffer2,FPNBUFL,buffer1);
    }
    /// Print entire string
    o << buffer2 << endl;
    o << " Binary value (from MSB to LSB):\n ";
    /// For every word of value:
    for(i=X._totalBits-1; i>=0; i--)
    {
        o<<X.GetBit(i);
    }
    /// Print entire string
    o << endl;
    o << "FixedPointNumber object end"<<endl;
    return o;
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
const FixedPointNumber operator + (const FixedPointNumber & lX, const FixedPointNumber & rX)
{
    Word carry;
    FixedPointNumber n;
    int i;

    /// WARNING due to speed choices, check on sign, total number of bits and 
    /// fractional bits are skipped!!!!

    /// Check if addends have the same words number
    if(lX._words != rX._words)
    {
        cout<<"Addiction members must have same _words"<<endl;
        return FixedPointNumber();
    }
    /// Init result class
     n.Init(lX._totalBits,lX._fractionBits,lX._withSign);
    /// Evaluating sum value
    carry = 0;
    for(i=0; i<lX._words; i++)
    {
        /// - Simple sum of words
        n._value[i] = lX._value[i] + rX._value[i] + carry;
        /// - Carry evaluation
        carry = 0;
        if(n._value[i] < lX._value[i])
            carry = 1;
        else if(n._value[i] < rX._value[i])
            carry = 1;
    }
    /// Setting overflow flag according to sum results
    n._overflow = (carry == 1);
    /// Return class with same representation and just calculated value
    return n;
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
const FixedPointNumber operator - (const FixedPointNumber & lX, const FixedPointNumber & rX)
{
    FixedPointNumber n;
    FixedPointNumber lsb;
    int i;

    /// WARNING due to speed choices, check on sign, total number of bits and 
    /// fractional bits are skipped!!!!

    /// Check if members have the same words number
    if(lX._words != rX._words)
    {
        cout<<"Subtraction members must have same _words"<<endl;
        return FixedPointNumber();
    }
    /// Creating negative of rX:
    n.Init(rX._totalBits,rX._fractionBits,rX._withSign,rX._value);
    for(i=0; i<n._words; i++)
    {
        n._value[i] = ~(n._value[i]);
    }
    /// Sum lX with not(rX)
    n = lX + n;
    /// If signed representation, two's complement requires an addictional +1 operation
    if(rX._withSign)
    {
        /// Init of lsb object
        lsb.Init(rX._totalBits,rX._fractionBits,rX._withSign);
        lsb._value[0] = 1;
        /// - Adding lsb to previous value
        n = n + lsb;
    }
    /// Return of the subtraction number
    return n;
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
FixedPointNumber & FixedPointNumber::operator = (const FixedPointNumber & X)
{
    Init(X._totalBits, X._fractionBits, X._withSign, X._value);
    return *this;
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
bool operator == (const FixedPointNumber & lX, const FixedPointNumber & rX)
{
    int i;

    /// Check all the members
    if((lX._totalBits == rX._totalBits) &&
        (lX._fractionBits == rX._fractionBits) &&
        (lX._withSign == rX._withSign) &&
        (lX._words == rX._words))
    {
        /// And all the bits
        for(i=0; i<lX._words; i++)
        {
            if(lX._value[i]!=rX._value[i])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
const FixedPointNumber operator << (const FixedPointNumber & X, const int & number)
{
    int i,j;
    bool oldSign;
    Word exceeds;
    FixedPointNumber n;
    int positions;

    /// Check number
    if(number <=0)
    {
        cout<<"Invalid number of left shifts"<<endl;
        return FixedPointNumber();
    }

    /// Reset overflow state
    n._overflow = false;
    /// Init with values specified in X
    n.Init(X._totalBits, X._fractionBits, X._withSign, X._value);
    /// Saving sign
    oldSign = false;
    if(n._withSign)
        oldSign = n.GetBit(n._totalBits-1);
    /// Shift cycle: i is the destination word, j is the source word
    i = n._words-1;
    j = i - (number / FPNWORL);
    if(j<0)
    {
        cout<<"Too high number of left shifts"<<endl;
        return FixedPointNumber();
    }
    positions = number % FPNWORL;
    /// - If positions to shift is multiple of word length, no shift required!
    /// Only register replacing is necessary
    if(positions == 0)
    {
        /// -- Registers replacing
        for(; j>=0; i--,j--)
            n._value[i] = n._value[j];
        /// -- Filling least significant bits with zeros
        for(; i>=0; i--)
            n._value[i] = 0;
    }
    /// - Else, necessary to take into account of bits that move between words
    else
    {
        /// -- First iteration, with possible overflow check
        /// --- Saving exceeding bits from source register
        exceeds = n._value[j] >> (FPNWORL-positions);
        /// --- If exceeds different from zero, overflow
        if(exceeds > 0)
        {
            n._overflow = true;
        }
        /// --- Shift source register and save in dest. register
        n._value[i] = n._value[j] << positions;
        i--;
        j--;
        /// -- Loop for every source register
        for(; j>=0; i--,j--)
        {
            /// --- Saving exceeding bits from source register
            exceeds = n._value[j] >> (FPNWORL-positions);
            /// --- Xoring previous destination register with exceeds bits
            n._value[i+1] ^= exceeds;
            /// --- Shift source register and save in dest. register
            n._value[i] = n._value[j] << positions;
        }
        /// -- Filling least significant words with zeros
        for(; i>=0; i--)
            n._value[i] = 0;
    }
    /// If negative sign was saved, restore it
    if(oldSign)
        n.SetBit(n._totalBits-1,true);
    /// Return object
    return n;
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
const FixedPointNumber operator >> (const FixedPointNumber & X, const int & number)
{
    int i,j;
    bool oldSign;
    Word exceeds;
    FixedPointNumber n;
    int positions;

    /// Check number
    if(number <=0)
    {
        cout<<"Invalid number of rigth shifts"<<endl;
        return FixedPointNumber();
    }

    /// Reset overflow state
    n._overflow = false;
    /// Init with values specified in X
    n.Init(X._totalBits, X._fractionBits, X._withSign, X._value);
    /// Saving sign
    oldSign = false;
    if(n._withSign)
        oldSign = n.GetBit(n._totalBits-1);
    /// Shift cycle: i is the destination word, j is the source word
    i = 0;
    j = i + (number / FPNWORL);
    if(j>n._words)
    {
        cout<<"Too high number of rigth shifts"<<endl;
        return FixedPointNumber();
    }
    positions = number % FPNWORL;
    /// - If positions to shift is multiple of word length, no shift required!
    /// Only register replacing is necessary
    if(positions == 0)
    {
        /// -- Registers replacing
        for(; j<n._words; i++,j++)
            n._value[i] = n._value[j];
        /// -- Filling most significant bits with zeros or ones, according to 
        /// original number sign
        if(oldSign)
            exceeds = ~((Word)0);
        else
            exceeds = (Word)0;
        for(; i<n._words; i++)
            n._value[i] = exceeds;
    }
    /// - Else, necessary to take into account of bits that move between words
    else
    {
        /// -- First iteration, with possible overflow check
        /// --- Shift source register and save in dest. register
        n._value[i] = n._value[j] >> positions;
        i++;
        j++;
        /// -- Loop for every source register
        for(; j<n._words; i++,j++)
        {
            /// --- Saving exceeding bits from source register
            exceeds = n._value[j] << (FPNWORL-positions);
            /// --- Xoring destination register with exceeds bits
            n._value[i-1] ^= exceeds;
            /// --- Shift source register and save in dest. register
            n._value[i] = n._value[j] >> positions;
        }
        /// -- Filling most significant bits with zeros or ones, according to 
        /// original number sign
        if(oldSign)
        {
            exceeds = ~((Word)0);
            n._value[i-1] |= (exceeds << (FPNWORL-positions)); 
        }
        else
            exceeds = (Word)0;
        for(; i<n._words; i++)
            n._value[i] = exceeds;
    }
    /// Return object
    return n;
}

/****************************** BASIC HANDLING ******************************/
//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
void FixedPointNumber::Init()
{
    /// Reset
    Reset();
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
void FixedPointNumber::Init(int totalBits, int fractionBits, bool withSign)
{
    int i;

    /// Parameters check
    if(totalBits <= 0)
    {
        cout<<"Param totalBits not valid in FixedPointNumber::Init"<<endl;
        return;
    }
    if((fractionBits <= 0) || 
         (fractionBits > totalBits))
    {
        cout<<"Param fractionBits not valid in FixedPointNumber::Init"<<endl;
        return;
    }
    /// Architecture check
    if(sizeof(Word)*8 != FPNWORL)
    {
        cout<<"Architecture does not match with defined word length; ";
        cout<<"sizeof(Word) is "<<sizeof(Word)<<"bytes";
        cout<<" where FPNWORL is "<<FPNWORL<<"bits in FixedPointNumber::Init"<<endl;
        return;
    }

    /// Reset
    Reset();
    /// Parameters assignment
    _totalBits = totalBits;
    _fractionBits = fractionBits;
    _withSign = withSign;
    /// Evaluating necessary word number
    _words = (int)ceil((double)_totalBits/FPNWORL);
    if(_words <= 0)
    {
        cout<<"Error during evaluating words number in FixedPointNumber::Init"<<endl;
        return;
    }
    /// Allocation of bits array space
    _value = new Word [_words];
    /// All bits to zero
    for(i=0; i<_words; i++)
        _value[i] = 0;
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
void FixedPointNumber::Init(int totalBits, int fractionBits, bool withSign, Word * value)
{
    int i;

    /// Check only value parameter
    if(value == NULL)
    {
        cout<<"Param value not valid in FixedPointNumber::Init"<<endl;
        return;
    }
    /// Call Init with representation parameters
    Init(totalBits,fractionBits,withSign);
    /// Value assignment
    for(i=0; i<_words; i++)
        _value[i] = value[i];
}
 
//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
void FixedPointNumber::Reset()
{
    /// Deallocation of bits array
    if(_value != NULL)
    {
        delete _value;
        _value = NULL;
    }
    _words = 0;
    _totalBits = 0;
    _fractionBits = 0;
    _withSign = false;
    _overflow = false;
}
 
//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
void FixedPointNumber::Dump()
{
    cout<<*this;
}
 
/***************************** ACCESS METHODS *******************************/
//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
inline bool FixedPointNumber::GetBit(int position)
{
    int word;
    int regpos;

    /// Check if position is valid
    if((position < 0) || (position >= _totalBits))
    {
        cout<<"Param position not valid in FixedPointNumber::GetBit"<<endl;
        return false;
    }
    /// Selection of correct word
    word = position / FPNWORL;
    /// Selection of position in register
    regpos = position % FPNWORL;
    /// Return selected word AND mask
    if(_value[word] & (1<<regpos))
        return true;
    return false;
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
inline void FixedPointNumber::SetBit(int position, bool value)
{
    int word;
    int regpos;

    /// Check if position is valid
    if((position < 0) || (position >= _totalBits))
    {
        cout<<"Param position not valid in FixedPointNumber::SetBit"<<endl;
        return;
    }
    /// Selection of correct word
    word = position / FPNWORL;
    /// Selection of position in register
    regpos = position % FPNWORL;
    /// If positive bit, OR with all zeros and 1 in desired position
    if(value)
    {
        _value[word] |= (1<<regpos);
    }
    /// Else, AND with all ones and 0 in desired position
    else
    {
        _value[word] &= ~(1<<regpos);
    }
}

//////////////////////////////////////////////////////////////////////////////
/// \par PROCEDURE:
inline bool FixedPointNumber::IsOverflow()
{
    return _overflow;
}