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

void printOut(vector<Item>& _vi){
    for (auto& item : _vi)
    {
        cout << item;
    }
    cout << endl;
}

int main(){
try{
    vector<Item> vi;

    // Reading from console / file (with < data.txt)
    for (int i = 0; i < 10; ++i)
    {
        Item _item;
        cin >> _item;
        vi.push_back(_item);
    }

    // File data:
    cout << "File data: " << endl;
    printOut(vi);

    cout << "Sorting.. " << endl;
    sort(vi.begin(), vi.end(), by_name());
    //printOut(vi);
    sort(vi.begin(), vi.end(), by_id());
    //printOut(vi);
    sort(vi.begin(), vi.end(), by_value());
    //printOut(vi);

    return 0;
}catch(exception& e) {
    cout << "Exception: " << e.what() << endl;
}
}
