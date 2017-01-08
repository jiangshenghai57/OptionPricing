#pragma once
#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H
using namespace std;
#include <string>
#include <iostream>

class EuropeanOption {

public:
	EuropeanOption();		// Default Constructor
							// Destructor adding later

	// Get private variables functions
	double getR();
	double getVol();
	double getK();
	double getS();
	double getQ();
	string getOptType();
	double getT();

	// Set private variables' values
	void setR(double&);
	void setVol(double&);
	void setK(double&);
	void setT(double&);
	void setS(double&);
	void setQ(double&);
	void setOptType(string&);

	void interface();

private:
	double r;		// Interest rate
	double price;	// Option price
	double vol;	// Volatility 
	double k;		// Strike price 
	double t;		// Expiry date in years
	double s;		// Current underlying price 
	double q;		// Cost of carry
	string optType;// Call or Put option
	
	// Cumulative Normal Distribution Funcion
	double N(double);

	// Contains BlackScholes Formula
	double euroOptionPrice();
};
#endif EUROPEAN_OPTION_H