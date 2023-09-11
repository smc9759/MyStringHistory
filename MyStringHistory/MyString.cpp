#include <iostream>
#include <string.h>

class MyString {
private:
	int string_length;
	char* string_context;
public:
	int return_length() const{ return string_length; };
	MyString(const char* str);
	MyString(char c);
	MyString(const MyString& str);
	~MyString();

	void print();
	void println();

};


MyString::MyString(char c) {
	//MyString str = new char[1];
	//str.string_length = 1;
	//str.string_context[0] = c;
	string_context = new char[1];
	string_length = 1;
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
	string_context = new char[string_length];
	for (int i = 0; i < string_length; i++) {
		string_context[i] = str[i];
	}
}

MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	for (int i = 0; i != string_length; i++) {
		string_context[i] = str.string_context[i];
	}
}

MyString::~MyString() { delete[] string_context; }


void MyString::print()
{
	//std::cout << string_context;
	for (int i = 0; i != string_length; i++) {
		std::cout << string_context[i];
	}
}

void MyString::println()
{
	//std::cout << string_context;
	for (int i = 0; i != string_length; i++) {
		std::cout << string_context[i];
	}
	std::cout << std::endl;
}

void main()
{
	MyString str1("Hello world");

	str1.println();
	str1.print();
}