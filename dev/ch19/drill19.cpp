#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
struct S {
    // Constructor: giving the val's value the input, but if there is no input, it's gonna be 0.
    S (T _input = 0) : val{_input}{}
    T& get();
    const T& get() const;
    void set(T _other){val = _other;};
    void operator=(const T& value);

private:
    // T is a custom data type with any value (val).
    T val;
};

// Reaching the get function of the custom typed struct "S".
template<typename type>
type& S<type>::get(){
    return val;
}

// Making the "=" operator useable for custom typed Struct when giving value for "val".
template<typename type>
void S<type>::operator=(const type& _value){
    val = _value;
}

template<typename type>
type& read_val(type& v){
    std::cin >> v;
    return v;
}

void writeOut(S<int>& mi, S<char>& mc, S<double>& md, S<string>& ms){
    cout << "S<int> : " << mi.get() << endl
        << "S<char> : " << mc.get() << endl
        << "S<double> : " << md.get() << endl
        << "S<string> : " << ms.get() << endl;
}

int main() {
    // 3. Define and initialize struct with int, char, double, string, and a vector<int>
    S<int> myInt {17};
    S<char> myChar {'c'};
    S<double> myDouble {7.49};
    S<string> myString {"Little fox bounces."};
    S<vector<int>> myVec {vector<int> {0, 1, 2, 3, 4, 5}};

    writeOut(myInt, myChar, myDouble, myString); // custom writeout method for future usage.
    cout << "S<vector> : ";
	for (auto& a: myVec.get()){
		cout << a << ' ';
	}
	cout << endl;

    // Giving new values to each variables.
    // Using the "=" custom operator for my variables and the read_val for reading from input field.
    int i = 0;
    cout << "Please give an int: ";
    myInt = (read_val(i)); cout << endl;

    char c = 'e';
    cout << "Please give a char: ";
    myChar = (read_val(c)); cout << endl;

    double d = 0.1;
    cout << "Please give a double: ";
    myDouble = (read_val(d)); cout << endl;

    string s = "Default String.";
    cout << "Please give a string: ";
    myString = (read_val(s)); cout << endl;

    writeOut(myInt, myChar, myDouble, myString);
}