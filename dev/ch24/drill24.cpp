#include "Matrix.h"
#include "MatrixIO.h"
#include <iostream>
#include <string>
#include <cmath>
#include <complex>
#include <numeric>

using namespace Numeric_lib;
using namespace std;

void numSqrt() {
    int a;
    cout << "Enter a number: ";
    std::cin >> a;
    if (a < 0){
        cout << "No square root" << endl;
    }
    else{
        cout << "Square root: " << std::sqrt(a) << endl;
    }
}

int main(){
    // 1.
    cout << "Size of char:\t"    << sizeof(char)    << endl;
    cout << "Size of short:\t"   << sizeof(short)   << endl;
    cout << "Size of int:\t"     << sizeof(int)     << endl;
    cout << "Size of long:\t"    << sizeof(long)    << endl;
    cout << "Size of float:\t"   << sizeof(float)   << endl;
    cout << "Size of double:\t"  << sizeof(double)  << endl;
    cout << "Size of int*:\t"    << sizeof(int*)    << endl;
    cout << "Size of double*: "  << sizeof(double*) << endl;
    cout << endl;

    // 2.
    Matrix<int> a(10);
    Matrix<int> b(100);
    Matrix<double> c(10);
    Matrix<int, 2> d(10, 10);
    Matrix<int, 3> e(10, 10, 10);

    cout << "Size of a: " << sizeof(a) << endl;
    cout << "Size of b: " << sizeof(b) << endl;
    cout << "Size of c: " << sizeof(c) << endl;
    cout << "Size of d: " << sizeof(d) << endl;
    cout << "Size of e: " << sizeof(e) << endl;
    cout << endl;

    // 3.
    cout << "Number of Elements in a: " << a.size() << endl;
    cout << "Number of Elements in b: " << b.size() << endl;
    cout << "Number of Elements in c: " << c.size() << endl;
    cout << "Number of Elements in d: " << d.size() << endl;
    cout << "Number of Elements in e: " << e.size() << endl;
    cout << endl;

    // 4.
    numSqrt();
    cout << endl;

    // 5.
    cout << "Enter 10 floating point numbers: " << endl;
    Matrix<double> doubles(10);
    for (int i = 0; i < 10; i++) {
        cin >> doubles[i];
    }
    cout << "Matrix: " << doubles << endl;
    cout << endl;

    // 6.
    cout << "Dimensions of multiplication table: " << endl;
    int n;
    int m;
    cin >> n >> m;
    Matrix<int, 2> table(n+1, m+1);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            table[i][j] = i * j;
            cout << table(i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    // 7.
    cout << "Enter 10 Complex numbers: " << endl;
    Matrix<complex<double>> cmatrix(10);
    complex<double> input;
    for (int i = 0; i < 10; i++) {
        cin >> input;
        cmatrix(i) = input;
    }
    auto sum = accumulate(cmatrix.data(), cmatrix.data() + cmatrix.size(), complex<double>{});
    cout << "Sum: " << sum << endl << endl;

    // 8.
    cout << "Enter 6 ints:" << endl;
    Matrix<int, 2> m2(2, 3);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 3; j++){
            cin >> m2[i][j];
        }
    }
    cout << "Matrix: " << m2 << endl;
}