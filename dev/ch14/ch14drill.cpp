#include <iostream>

using namespace std;

class B1 { // (1.1) Define a class B1 with virtual func. vf() and non-virtual f().
public: // (1.2) Also make the functions public.
    virtual void vf() {
        cout << "B1::vf()" << endl;
    }
    void f() {
        cout << "B1::f()" << endl;
    }
    // Pure (raw) virtual function: Every implementation must have this function, but it won't make sense at B1
    // Ex: Every animal should know how to move, but "Animal" class cannot provide this, only derived classes can.
    // We must override this function in the derived class, otherwise the derived class will also become abstract class.
    virtual void pvf() = 0;
};

class D1 : public B1 { // Deriving a D1 class from B1.
public:
    virtual void vf() { 
        // Overriding B1's vf()
        cout << "D1::vf()" << endl;
    }
    void f() {
        cout << "D1::f()" << endl;
    }
    // Still no override of B1's abstract function..
    virtual void pvf() = 0;
};

class D2 : public D1 {
public:
// (6.1) Finally overriding the abstract function.
    void pvf() {
        cout << "Overriding..\tD2::pvf()" << endl;
    }
};

class B2 { // 7.1 Define class B2 with pfv() abs.function
public:
    virtual void pvf() = 0;
};

class D21 : public B2 { // (7.2) Define a D21 class with a STRING data member and a pvf().
public:
    string str;
    // This should override parent B2 and cout the string.
    void pvf() {
        cout << str << endl;
    }
};

class D22 : public B2 { // (7.3) Define a D22 class like D21, but the variable type is an INTEGER now.
public:
    int number;
    void pvf() {
        cout << number << endl;
    }
};

void f(B2& b2ref) { // (7.4) Define a function f that takes a "B2 reference type" as an argument and calls pvf().
    b2ref.pvf();
}

int main() {
    /*
    // 1. Creating B1 type object and calling their functions.
        B1 b1;
        b1.vf(); // Output: B1::vf()
        b1.f(); // Output: B1::f()
        cout << endl;

    // 2. Making a D1 function.
        D1 d1;
        d1.vf(); // Output: D1::vf()
        d1.f(); // Output: D1::f()
        cout << endl; 
    // 3. We are creating a reference to the B1 class and inicializing it to d1 object.
        B1& b_reference = d1; 
    // Since it doesn't have it's own functions, it will use B1's.

    // 4. After adding D1 it's own functions: 
    b_reference.vf(); // Output: D1::vf() // Because we overrided with an own function.
    b_reference.f(); // Output: B1::f() // we don't override this function, so reference will use it's own B1 function.

    //     -----> After step 5: Since we made B1 an abstract class and D1 is a B1, we cannot Define b1 or d1 anymore, or making reference of them. <-----
    */
   cout << "Creating D2" << endl;
    D2 d2; // 6. Making an object of d2, which now has a pvf function override, BUT NO override of vf() and f()
    //           D2(override) -> D1(no override) -> B1(abst)
    d2.vf(); // Output: D1::vf()        (No override.)
    d2.f(); // Output: D1::f()          (No override.)
    d2.pvf(); // Output: Overriding..     D2::pvf()
    cout << "------------------------------" << endl; 

   cout << "Giving d21 a string..." << endl;
    D21 d21str;
    d21str.str = "I'm a string!";
    //d21str.pvf();   Testing...

    cout << "Giving d22 a number." << endl;
    D22 d22num;
    d22num.number = 777;
    //d22num.pvf();    Testing...
    cout << endl;

    // 7.5 Call f() with d21 and d22
    f(d21str); // If reference is d21, Output: Overriding B2... \tD21::B2       (String).
    f(d22num);// If reference is d22, Output: 777                               (Integer).
    // Since f requires a B2 type reference:
    // This function's output depends on what reference we give to them. They contain different data members.
}