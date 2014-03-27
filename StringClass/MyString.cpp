#include "MyString.h"

/*
StdConstructor for MyString
/**/
String::String()
: m_len(0)
, m_start(0)
, m_string(nullptr)
{
	cout << "	<MyString instance created>" << endl;
}

/*
CopyConstructor for MyString
/**/
String::String(const String& s)
: m_len(s.m_len)
, m_start(s.m_start)
, m_string(s.m_string)
{
	cout << "	<Copy of MyString instance created>" << endl;
}

/*
TypeConvertConstructor for MyString
/**/
String::String(const char* c)
: m_start(0)
, m_len(0)
{
	while (*(c + m_len) != 0x00){
		m_len++;
	}
	unique_ptr<char[]> tmp (new char[m_len + 1]);
	for (size_t i = 0; i <= m_len; i++){
		tmp[i] = c[i];
	}
	m_string = move(tmp);
	cout << "	<Type conversion of MyString instance>" << endl;
}

/*
MoveConstructor for MyString
/**/
String::String(String&& s)
: m_start(s.m_start)
, m_len(s.m_len)
, m_string(move(s.m_string))
{
	s.m_len = 0;
	s.m_start = 0;
	cout << "	<MyString MoveConstructor called>" << endl;
}

/*
charAt Method
/**/
char String::charAt(size_t i) const {
	if (i < m_len) {
		return m_string.get()[i];
	}
	else {
		throw exception("Index out of bounds exception!");
	}
}

/*
compareTo Method
/**/
int String::compareTo(const String& s) const {

	int comparator = 0;
	size_t t = 0;

	while (t < s.m_len && t < m_len && comparator == 0){
		if (m_string.get()[t] > s.m_string.get()[t]){
			comparator = 1;
		}
		else if (m_string.get()[t] < s.m_string.get()[t]){
			comparator = -1;
		}
		t++;
	}
	if (comparator == 0){
		if (s.m_len > m_len)
			comparator = -1;
		else if (s.m_len < m_len)
			comparator = 1;
	}
	return comparator;
}

/*
concatenate Method (char)
/**/
String String::concat(char c) const{

	String s;
	s.m_len = m_len + 1;
	unique_ptr<char[]> t (new char[s.m_len + 1]);

	for (size_t i = 0; i < m_len; i++){
		t[i] = m_string.get()[i];
	}
	t[m_len] = c;
	t[m_len + 1] = 0x00;

	s.m_string = move(t);

	return move(s);
}

/*
concatenate Method (String)
/**/
String String::concat(const String& s) const{
	
	String concat;
	concat.m_len = m_len + s.m_len;
	unique_ptr <char[]> t(new char[concat.m_len + 1]);

	for (size_t i = 0; i < m_len; ++i){
		t[i] = m_string.get()[i];
	}
	for (size_t i = 0; i < s.m_len; ++i){
		t[i + m_len] = s.m_string.get()[i];
	}
	t[m_len + s.m_len] = 0x00;
	concat.m_string = move(t);
	return move(concat);
}

/*
Getter method for m_len
/**/
size_t String::length() const{
	return m_len;
}

/*
Substring method
/**/
String String::substring(size_t start, size_t end) const {
	
	if (end <= start || start >= m_len) {
		return String("");
	}
	else {
		if (end > m_len) {
			end = m_len;
		}
		String s;
		s.m_len = end - start;
		cout << s.m_len << endl;
		unique_ptr <char[]> tmp(new char[s.m_len + 1]);
		for (size_t i = 0; i < s.m_len; ++i){
			tmp[i] = m_string.get()[start + i];
		}
		tmp[s.m_len] = 0x00;
		s.m_string = move(tmp);
		return move(s);
	}
}

/*
toInt method
/**/
int String::toInt() const {

	size_t i = 0;
	int value = 0;
	bool isNeg = false;

	while (i < m_len && !isdigit(m_string.get()[i])) i++;
	if (i > 0) {
		if (m_string.get()[i - 1] == '-') {
			if (i > 1 && m_string.get()[i - 2] != ' ') throw exception("Unsupported character before number");
			else isNeg = true;
		}
		else if (m_string.get()[i - 1] != ' ') throw exception("Unsupported character before number");
	}
	while (i < m_len && isdigit(m_string.get()[i])) {
		value = 10 * value + m_string.get()[i] - '0';
		i++;
	}
	if (isNeg) value *= -1;
	if (i < m_len && m_string.get()[i] != ' ') throw exception("Unsupported character after number");
	return value;
}

/*
toCString method
/**/
unique_ptr<char[]> String::toCString() const{

	unique_ptr<char[]> tmp(new char[m_len + 1]);

	if (m_string == nullptr){
		tmp[0] = 0x00;

		return move(tmp);
	}
	else{
		for (size_t i = 0; i <= m_len; i++){
			tmp[i] = m_string.get()[i];
		}
		return move(tmp);
	}
}

 String String::valueOf(int number){
	 bool vorzeichen = false;

	 if (number < 0) {
		 number *= (-1);
		 vorzeichen = true;
	 }

	String s;
	if (number == 0)
		s.m_len = 1;
	else
		s.m_len = (int)log10((double)number) + 1;
	if (vorzeichen)
		s.m_len++;
	s.m_string = unique_ptr<char[]>(new char[s.m_len + 1]);
	
	for (size_t i = 0; i < s.m_len; i++)
	{
		s.m_string.get()[s.m_len - 1 - i] = '0' + (number % 10);
		number = number / 10;
	}

	s.m_string.get()[s.m_len] = 0x00;

	if (vorzeichen)
		s.m_string.get()[0] = '-';

	return move(s);
}