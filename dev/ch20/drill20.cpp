#include <iostream>
#include <list>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename type> 
void print(const type& _type){ 
	// As an input parameter we give a "type(name)" type reference.
	for (auto& i : _type){ // rangefor to the end of _type reference.
    	cout << i << " ";
	};
	cout << endl;
}

template <typename type> 
void increment(type& _type, int val){ 
	// As an input parameter we give a "type(name)" type reference, and an increment value (val).
	for(auto& i : _type){
		i += val;
	};
}

template<typename inType, typename outType> 
outType myCopy(inType _start, inType _end, outType _output){
	for (inType p = _start; p != _end; ++p) { // Increasing the index from the start index.
		// We increase output first (to increase size of the output data type) and then give a value: first, the start's, after the increased one.
		*_output++ = *p;
	}
	return _output;
}

int main()
try {
	const int size = 10;
	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// This copy is a std function.
	// 1. Define an array of 10 ints:
	array<int, size> intArr;
	myCopy(numbers, numbers + size, intArr.begin());

	// 2. Define a vector:
	vector<int> intVec(size);
	myCopy(numbers, numbers + size, intVec.begin());
	// 3. Define a list: 
	list<int> intList(size);
	myCopy(numbers, numbers + size, intList.begin());

	// 4. Define a 2nd of each data type:
	array<int, size> intArrCopy = intArr;
	vector<int> intVecCopy = intVec;
	list<int> intListCopy = intList;

	// Print them with a function to self check:
	cout << "Array, Vector, List: " << endl;
	print(intArrCopy);
	print(intVecCopy);
	print(intListCopy);

	// 5. Increment each element in : array by 2 | vector by 3 | intListst by 5.
	// I use a function for each.
	increment(intArrCopy, 2);
	increment(intVecCopy, 3);
	increment(intListCopy, 5);

	// Self check.
	cout << "Incremented: " << endl;
	print(intArrCopy);
	print(intVecCopy);
	print(intListCopy);

	// 6. Write a copy function.

	// 7. Use copy function to copy: array to vector, list to array.
	copy(intArrCopy.begin(), intArrCopy.end(), intVecCopy.begin());
	copy(intListCopy.begin(), intListCopy.end(), intArrCopy.begin());
	cout << endl;

	// Self check.
	cout << "Copied Array: " << endl;
	print(intArrCopy);
	cout << "Copied Vector: " << endl;
	print(intVecCopy);
	cout << "List: " << endl;
	print(intListCopy);

	// Search for value 3 in the vector with an iterator.
	int searchVal = 3;
	//Iterator which points to an integer contained in a vector. (ch. 20.3 Sequences and iterators.)
	vector<int>::iterator vecIter = find(intVecCopy.begin(), intVecCopy.end(), searchVal);

	if(vecIter != intVecCopy.end()){
		cout << "Value (" << searchVal << ") in vector found at: " << distance(intVecCopy.begin(), vecIter) << endl;
	} else {
		cout << "Not found" << endl;
	};
}
catch(exception& e){
	cerr << "Exception: " << e.what() << '\n';
	return 1;
}
catch(...){
	cerr << "Unknown exception\n";
	return 2;
}