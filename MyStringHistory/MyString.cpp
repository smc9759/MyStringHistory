#include <iostream>
#include <string.h>

class MyString {
private:
	int string_length;
	char* string_context;
	int memory_capacity;   // ���� �Ҵ�� �뷮
public:
	MyString(const char* str);
	MyString(char c);
	MyString(const MyString& str);
	explicit MyString(int capacity);
	~MyString();
	MyString& assign(const char* str);
	MyString& assign(const MyString& str);
	MyString& addString(const char* str);
	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);
	MyString& erase(int loc, int num);

	void print() const;
	void println() const;
	int capacity();
	int length() const;
	void reserve(int size);
	char at(int i) const;
	int find(int find_from, MyString& str) const;
	int compare(const MyString& str) const;

	bool operator==(MyString& str);
};

class Complex {
private:
	double real, img;

public:
	Complex(double real, double img) : real(real), img(img) {}
};

MyString::MyString(int capacity) {
	string_context = new char[capacity];
	string_length = 0;
	memory_capacity = capacity;
	std::cout << "Capacity : " << capacity << std::endl;
}

MyString::MyString(char c) {
	//MyString str = new char[1];
	//str.string_length = 1;
	//str.string_context[0] = c;
	string_context = new char[1];
	string_length = 1;
	memory_capacity = 1;
	string_context[0] = c;

}
MyString::MyString(const char* str) {
	/*int count = 0;
	for (int i = 0; str[count] != NULL; i++) {
		count++;
	}
	MyString str1 = new char[count];
*/
	string_length = strlen(str);
	memory_capacity = string_length;
	string_context = new char[string_length+1];
	for (int i = 0; i != string_length; i++) {
		string_context[i] = str[i];
	}
	string_context[string_length] = 0;

}

MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	string_context = new char[string_length+1];
	memory_capacity = string_length;

	for (int i = 0; i != string_length; i++) {
		string_context[i] = str.string_context[i];
	}
	string_context[string_length] = 0;
}

MyString::~MyString() { delete[] string_context; }


void MyString::print() const
{
	//std::cout << string_context;
	for (int i = 0; i != string_length; i++) {
		std::cout << string_context[i];
	}
}

void MyString::println() const
{
	//std::cout << string_context;
	
	//////////////////////////////////
	//Used when array is non-null-terminated string

	for (int i = 0; i != string_length; i++) {
		std::cout << string_context[i];
	}
	std::cout << std::endl;
}

MyString& MyString::assign(const char* str)
{
	//memset(string_context, 0, sizeof(char)*string_length);
	//delete[] string_context;
	int new_strlength = strlen(str);
	if (new_strlength > string_length) {
		delete[] string_context;
		string_context = new char[new_strlength+1];
		memory_capacity = string_length;
	}
	for (int i = 0; i != new_strlength; i++) {
		string_context[i] = str[i];
	}
	string_length = new_strlength;
	string_context[string_length] = 0;
	return *this;
}

MyString& MyString::assign(const MyString& str) {
	int new_strlength = strlen(str.string_context);
	if (new_strlength > string_length) {
		delete[] string_context;
		string_context = new char[new_strlength + 1];
		memory_capacity = str.string_length;
	}
	for (int i = 0; i != new_strlength; i++) {
		string_context[i] = str.string_context[i];
	}
	string_length = new_strlength;
	string_context[string_length] = 0;
	return *this;
}

int MyString::capacity() { return memory_capacity; }

int MyString::length() const { return string_length; }

void MyString::reserve(int size) {
	if (size > memory_capacity) {
		char *prev_string_content = string_context;

		string_context = new char[size];
		memory_capacity = size;

		for (int i = 0; i != string_length; i++)
			string_context[i] = prev_string_content[i];

		delete[] prev_string_content;
	}
	string_context[string_length] = 0;
}

char MyString::at(int i) const {
	if (i >= string_length || i < 0)
		return NULL;
	else
		return string_context[i];
}

MyString& MyString::addString(const char* str) {
	if (string_length + strlen(str) > memory_capacity) {
		reserve(memory_capacity * 2);
	}
	for (int i = 0; i != strlen(str); i++) {
		string_context[string_length + i] = str[i];
	}
	string_context[string_length + strlen(str)] = 0;
	string_length += strlen(str);
	return *this;
}

MyString& MyString::insert(int loc, const MyString& str) {
	if (loc <0 || loc > string_length)
		return *this;
	if (string_length + str.string_length > memory_capacity) {
		reserve(memory_capacity * 2);

		char* prev_string_content = string_context;
		string_context = new char[memory_capacity];

		int i,j ;
		for (i = 0; i < loc; i++) {
			string_context[i] = prev_string_content[i];
		}
		for (j = 0; j != str.string_length; j++) {
			string_context[i + j] = str.string_context[j];
		}
		for (; i < string_length; i++) {
			string_context[i + j] = prev_string_content[i];
		}
		string_length += str.string_length;
	}
	
	return *this;
}

MyString& MyString::insert(int loc, const char* str) {
	MyString temp(str);
	return insert(loc, temp);
}

MyString& MyString::insert(int loc, char c) {
	MyString temp(c);
	return insert(loc, temp);
}

MyString& MyString::erase(int loc, int num) {
	if (num < 0 || loc < 0 || loc > string_length) return *this;

	// ����ٴ� ���� �ܼ��� ���� ���ڵ��� ������ ���� �´ٰ�
	// �����ϸ� �˴ϴ�.

	for (int i = loc + num; i < string_length; i++) {
		string_context[i - num] = string_context[i];
	}

	string_length -= num;
	return *this;
}

int MyString::find(int find_from, MyString& str) const {
	if (find_from<0 || find_from> string_length) return -1;
	static int str_index = 0;
	//1. original
	int i, j;
	for (i = find_from; i < string_length- str.string_length; i++) {
		for (j = 0; j < str.string_length; j++) {
			if (string_context[i + j] != str.string_context[j]) {
				break;
			}
		}
		if (j == str.string_length) return i;
	}
	return -1;

	//2. pi
	//orginal understanding needed first
}
#include <algorithm>
int MyString::compare(const MyString& str) const {
	// (*this) - (str) �� �����ؼ� �� 1, 0, -1 �� �� ����� �����Ѵ�
	// 1 �� (*this) �� ���������� �� �ڿ� �´ٴ� �ǹ�. 0 �� �� ���ڿ�
	// �� ���ٴ� �ǹ�, -1 �� (*this) �� ���������� �� �տ� �´ٴ� �ǹ��̴�.

	for (int i = 0; i < std::min(string_length, str.string_length); i++) {
		if (string_context[i] > str.string_context[i])
			return 1;

		else if (string_context[i] < str.string_context[i])
			return -1;
	}

	// ���� ���� �ߴµ� ������ �ʾҴٸ� �� �κ� ���� ��� �Ȱ��� ���� �ȴ�.
	// ���� ���ڿ� ���̰� ���ٸ� �� ���ڿ��� �ƿ� ���� ���ڿ��� �ȴ�.

	if (string_length == str.string_length) return 0;

	// ����� abc �� abcd �� ũ�� �񱳴� abcd �� �� �ڿ� ���� �ȴ�.
	else if (string_length > str.string_length)
		return 1;

	return -1;
}

bool MyString::operator==(MyString& str) {
	return !compare(str);  // str �� ������ compare ���� 0 �� �����Ѵ�.
}

void main()
{
	MyString str1("very very very long string");
	MyString str2("My Life has begun");
	MyString str3("My Life has begun");

	if (str1 == str2)
		std::cout << "str1 �� str2 ����." << std::endl;
	else
		std::cout << "st1 �� str2 �� �ٸ���." << std::endl;

	if (str2 == str3)
		std::cout << "str2 �� str3 �� ����." << std::endl;
	else
		std::cout << "st2 �� str3 �� �ٸ���" << std::endl;
}