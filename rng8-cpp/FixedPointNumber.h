/****************************************************************************/
/**
	@file		FixedPointNumber.h
	@author		Alessio Leoncini
	@brief		Header file with definitions for FixedPointNumber, a class that 
				embeds number and associated operations in a fixed point 
				representation

				TODO: possibility of overflow ring in operations, and get of 
				private members for reading bits representation
*/
/****************************************************************************/
 
#ifndef FixedPointNumber_h
#define FixedPointNumber_h
 
#include <iostream>
#include <math.h>

/// Buffer lenght (bytes)
#define FPNBUFL 20000
/// Word length (bits)
#define FPNWORL 32
/// Predefined type for a single word
typedef unsigned int Word; 
 
using namespace std;
 
/**
@class FixedPointNumber
@brief Random Number Generator. It generates [0,1) random number
*/
class FixedPointNumber
{
 
/////////////////////////////// PRIVATE Segment //////////////////////////////
private:
/////////////////////////////// PROTECTED Segment ////////////////////////////
protected:
	/// Array of words; 
	Word * _value;
	int _words;
	bool _overflow;
	bool _withSign;
	int _totalBits;
	int _fractionBits;
 
/////////////////////////////// PUBLIC Segment ///////////////////////////////
public:
 
	/// @name CONSTRUCTORS/DESTRUCTOR
	/// @{
 
	/// Private default constructor
	FixedPointNumber();
	/// Init constructor
	FixedPointNumber(int totalBits, int fractionBits, bool withSign);
	/// Init constructor with value
	FixedPointNumber(int totalBits, int fractionBits,  bool withSign, Word * value);
	/// Copy constructor
	FixedPointNumber(FixedPointNumber & X);
	/// Destructor
	virtual ~FixedPointNumber();
	//@}
 
	/// @name OPERATORS
	/// @{
 
	/// Print operator
	friend ostream & operator << ( ostream & o, FixedPointNumber & X); 
	/// Sum operator
	friend const FixedPointNumber operator + (const FixedPointNumber & lX, const FixedPointNumber & rX);
	/// Subtraction operator
	friend const FixedPointNumber operator - (const FixedPointNumber & lX, const FixedPointNumber & rX);
	/// Assignment operator
	FixedPointNumber & operator = (const FixedPointNumber & X);
	/// Equality operator
	friend bool operator == (const FixedPointNumber & lX, const FixedPointNumber & rX);
	/// Arithmetic left shift operator
	friend const FixedPointNumber operator << (const FixedPointNumber & X, const int & number);
	/// Arithmetic right shift operator
	friend const FixedPointNumber operator >> (const FixedPointNumber & X, const int & number);
	//@}
 
	/// @name BASIC HANDLING
	/// @{
 
	/// Default initialization
	void Init();
	/// Parameters initialization
	void Init(int totalBits, int fractionBits, bool withSign);
	/// Parameters and value initialization
	void Init(int totalBits, int fractionBits, bool withSign, Word * value);
	/// Object erasure
	void Reset();
	/// Object printout for diagnostic
	void Dump();
	//@}
 
	/// @name ACCESS METHODS
	/// @{

	/// Get specified bit (0=LSB, _totalBits-1=MSB)
	bool GetBit(int position);
	/// Set specified bit (0=LSB, _totalBits-1=MSB)
	void SetBit(int position, bool value);
	/// Read overflow flag
	bool IsOverflow();
	//@}
};
 
#endif