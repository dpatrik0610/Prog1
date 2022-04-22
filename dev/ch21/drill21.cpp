#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int iid;
    double value;
    Item(): name("undefined"), iid(-1), value(0){}
    Item(string _name, int _id, double _val): name(_name), iid(_id), value(_val){}
};

ostream& operator<<(ostream& os, Item& item){
    return os << "{" << item.name << ", " << item.iid << ", " << item.value << "}" << endl;
}

istream& operator>>(istream& is, Item& item){
    string input;
    is >> item.name >> item.iid >> item.value;
    return is;
}

int main(){
try{
    vector<Item> vi;

    for (int i = 0; i < 10; ++i)
    {
        Item _item;
        cin >> _item;
        vi.push_back(_item);
    }
    // File data:
    cout << "File data: " << endl;
    for (auto& item : vi)
    {
        cout << item;
    }
    cout << endl;
    return 0;
    cout << "Sorted by name: " << endl;
    // to be continued.
    
}catch(exception& e) {
    cout << "Exception: " << e.what() << endl;
}
}
