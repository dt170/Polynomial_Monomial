#ifndef _MONOMIAL_H
#define _MONOMIAL_H
#include<iostream>
#include<math.h>
using namespace std;

//define char size.
constexpr auto SIZE = 256;

class Monomial
{
public:
	//c 'tor and d'tor
	Monomial(const Monomial& other);
	Monomial(double c = 0, int d = 0); // setting default values 
	~Monomial();

	//functions
	static int getNumberOfMonomials();
	bool add(const Monomial &Mon);
	void print()const;
	void setDegree(int);
	void setCoefficient(double);
	int getDegree() const;
	double getCoefficient()const;
	bool isDegreeEqual(const Monomial& mon)const;
	bool isCoefficientEqual(const Monomial& mon);
	double& getCoefficientReference();
	int& getDegreeReference();
	void updateMonomialString(char* str, double& c, int& d);

	// operators 
	friend ostream& operator <<(ostream& output, const Monomial& mon);
	friend istream& operator >>(istream& intput,  Monomial& mon);
	bool operator ==(const Monomial& mon)const;
	bool operator !=(const Monomial& mon)const;
	const Monomial &operator=(const Monomial& mon);
    Monomial operator-(const Monomial& mon)const;
	Monomial operator+(const Monomial& mon)const;
	Monomial operator*(const Monomial& mon)const;
	Monomial operator-()const;
	const Monomial &operator+=(const Monomial& mon);
	const Monomial& operator*=(const Monomial& mon);
	const Monomial& operator-=(const Monomial& mon);
	double operator()(double x)const;

private:
	double coefficientNum;
	int degreeNum;
	static int numberOfMonomials;
};

#endif // !_MONOMIAL_H
