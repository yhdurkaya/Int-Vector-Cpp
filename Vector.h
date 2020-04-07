//
// Created by YHD on 24.03.2020 
//

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
	int* elements;
	size_t vectorCapacity;
	size_t vectorSize;
public:

	//--------------------------------------------------
	// type members

	class iterator;       //1
	class const_iterator; //2
	//--------------------------------------------------


	//--------------------------------------------------
	// special member functions


	Vector();									//3
	~Vector();									//4
	Vector(const Vector&);						//5
	Vector(Vector&&)noexcept;                   //6
	Vector& operator=(const Vector&);			//7
	Vector& operator=(Vector&&)noexcept;        //8 
	//--------------------------------------------------


	//--------------------------------------------------
	//constructors
	explicit Vector(size_t size, int val);  //9
	Vector(std::initializer_list<int> ilist);   //10
	Vector(const int* pbegin, const int* pend);  //11
	Vector(const_iterator beg, const_iterator end);     //12

    //--------------------------------------------------

	void reserve(size_t new_cap);  //13
	void shrink_to_fit(); //14

	iterator begin(); //15
	iterator end(); //16
	const_iterator begin()const; //17
	const_iterator end()const;  //18


	//setters/mutators
	Vector& operator=(std::initializer_list<int> ilist); //22
	void resize(std::size_t, int val = 0);  //23

	void assign(std::size_t n, int val);  //26
	void assign(std::initializer_list<int> ilist); //27
	void assign(const int* pbeg, const int* pend);  //28

	iterator insert(iterator where, int val); //30
	iterator insert(iterator where, iterator source_beg, iterator source_end); //31

	iterator erase(iterator where); //34
	iterator erase(iterator beg, iterator end); //35
	void push_back(int val); //36
	void pop_pack(); //37

	void swap(Vector& other); //38
	void clear(); //39

	int& front();  //42
	const int& front()const; //43
	int& back();  //44
	const int& back()const; //45
	int& operator[](size_t idx); //46
	const int& operator[](size_t idx)const; //47
	
	//--------------------------------------------------

	int* data(); //50
	const int* data()const; //51

	size_t capacity()const; //52

	size_t size()const;  //53

	bool empty()const; //54

	//--------------------------------------------------
	//type members
	class iterator {
	private:
		int* iter;
	public:
		iterator() = default;
		iterator(int*);
		iterator& operator++();  //60
		iterator operator++(int); //61
		iterator& operator--();  //62
		iterator operator--(int); //63
		int& operator*(); //64
		int& operator[](int n);  //65
		std::ptrdiff_t operator-(iterator); //66
		iterator operator+(int n); //67
		iterator operator-(int n); //68
		iterator& operator+=(int n); //69
		iterator& operator-=(int n); //70
		bool operator<(iterator)const; //71
		bool operator<=(iterator)const; //71
		bool operator>(iterator)const; //71
		bool operator>=(iterator)const; //71
		bool operator==(iterator)const; //71
		bool operator!=(iterator)const; //71
	};

	class const_iterator {
	private:
		int* iter;
	public:
		const_iterator() = default;
		const_iterator(int*);
		iterator& operator++();  //80
		iterator operator++(int); //81
		iterator& operator--();  //82
		iterator operator--(int); //83
		int& operator*(); //84
		int& operator[](int n);  //85
		std::ptrdiff_t operator-(iterator); //86
		const_iterator operator+(int n); //87
		const_iterator operator-(int n); //88
		const_iterator& operator+=(int n);  //89
		const_iterator& operator-=(int n); //90
		bool operator<(const_iterator)const; //91
		bool operator<=(const_iterator)const; //91
		bool operator>(const_iterator)const; //91
		bool operator>=(const_iterator)const; //91
		bool operator==(const_iterator)const; //91
		bool operator!=(const_iterator)const; //91
		//int operator-(const_iterator iter1, const_iterator iter2);//92 SOMEHOW INCLUDES XUTILITY HEADER AND ERRORS
	};

};

#endif