#include <iostream>
#include <string.h>

class MyString {
private:
	int string_length;
	char* string_context;
	int memory_capacity;   // 현재 할당된 용량
public:
	MyString(const char* str);
	MyString(char c);
	MyString(const MyString& str);
	~MyString();
	MyString& assign(const char* str);
	MyString& assign(const MyString& str);
	MyString& addString(const char* str);

	void print() const;
	void println() const;
	int capacity();
	int length() const;
	void reserve(int size);
	char at(int i) const;
};


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

void main()
{

	MyString str1("very very very long string");
	str1.reserve(30);

	std::cout << "Capacity : " << str1.capacity() << std::endl;
	std::cout << "String length : " << str1.length() << std::endl;
	str1.println();

	str1.addString("Tail Added Tail Added Tail Added");
	str1.println();

}