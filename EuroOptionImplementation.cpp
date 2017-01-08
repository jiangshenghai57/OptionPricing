#include <iostream>
#include "EuroOption.h"
#include <iomanip>
using namespace std;

// Default Constructor
EuropeanOption::EuropeanOption() {
	r = 0.0;
	vol = 0.0;
	k = 0.0;
	t = 0.0;
	s = 0.0;
	q = 0.0;
}

double EuropeanOption::getR() {
	return r;	// Return interest rate variable r
}

double EuropeanOption::getVol() {
	return vol;	// Return volatility of the underlying
}
double EuropeanOption::getK() {
	return k;	// Return the strike price
}

double EuropeanOption::getS() {
	return s;	// Return the underlying price
}

double EuropeanOption::getQ() {
	return q;	// Retrun the dividend yield
}

string EuropeanOption::getOptType() {
	return optType;	// Return option type (call or put)
}

double EuropeanOption::getT() {
	return t;
}

void EuropeanOption::setR(double &newR) {
	r = newR;
}

void EuropeanOption::setVol(double &newVol) {
	vol = newVol;
}

void EuropeanOption::setK(double &newK) {
	k = newK;
}

void EuropeanOption::setT(double &newT) {
	t = newT;
}

void EuropeanOption::setS(double &newS) {
	s = newS;
}

void EuropeanOption::setQ(double &newQ) {
	q = newQ;
}

void EuropeanOption::setOptType(string &newOptType) {
	optType = newOptType;
}

void EuropeanOption::interface() { 
	cout << "What is the interest rate?" << endl;
	cin >> r; setR(r);
	cout << "Interest rate is " << fixed << setprecision(2) << getR() * 100 << "%" << endl << endl;

	cout << "What it the current asset price?" << endl;
	cin >> s; setS(s);
	cout << "The asset price is $" << getS() << endl << endl;

	cout << "What is the strike price?" << endl;
	cin >> k; setK(k);
	cout << "The strike price is $" << getK() << endl << endl;

	cout << "How long is the option?" << endl;
	cin >> t; setT(t);
	cout << "Time for the option is " << getT() << " year." << endl << endl;

	cout << "What is the volitality of the underlying?" << endl;
	cin >> vol; setVol(vol);
	cout << "The underlying volatility is " << getVol() * 100 << "%" << endl << endl;

	cout << "Is there any dividend yield?" << endl;
	cin >> q; setQ(q);
	cout << "The underlying yield is " << getQ() * 100 << "%" << endl << endl;

	cout << "Is this a call or a put option?" << endl;
	cin >> optType; setOptType(optType);
	cout << "The underlying is a " << getOptType() << " option" << endl << endl;

	cout << "European option price is " << fixed << setprecision(10) << euroOptionPrice() << endl << endl;
}

double EuropeanOption::N(double x) {
	// Calculating PDF
	const double PI = 3.141592653589793238462643;
	double L, K, w;
	/* constants */
	double const a1 = 0.31938153, a2 = -0.356563782, a3 = 1.781477937;
	double const a4 = -1.821255978, a5 = 1.330274429;

	L = fabs(x);
	K = 1.0 / (1.0 + 0.2316419 * L);
	w = 1.0 - 1.0 / sqrt(2 * PI) * exp(-L *L / 2) * (a1 * K + a2 * K *K + a3 * pow(K, 3) + a4 * pow(K, 4) + a5 * pow(K, 5));

	if (x < 0) {
		w = 1.0 - w;
	}
	return w;
}

double EuropeanOption::euroOptionPrice() {
	// BlackScholes formula
	double d1 = 0.0;
	double d2 = 0.0;
	d1 = (log(s / k) + (r - q + 0.5 * pow(vol, 2)) * t) / (sqrt(t) * vol);
	d2 = d1 - sqrt(t) * vol;
	if (optType == "Call" || optType == "call") {
		price = s * exp(-q * t) * N(d1) - k * exp(-r * t) * N(d2);
		return price;
	}
	else {
		price = k * exp(-r * t) * N(-d2) - s * exp(-q * t) * N(-d1);
		return price;
	}
}