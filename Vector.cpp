//
// Created by YHD on 24.03.2020 
//

#include <iostream>
#include <initializer_list>

#include "Vector.h"

//Default Constructor
Vector::Vector() : elements(0), vectorCapacity(0), vectorSize(0) {
	std::cout << "Vector : Default Constructor\n";
}//3

//Destructor
Vector::~Vector() {
	std::cout << "Vector : Destructor\n";

	delete[] elements;
	std::cout << "Deleted\n";
}//4

//Copy Constructor
Vector::Vector(const Vector& other) : elements(new int[other.vectorSize]), vectorSize(other.vectorSize), vectorCapacity(other.vectorCapacity) {
	std::cout << "Vector : Copy Constructor\n";
	
	for (int index = 0; index < other.vectorSize; ++index) {
		elements[index] = other.elements[index];
	}
}//5

//Move Constructor
Vector::Vector(Vector&& other)noexcept : elements(std::exchange(other.elements, nullptr)), vectorCapacity(std::exchange(other.vectorCapacity, 0)),
									vectorSize(std::exchange(other.vectorSize, 0)){
	std::cout << "Vector : Move Constructor\n";
}//64


//Copy Assignment Operator	7
Vector& Vector::operator=(const Vector& other) {
	std::cout << "Vector : Copy Assignment Operator\n";
	
	if (this == &other) {
		return *this;
	}

	if (other.vectorSize <= vectorCapacity) {
		for (int index = 0; index < other.vectorSize; ++index) {
			elements[index] = other.elements[index];
			vectorSize = other.vectorSize;
			return *this;
		}
	}

	int* newElements = new int[other.vectorSize];

	for (int index = 0; index < other.vectorSize; ++index) {
		newElements[index] = other.elements[index];
	}

	delete[] this->elements;

	vectorSize = other.vectorSize;
	vectorCapacity = other.vectorCapacity;
	elements = newElements;

	return *this;
}//7

//Move Assignment Operator
Vector& Vector::operator=(Vector&& other) noexcept {
	std::cout << "Vector : Move Assignment Operator\n";
	
	if (this != &other) {
		delete[] elements;

		elements = other.elements;
		vectorCapacity = other.vectorCapacity;
		vectorSize = other.vectorSize;

		other.elements = nullptr;
		other.vectorCapacity = 0;
		other.vectorSize = 0;
	}
	return *this;
}//8

//Fill Constructor
Vector::Vector(size_t size, int val = 0) : elements(new int[size]), vectorCapacity(size), vectorSize(size){
	std::cout << "Vector : Fill Constructor\n";
	
	for (int index = 0; index < size; ++index) {
		elements[index] = val;
	}
}//9

//Contructor with initalizer_list parameter
Vector::Vector(std::initializer_list<int> ilist) : elements(new int[ilist.size()]), vectorSize(ilist.size()),
													vectorCapacity(static_cast<size_t>((ilist.size())* 1.5 +1 )) {
	std::cout << "Vector : std::initializer_list Constructor\n";
	
	std::copy(ilist.begin(), ilist.end(), elements);
}//10

//Constructor with range parameter pointer
Vector::Vector(const int* pbegin, const int* pend) : elements(new int[pend - pbegin]), vectorSize(pend - pbegin) ,
														vectorCapacity(static_cast<size_t>((pend-pbegin) *1.5 + 1)) {
	std::cout << "Vector : Range Constructor\n";

	std::copy(pbegin, pend, elements);
}//11

/*
//Constructor with range parameter const_iterator
Vector::Vector(const_iterator beg, const_iterator end) : elements(new int[end-beg]), vectorSize(end-beg), vectorCapacity(static_cast<size_t>((end-beg) * 1.5 + 1)){
	std::cout << "Vector : Range Constructor with Const Iterators\n";

	std::copy(*beg, *end, elements);
}//12
*/
//Vector sýnýfý için reserve iþlemi

void Vector::reserve(size_t new_cap) {
	if ( vectorCapacity < new_cap) {
		int* newAlloc = new int[new_cap];

		for (int index = 0; index < vectorSize; ++index) {
			newAlloc[index] = elements[index];
		}

		this->vectorCapacity = new_cap;
		delete[] elements;
		this->elements = newAlloc;
	}
}//13

//Shrink function to fit
void Vector::shrink_to_fit() {
	int * newAlloc = new int[vectorSize];

	for (int index = 0; index < vectorSize; ++index) {
		newAlloc[index] = elements[index];
	}

	delete[] elements;

	elements = newAlloc;

	vectorCapacity = vectorSize;
	
} //14

//Begin function for vector iterator
Vector::iterator Vector::begin() {
	return Vector::iterator(&elements[0]);
}//15

//End function for vector iterator
Vector::iterator Vector::end() {
	return Vector::iterator(&elements[vectorSize]);
} //16

//Const begin function for vector iterator
Vector::const_iterator Vector::begin()const {
	return Vector::const_iterator(&elements[0]);
} //17

//Const end function for vector iterator
Vector::const_iterator Vector::end()const {
	return Vector::const_iterator(&elements[vectorSize]);
} //18

//Assignment with initializer list parameter
Vector& Vector::operator=(std::initializer_list<int> ilist) {
	for (size_t index = 0; index < ilist.size(); ++index) {
		elements[index] = *(ilist.begin() + index);
	}
	return *this;
} //22

//resize function to change the element number of vector
void Vector::resize(std::size_t newSize, int val) {
	
	(newSize);

	for (size_t index = vectorSize; index < newSize; ++index) {
		elements[index] = 0;
	}

	vectorSize = newSize;
}  //23

//Assign function for vector
void Vector::assign(std::size_t n, int val) {
	for (size_t index = 0; index < n; ++index) {
		elements[index] = val;
	}
}  //26

//Assign function for vector
void Vector::assign(std::initializer_list<int> ilist) {
	for (size_t index = 0; index < ilist.size(); ++index) {
		elements[index] = *(ilist.begin() + index);
	}
} //27

//Assign function for vector
void Vector::assign(const int* pbeg, const int* pend) {
	for (size_t index = 0; index < pend-pbeg; ++index) {
		elements[index] = *(pbeg + index);
	}
}  //28

//Insert function for vector
Vector::iterator Vector::insert(iterator where, int val) {
	for (iterator check = this->end(); check >= where; --check) {
		std::cout << "Insert function" << std::endl;
		if (check == where) {
			*check = val;
		}
		else {
			*check = *(check - 1);
		}
	}
	vectorSize++;
	return where;
} //30

//Insert function for vector
Vector::iterator Vector::insert(iterator where, iterator source_beg, iterator source_end) {
	for (iterator check = this->end()-1; check >= where; --check) {
		*(check + (source_end - source_beg) +1) = *check;
		vectorSize++;
	}
	for (int iter = 0; iter <= source_end - source_beg; ++iter) {
		*(where + iter) = *(source_beg + iter);
	}
	
	return where;
} //31

//Erase function for vector
Vector::iterator Vector::erase(Vector::iterator where) {
	iterator check = where+1;

	while (check != this->end()) {
		*(check-1) = *check;
		++check;
	}

	elements[vectorSize-1] = NULL;
	resize(vectorSize - 1);

	return where;
} //34


//Erase function for vector
Vector::iterator Vector::erase(Vector::iterator beg, Vector::iterator end) {
	iterator check = this->begin();

	for (; check <= this->end(); ++check) {
		if (check == beg) {
			for (iterator copy = beg; copy <= this->end(); ) {
				*copy = *(++copy);
			}
			break;
		}
	}
	return check;
} //35


//Push function for vector
void Vector::push_back(int val) {
	if (vectorCapacity == 0) {
		reserve(3);
	}
	else if (vectorSize == vectorCapacity) {
		reserve(vectorCapacity * 2);
	}

	elements[vectorSize] = val;
	vectorSize++;
} //36

//Pop function for vector
void Vector::pop_pack() {
	elements[vectorSize] = NULL;
	vectorSize--;
} //37

//Swap function for vector
void Vector::swap(Vector& other) {
	int* tempElements = this->elements;
	size_t tempVectorSize = this->vectorSize;
	size_t tempVectorCapacity = this->vectorCapacity;

	this->elements = other.elements;
	this->vectorSize = other.vectorSize;
	this->vectorCapacity = other.vectorCapacity;

	other.elements = tempElements;
	other.vectorSize = tempVectorSize;
	other.vectorCapacity = tempVectorCapacity;
} //38

//clear function for vector
void Vector::clear() {

	for (iterator it = this->begin(); it != this->end(); ) {
		this->erase(it);
	}
} //39

//Front function for vector, returns the first element in the vector
int& Vector::front() {
	return *begin();
}  //42

//Front function for vector, returns the first element in the vector
const int& Vector::front()const {
	return *begin();
} //43

//Back function for vector, returns the last element in the vector
int& Vector::back() {
	return *(end()-1);
}  //44

//Back function for vector, returns the last element in the vector
const int& Vector::back()const {
	return *(end() - 1);
} //45

//
int& Vector::operator[](size_t idx) {
	return *(elements + idx);
} //46

const int& Vector::operator[](size_t idx)const {
	return *(elements + idx);
} //47

int* Vector::data() {
	return elements;
} //50

const int* Vector::data()const {
	return elements;
} //51

size_t Vector::capacity()const {
	return vectorCapacity;
} //52

size_t Vector::size()const {
	return vectorSize;
}  //53

bool Vector::empty()const {
	if (vectorSize == 0) {
		return true;
	}
	return false;
} //54

//Constructor for int*
Vector::iterator::iterator(int* other) : iter(other) {}

Vector::iterator& Vector::iterator::operator++() {
	++iter;
	return *this;
}//60

Vector::iterator Vector::iterator::operator++(int) {
	iterator temp{ *this };
	++(*this);
	return temp;
}//61

Vector::iterator& Vector::iterator::operator--() {
	--iter;
	return *this;
}//62

Vector::iterator Vector::iterator::operator--(int) {
	iterator temp{ *this };
	--(*this);
	return temp;
}//63

int& Vector::iterator::operator*() {
	return *iter;
}//64

int& Vector::iterator::operator[](int n) {
	return *(iter + n);
}//65

//NOT SURE IF IT WORKS
std::ptrdiff_t Vector::iterator::operator-(iterator other) {
	return iter - other.iter;
} //66

Vector::iterator Vector::iterator::operator+(int n) {
	iterator temp{};
	temp.iter = iter + n;
	return temp;
} //67

Vector::iterator Vector::iterator::operator-(int n) {
	iterator temp{};
	temp.iter = iter - n;
	return temp;
} //68

Vector::iterator& Vector::iterator::operator+=(int n) {
	iter = iter + n;
	return *this;
} //69

Vector::iterator& Vector::iterator::operator-=(int n) {
	iter = iter - n;
	return *this;
} //70

bool Vector::iterator::operator<(iterator other)const {
	if (iter < other.iter) {
		return true;
	}
	return false;
} //71

bool Vector::iterator::operator<=(iterator other)const {
	if (iter <= other.iter) {
		return true;
	}
	return false;
} //71

bool Vector::iterator::operator>(iterator other)const {
	if (iter > other.iter) {
		return true;
	}
	return false;
} //71

bool Vector::iterator::operator>=(iterator other)const {
	if (iter >= other.iter) {
		return true;
	}
	return false;
} //71

bool Vector::iterator::operator==(iterator other)const {
	if (iter == other.iter) {
		return true;
	}
	return false;
} //71

bool Vector::iterator::operator!=(iterator other)const {
	if (iter != other.iter) {
		return true;
	}
	return false;
} //71

//Constructor for int*
Vector::const_iterator::const_iterator(int* other) : iter(other) {}

//Iterator& Const_Iterator::operator++() {
Vector::iterator& Vector::const_iterator::operator++() {
	iterator newIter(++(this->iter));
	return newIter;
}  //80

Vector::iterator Vector::const_iterator::operator++(int) {
	iterator newIter((this->iter)++);
	return newIter;
} //81

Vector::iterator& Vector::const_iterator::operator--() {
	iterator newIter(--(this->iter));
	return newIter;
}  //82

Vector::iterator Vector::const_iterator::operator--(int) {
	iterator newIter((this->iter)--);
	return newIter;
} //83

int& Vector::const_iterator::operator*() {
	return *iter;
} //84

int& Vector::const_iterator::operator[](int n) {
	return *(iter + n);
}  //85

std::ptrdiff_t Vector::const_iterator::operator-(iterator other) {
	return static_cast<__int64>(*iter) - static_cast<__int64>(*other);
} //86

Vector::const_iterator Vector::const_iterator::operator+(int n) {
	const_iterator newIter((this->iter) + n);
	return  newIter;
} //87

Vector::const_iterator Vector::const_iterator::operator-(int n) {
	const_iterator newIter((this->iter) - n);
	return  newIter;
} //88

Vector::const_iterator& Vector::const_iterator::operator+=(int n) {
	iter += n;
	return *this;
}  //89

Vector::const_iterator& Vector::const_iterator::operator-=(int n) {
	iter -= n;
	return *this;
} //90

bool Vector::const_iterator::operator<(const_iterator other)const {
	if (iter < other.iter) {
		return true;
	}
	return false;
} //91

bool Vector::const_iterator::operator<=(const_iterator other)const {
	if (iter <= other.iter) {
		return true;
	}
	return false;
} //91

bool Vector::const_iterator::operator>(const_iterator other)const {
	if (iter > other.iter) {
		return true;
	}
	return false;
} //91

bool Vector::const_iterator::operator>=(const_iterator other)const {
	if (iter >= other.iter) {
		return true;
	}
	return false;
} //91

bool Vector::const_iterator::operator==(const_iterator other)const {
	if (iter == other.iter) {
		return true;
	}
	return false;
} //91

bool Vector::const_iterator::operator!=(const_iterator other)const {
	if (iter != other.iter) {
		return true;
	}
	return false;
} //91
/*
//Substraction operator for const iterators----- SOMETHING BROKEN ABOUT XUTILITY HEADER GOD KNOWS WHY
int Vector::operator-(Vector::const_iterator constIter1, Vector::const_iterator constIter2) {
	return static_cast<int>(constIter1.iter - constIter2.iter);
}//92
*/