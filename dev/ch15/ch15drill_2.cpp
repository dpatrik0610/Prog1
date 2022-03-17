#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct Person {
private:
    string fname;
    string sname;
    int age;

public:
    Person(){};
    Person(string _fname, string _secname, int _age){
        // Checking age
        if(_age < 0 || _age > 150) throw runtime_error("Invalid age.");
        age = _age;
        // Checking name.
        string invalid[] = {";", ":", "\"", "\'", "[", "]", "*", "&", "^", "%", "$", "@", "!"};
        for (int i = 0; i < 13; i++)
        {
            // Search the name to find any invalid string.
            if (_fname.find(invalid[i]) != string::npos || _secname.find(invalid[i]) != string::npos){
                throw runtime_error("Invalid name.");
            }
        }
        fname = _fname;
        sname = _secname;
    };
    string getFirstName() const {return fname;};
    string getSecName() const {return sname;};
    int getAge() const {return age;};
};

ostream &operator<<(ostream &os, const Person &p) {
    return os << p.getFirstName() << " " << p.getSecName() << " " << p.getAge();
}

istream &operator>>(istream &is, Person &p) {
    string fname;
    string sname;
    int age;
    is >> fname >> sname >> age;
    p = Person(fname, sname, age);
    return is;
}

int main() {
    Person goofy("Very", "Goofy", 63);
    cout << goofy.getFirstName() << " " << goofy.getSecName() << " " << goofy.getAge() << endl;
    cout << goofy << endl;

    // Creating a custom person from input.
    Person newPerson;
    cin >> newPerson;
    cout << newPerson << endl;

    //Get multiple persons
    vector<Person> persons;

    for (Person person; cin >> person;) {
        if (person.getFirstName() == "quit") {
            break;
        }
        persons.push_back(person);
    }
    
    // Write vector elements out
    for (auto person : persons) {
        cout << person << endl;
    }
    
    return -1;
}

