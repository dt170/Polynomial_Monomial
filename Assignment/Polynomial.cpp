#include "Polynomial.h"
#include "Monomial.h"

//this number return in [] not found
double zeroNumber=0;


// set the head and tail to null 
Polynomial::Polynomial(){
	head = NULL;
}

Polynomial::Polynomial(const Polynomial& other){
	head = NULL;
	Node *otherPosition=other.head, *currentPosition=head;

	if (!otherPosition)
		return; 
	else {
		head = new Node();
		currentPosition = head;
		currentPosition->monom = new Monomial(0,otherPosition->monom->getDegree());
		this->add(*otherPosition->monom);
		otherPosition = otherPosition->next;
	}

	while (otherPosition) {
		this->add(*otherPosition->monom);
		otherPosition = otherPosition->next;
	}
}

//find bigger or equal degree
Polynomial::Node* Polynomial::findBiggerOrEqual(int degree, Polynomial::Node*& prev) const {
	Node* ret = prev = NULL;
	Node* p = head;
	while (p && p->monom->getDegree() >= degree) {
		prev = ret;
		ret = p;
		p = p->next;
	}
	return ret;
}

// this function is adding new polynomial and also taking care of all cases if needed to delete a node (monomial)
void Polynomial::add(const Monomial &mon){
	Node* prev;
	Node* p = findBiggerOrEqual(mon.getDegree(), prev);
	if (p && p->monom->getDegree() == mon.getDegree()) {
		p->monom->add(mon);
		if (p->monom->getCoefficient() == 0) { // The monomial vanished, remove it from list
			delete p->monom;
			if (prev) {
				prev->next = p->next;
			}
			else {
				head = p->next;
			}
			delete p;
		}
	}
	else {
		Node* newNode = new Node;
		newNode->monom = new Monomial(mon);
		if (p) {
			newNode->next = p->next;
			p->next = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
	}
}

// this print function running all over the list and print the vaules 
void Polynomial::print()const{
	if (!head) {
		cout << "0";
	}
	else {
		Node* current = head;
		while (current) {
			if (current->monom->getCoefficient() > 0 && current != head) cout << '+';
			current->monom->print();
			current = current->next;
		}
	}
}

//operator + pol&pol
 Polynomial Polynomial::operator+(const Polynomial& poly)const{
	Node* currentP = head;
	Node* other = poly.head;

	Polynomial p;
	while (currentP) {
		p.add(*currentP->monom);
		currentP = currentP->next;
	}
	while (other) {
		p.add(*other->monom);
		other=other->next;
	}
	return p;
}

 //operator + pol&mon
 Polynomial Polynomial::operator+(const Monomial& mon)const{

	Polynomial p=*this;
	p.add(mon);
	return p;
}

 //d'tor
Polynomial::~Polynomial(){
	this->deletePolynomial();
}

//operator << print the polynomial
ostream& operator<<(ostream& output, const Polynomial& poly){
	
	poly.print();
	return output;
}

//operator >> get the polynomial from string 
istream& operator>>(istream& input, Polynomial& poly){
	char str[SIZE];
	int flagMonomial = 0;
	int i = 0;
	int flagminus = 0;
	int j = 0;
	cin.getline(str, 256);
	char monomStr[SIZE];
	poly.deletePolynomial();
	while (str[i] != ',' && str[i] != '\0') {
		if (flagMonomial == 0) {
			if (str[i] == '-') {
				flagminus = 1;
				i++;
			}
			if (isdigit(str[i])) {
				while (str[i] != '-' && str[i] != '+') {
					monomStr[j] = str[i];	
					if (str[i] == ',')
						break;
					i++;
					j++;
				}
				monomStr[j] = '\0';
				Monomial m;
				m.updateMonomialString(monomStr, m.getCoefficientReference(), m.getDegreeReference());
				if (flagminus == 1)
					poly.add(-m);
				else
					poly.add(m);
				flagMonomial = 1;
				j = 0;
				flagminus = 0;
			}
		}
		flagMonomial = 0;
		i++;
	}
	return input;
}

//operator - pol&pol
 Polynomial  Polynomial::operator-(const Polynomial & poly) const{
	return *this + (-poly);
}

 //operator - pol&mon
 Polynomial  Polynomial::operator-(const Monomial & mon) const{
	Polynomial p = *this;
	p.add(-mon);
	return p;
}

 //operator -= pol&mon
const Polynomial & Polynomial::operator-=(const Monomial & mon){
	this->add(-mon);
	return *this;
}

//operator += pol&mon
const Polynomial & Polynomial::operator+=(const Monomial & mon){
	this->add(mon);
	return *this;
}

//operator -= pol&pol
const Polynomial& Polynomial::operator-=(const Polynomial& poly){
	Node* current = poly.head;

	while (current) {
		this->add(-(*current->monom));
		current = current->next;
	}
	return *this;
}

//operator += pol&pol
const Polynomial& Polynomial::operator+=(const Polynomial& poly){
	Node* current = poly.head;

	while (current) {
		this->add((*current->monom));
		current = current->next;
	}
	return *this;
}

//operator [] finds the degree and return a reference coe so you may change it .
double& Polynomial::operator[](int num) {
	Node* current=head;
	
	if (!current)
		return zeroNumber;
	while (current){
		if (current->monom->getDegree() == num)
			return current->monom->getCoefficientReference();
		current = current->next;
	}
	return zeroNumber;
}

//operator = pol&pol
 const Polynomial& Polynomial::operator=(const Polynomial& other){
	// if they are the same poly return 
	 if (head == other.head)
		 return *this;
	 else {
		 this->deletePolynomial(); // delete the poly
		 Node *current = other.head;
		 while (current) {
			 this->add(*(current->monom));
				 current = current->next;
		 }
		 return *this;
	 }	
}

 //operator () get result if x=num 
 const double Polynomial::operator()(const int num) const{
	 Node* current = head;
	 double polValue=0;
	 while (current) {

		 polValue += (*(current->monom))(num);
		 current = current->next;
	 }
	 return polValue;
 }

 // delete the polynomial linked list
 void Polynomial::deletePolynomial(){
	 /* deref head_ref to get the real head */
	 Node* current = head;
	 Node* next;

	 while (current != NULL) {
		 next = current->next;
		 delete(current->monom);
		 delete(current);
		 current = next;
	 }
	 head = NULL;
 }

 //operator - unary
 Polynomial Polynomial::operator-() const{

	Polynomial *p = new Polynomial();
	Node *current=head;
	if (!head)
		return *p;

	while (current) {
		p->add(-(*current->monom));
		current=current->next;
	}
	return *p;
}

 //operator == pol&pol
const bool Polynomial::operator==(const Polynomial& poly){

	if (!head && !(poly.head))
		return true;
	else {
		Polynomial::Node* p1 = head;
		Polynomial::Node* p2 = poly.head;

		while (!p1&&!p2) {
			if (p1->monom != p2->monom)
				return false;
			p1 = p1->next;
			p2 = p2->next;
		}
		// checking that both p1 and p2 had noting left if 1 of them not ended then they are not equal
		//example p1=2x p2=2x+1 
		if (!p1 || !p2)
			return false;
		return true;
	}
}

//operator != pol&mol
const bool Polynomial:: operator!=(const Monomial& mono){

	return (*(this->head->monom) != mono);
}

//operator != pol&pol
const bool Polynomial::operator!=(const Polynomial& poly){
	return !(*this==poly);
}
