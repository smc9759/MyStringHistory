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
	MyString& assign(const char* str);

	void print() const;
	void println() const;

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
	string_context = new char[string_length+1];
	for (int i = 0; i != string_length; i++) {
		string_context[i] = str[i];
	}
	string_context[string_length] = 0;

}

MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	string_context = new char[string_length+1];

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
	std::cout << string_context;
	
	//////////////////////////////////
	//Used when array is non-null-terminated string

	//for (int i = 0; i != string_length; i++) {
	//	//std::cout << string_context[i];
	//}
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
	}
	for (int i = 0; i != new_strlength; i++) {
		string_context[i] = str[i];
	}
	string_length = new_strlength;
	string_context[string_length] = 0;
	return *this;
}

void main()
{
	MyString str1("Hello world");
	MyString str2(str1);

	str1.println();
	str2.println();

	str1.assign("UnderWorld UnderWorld UnderWOrld");
	str1.println();
}