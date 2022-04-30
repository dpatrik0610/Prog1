#include <stdio.h>
//gcc drill27.c -o ../../builds/drill27

void func(const char* p, const int x) {
    printf("p is \"%s\" and x is %i\n", p, x);
}

int main(){


	// 1. Write a "Hello World!"
	printf("Hello World \n");

	// 2. Define 2 var, concat. them.
	char* first = "Hello";
	char* last = "World";

	// %s is a string of characters.
	printf("%s %s\n",first,last);
	
	// 3. Define a function. 
	func("foo", 7);
	func("bar", 1);
}