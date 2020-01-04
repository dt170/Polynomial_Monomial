#include "Monomial.h"
#include <assert.h>
#include<string>

int Monomial::numberOfMonomials = 0; // set the counter to zero 

//setting the monomials degrees and coefficient plus adding to counter 1 
Monomial::Monomial(double coe,  int degree){
	assert(degree >= 0);
	setDegree(degree);
	setCoefficient(coe);
	numberOfMonomials++;
}

//get the number of monomials created
int Monomial::getNumberOfMonomials(){
	return numberOfMonomials;
}

// bool function that check if the numbers have the same degree if so its adding them and return true else return false.
bool Monomial::add(const Monomial &mon)  {
	if (isDegreeEqual(mon)) {
		this->coefficientNum = this->coefficientNum + mon.coefficientNum;
		return true;
	}
	else
		return false;
}

Monomial::Monomial(const Monomial& mon){
	setDegree(mon.degreeNum);
	setCoefficient(mon.coefficientNum);
	numberOfMonomials++;
}

// print function to handle all cases of the monomials
void Monomial::print() const{
	switch (this->degreeNum) {
	case 0:
		cout << this->coefficientNum;
		break;
	case 1:
		if (this->coefficientNum != 1)
			cout << this->coefficientNum << "*x";
		else
			cout << "x";
		break;
	default:
		if (this->coefficientNum != 1 && this->coefficientNum!=0)
			cout << this->coefficientNum << "*x^" << this->degreeNum;
		else if (this->coefficientNum == 0) // if the number is 0 dont print .
			return;
		else
			cout << "x^" << this->degreeNum;
	}
}

// set the degree number
void Monomial::setDegree(int degree){
	this->degreeNum = degree;
}

// set the Coefficient number 
void Monomial::setCoefficient(double Coe){

	this->coefficientNum = Coe;
}

//get the degree of the current monomial 
int Monomial::getDegree()const {
	return degreeNum;
}

//get the Coefficient of the current monomial 
double Monomial::getCoefficient()const{
	return this->coefficientNum;

}

// when the destructor actived remove 1 monomial from counter
Monomial::~Monomial(){
	numberOfMonomials--;
}

// operator ==
bool Monomial::operator==(const Monomial& mon) const{

	return (this->coefficientNum==mon.coefficientNum && this->degreeNum==mon.degreeNum);
}\

// operator != using operator ==
bool Monomial::operator!=(const Monomial& mon) const{

	return !(*this==mon);
}

// operator = 
const Monomial& Monomial::operator=(const Monomial& mon){
	setCoefficient(mon.coefficientNum);
	setDegree(mon.degreeNum);
	return *this;
}

// operator +
 Monomial Monomial::operator+(const Monomial& mon)const{

	if (this->isDegreeEqual(mon)) 
		return Monomial(coefficientNum+mon.coefficientNum,degreeNum);
	else
	return *this;
}

 // operator -
Monomial Monomial::operator-(const Monomial& mon)const{
	return *this + (-mon); // using unary to 
}

// operator *
Monomial Monomial::operator*(const Monomial& mon)const{
	return Monomial(this->coefficientNum*mon.coefficientNum, this->degreeNum + mon.degreeNum);
}

// operator +=
const Monomial& Monomial::operator+=(const Monomial& mon){
	*this = *this + mon;
	return *this;
}

// operator *=
const Monomial& Monomial::operator*=(const Monomial& mon){
	*this = *this * mon;
	return *this;
}

// operator -=
const Monomial& Monomial::operator-=(const Monomial& mon){
	*this = *this - mon;
	return *this; 
}

// get coe reference so we can change it later
double& Monomial::getCoefficientReference(){
	return coefficientNum;	
}

//get deg reference so we can change it later
int& Monomial::getDegreeReference()
{
	return degreeNum;
}

// operator - unary
Monomial Monomial::operator-()const{
	return Monomial(-this->coefficientNum,this->degreeNum);
}

//update coe and degree from text 
void Monomial::updateMonomialString(char* str, double& c, int& d){
	double coe = 0;
	int degree = 0;
	int flagCoe = 0;
	int i = 0;
	int flagminus = 0;
	int j=1;

	while (str[i] != '\0') {
		if ((str[i] == 'x' || str[i] == 'X') && flagCoe == 0) { // the first char was x meaning coe is 1 
			flagCoe = 1;
			coe = 1;
		}
		if (str[i] == '-')
			flagminus = 1;
		if (isdigit(str[i]) && flagCoe == 0) {
			while (isdigit(str[i])) {
				coe *= 10;
				coe += (double)str[i] - '0';
				i++;
			}
			flagCoe = 1;
			if (str[i] == '.') { //if its a double number 
				i++;
				while (isdigit(str[i])) {
					j*= 10;
					coe +=  ((double)str[i] - '0')/j  ;
					i++;
				}
			}
		}
		if (str[i] == '\0') {
			break;
		}
		if (str[i] == 'x' || str[i] == 'X')
			degree = 1;

		if (str[i] == '^')
			degree = 0;
		if (isdigit(str[i])) {
			while (isdigit(str[i])) {
				degree *= 10;
				degree += (int)str[i] - '0';
				i++;
			}
		}
		if (str[i] == '\0') {
			break;
		}
		i++;
	}

	d = degree;
	if (flagminus == 1)
		c = -coe;
	else
		c = coe;
}

// operator () to get result of x=num
double Monomial::operator()(double x)const{
		return (getCoefficient() * pow(x, getDegree()));
}

//check if equal degrees
bool Monomial::isDegreeEqual(const Monomial& mon)const
{
	return (this->degreeNum==mon.degreeNum);
}

//check if equal coe
bool Monomial::isCoefficientEqual(const Monomial& mon)
{
	return (this->coefficientNum==mon.coefficientNum);
}

//operator << print monomial
ostream& operator<<(ostream& output, const Monomial& mon){
	mon.print();
	return output;
}

//operator >> get monomial from string 
istream& operator>>(istream& input, Monomial& mon){
	char str[SIZE];
	cin.getline(str, SIZE);
	mon.updateMonomialString(str, mon.coefficientNum, mon.degreeNum);

	return input;
}

