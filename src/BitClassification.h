// pomerol/trunk/BitClassification.h
// This file is a part of pomerol diagonalization code

/** \file BitClassification.h
**  \brief Declaration of BitInfo & BitClassification classes.
** 
**  \author	Andrey Antipov (antipov@ct-qmc.org)
*/

#ifndef __BIT_CLASSIFICATION__
#define __BIT_CLASSIFICATION__

#include "config.h"
#include "term.h"
#include <json/json.h>
#include <map>
#include <string>


//! BitInfo - a class to reproduce full information about the given bit
/**
 * BitInfo class is an abstract class to handle all info about current bit.  
 */ 

class BitInfo
{
public:
  	unsigned short site;
	unsigned short spin;
	string type;
	unsigned short bitNumber;
	void setBitNumber(const unsigned short &in);
	virtual void print_to_screen()=0;
};

class sBitInfo : public BitInfo
{
public:
	RealType U;
	sBitInfo(unsigned short site_, string &type_, unsigned short spin_, RealType U_):U(U_){site=site_;type=type_;spin=spin_;};
	friend std::ostream& operator<<(std::ostream& output, const sBitInfo& out);
	void print_to_screen(){cout << *this << endl;};
};

class pBitInfo : public BitInfo
{
public:
	RealType U;
	RealType J;
	string basis;
	short index; 
	pBitInfo(unsigned short site_, string &type_, unsigned short spin_, short index_, const string &basis_, RealType U_, RealType J_):U(U_),J(J_){site=site_;type=type_;spin=spin_;index=index_;basis=basis_;};
	friend std::ostream& operator<<(std::ostream& output, const pBitInfo& out);
	void print_to_screen(){cout << *this << endl;};
};

struct TermsList // A list of terms of different orders
{
   std::vector<Term<2>*> Terms1Order;
   std::vector<Term<4>*> Terms2Order;
   std::vector<Term<6>*> Terms3Order;
   std::vector<Term<8>*> Terms4Order;
   std::vector<Term<10>*> Terms5Order;

   TermsList(){Terms1Order.resize(0); Terms2Order.resize(0);Terms3Order.resize(0);Terms4Order.resize(0);Terms5Order.resize(0);};
   friend std::ostream& operator<<(std::ostream& output,TermsList& out);
};

class BitClassification
{
  	Json::Value root; 
	int N_bit;
	RealMatrixType HoppingMatrix;
	vector<BitInfo*> BitInfoList;
	TermsList Terms;
public:
	BitClassification();
	int readin();
	void printBitInfoList();
	void printHoppingMatrix();
	void printTerms();
	RealMatrixType& getHoppingMatrix();
	std::vector<BitInfo*> &getBitInfoList();
	const int& getBitSize() const;
private:
	enum OrbitalValue {s=0, p=1, d=2, f=3};
	std::map<std::string, OrbitalValue> mapOrbitalValue;
	void defineBits();
	void defineHopping();
	void defineTerms();
	void definePorbitalSphericalTerms(pBitInfo **Bits);
	void definePorbitalNativeTerms(pBitInfo **Bits);
	vector<unsigned short>& findBits(const unsigned short &site);
	unsigned short findBit(const unsigned short &site,const unsigned short &spin);
};

#endif

