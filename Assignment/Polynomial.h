#ifndef POLYNOMIAL_H 
#define POLYNOMIAL_H
#include "Monomial.h"

class Polynomial{

public:

	 // c'tors and d'tor
	 Polynomial();
	 Polynomial(const Polynomial& other);
	~Polynomial();

	//functions
	void add(const Monomial &mon);
	void print()const;
	void deletePolynomial();

	//operator function
	friend ostream& operator <<(ostream& output, const Polynomial& poly);
	friend istream& operator >>(istream& input, Polynomial& poly);
	Polynomial operator+(const Polynomial& poly)const; // pol+pol
	Polynomial operator+(const Monomial& mon)const;// pol + mon
	Polynomial operator-(const Polynomial& poly)const; // pol - pol
	Polynomial operator-(const Monomial& mon)const;// pol - mon
	Polynomial operator-()const; // not sure about it
	const Polynomial& operator=(const Polynomial& poly); // pol=pol
	const Polynomial& operator-=(const Monomial& mon);// pol -= mon
	const Polynomial& operator+=(const Monomial& mon);// pol += mon
	const Polynomial& operator-=(const Polynomial& poly);// pol -= mon
	const Polynomial& operator+=(const Polynomial& poly);// pol += mon
	double& operator[](int num);
	const double operator()(const int num) const;
	const bool operator==(const Polynomial& poly); // pol+pol
	const bool operator!=(const Monomial& mono);
	const bool operator!=(const Polynomial& poly); // pol+pol

private:
	typedef struct node {
		Monomial* monom;
		struct node* next;
	} Node;
	Node* head;
	Node* findBiggerOrEqual(int degree, Node*& prev) const;
};
#endif // !POLYNOMIAL_H 

