#include "Mystring.h"
#include <string>

int main(){

	String greetme("Hello");
	String world(" world");

	// Print a standard String
	cout << "Standard String" << endl;
	cout << "***************" << endl;
	cout << greetme << endl;
	cout << endl;

	// Print a concatenated String
	cout << "Concatenated String" << endl;
	cout << "*******************" << endl;
	String concat = greetme.concat(world);
	cout << concat << endl;

}