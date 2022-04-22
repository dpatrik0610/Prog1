#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

//g++ ./dev/ch21/drill21.cpp -o ./builds/ch21
//./builds/ch21 < ./dev/ch21/data.txt

using namespace std;

struct Item {
    string name;
    int iid;
    double value;
    Item(): name("undefined"), iid(-1), value(0){}
    Item(string _name, int _id, double _val): name(_name), iid(_id), value(_val){}
};

// Output stream for readibility. Output: {Apple, 0, 130}

ostream& operator<<(ostream& os, Item& item){
    return os << "{" << item.name << ", " << item.iid << ", " << item.value << "}" << endl;
}

// Input stream to get items from console. Input: Apple 0 130
istream& operator>>(istream& is, Item& item){
    string input;
    is >> item.name >> item.iid >> item.value;
    return is;
}

// Policies: 
struct by_name {
    bool operator()(const Item& _item1, const Item& _item2) const{
        return _item1.name < _item2.name;
    }
};

struct by_id {
    bool operator()(const Item& _item1, const Item& _item2) const {
        return _item1.iid < _item2.iid;
    }
};

struct by_value {
    bool operator()(const Item& _item1, const Item& _item2) const {
        return _item1.value > _item2.value;
    }
};

template <typename T>
void printOut(T& data){
    for (auto& item : data)
    {
        cout << item;
    }
    cout << endl;
}

int main(){
try{
    // 1. Make vector<Item> vi
    vector<Item> vi;

    // Reading from console / file (with < data.txt)
    for (int i = 0; i < 10; ++i)
    {
        Item _item;
        cin >> _item;
        vi.push_back(_item);
    }

    // File data:
    cout << "Vector data: " << endl;
    printOut(vi);

    //cout << "Sorting.. " << endl;

    // 2, 3, 4. Sorting.
    // About sorting: sort() uses < as the sorting criterion, but we can also supply our own criteria.
    // I'm going to make that criteria with structures. Book: 21.8, Sorting and searching.
    sort(vi.begin(), vi.end(), by_name());
    //printOut(vi);
    sort(vi.begin(), vi.end(), by_id());
    //printOut(vi);
    sort(vi.begin(), vi.end(), by_value());
    //printOut(vi);

    // 5. Insert item ("horse shoe", 99, 12.34) & ("Canon S400", 9988, 499.95)
    vi.push_back(Item{"horse shoe", 99, 12.34});
    vi.push_back(Item{"Canon S400", 9988, 499.95});
    //printOut(vi);

    // 6. Remove 2 items identified by name from vi.

    // .erase() removes ITEM(S) IN A RANGE OF ITERATORS. (Need an iterator)
    // remove_if() removes the entries from vector and will point at the first occurance of the predicate.
    vi.erase( 
        remove_if( // The beginning of the iterator = First occurance of predicate.
            vi.begin(), // From the start
            vi.end(), // To the end + 1
            [](const Item& item) {return item.name == "horse shoe" || item.name == "Pineapple";}), // Lambda to make an item named "customname".
        vi.end() // End of the iterator (and the vector.)
    );
    //printOut(vi);

    // 7. Remove two items identified by iid from vi.
    vi.erase( 
        remove_if( // The beginning of the iterator = First occurance of predicate.
            vi.begin(), // From the start
            vi.end(), // To the end + 1
            [](const Item& item) {return item.iid == 9988 || item.iid == 7;}), // Lambda to make an item iid as 9988 and 7 (Canon.. and Papaya)
        vi.end() // End of the iterator (and the vector.)
    );
    cout << "Reduced Data:" << endl;
    printOut(vi);

    // Repeat with list:
    list<Item> li;
    for (auto& item : vi){
        li.push_back(item);
    }
    cout << "List Data:" << endl;
    printOut(li);

    li.sort([](const Item& a, const Item& b) { return a.name < b.name; });
    li.sort([](const Item& a, const Item& b) { return a.iid < b.iid; });
    li.sort([](const Item& a, const Item& b) { return a.value > b.value; });

    li.push_back(Item{"horse shoe", 99, 12.34});
    li.push_back(Item{"Canon S400", 9988, 499.95});

    li.erase(
        remove_if(
            li.begin(),
            li.end(),
            [](const Item& item) { return item.name == "Apple" || item.name == "Orange"; }),
        li.end()
    );

    li.erase(
        remove_if(
            li.begin(),
            li.end(),
            [](const Item& item) { return item.iid == 8 || item.iid == 9; }),
        li.end()
    );

}catch(exception& e) {
    cout << "Exception: " << e.what() << endl;
}
}
