#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <typename T>
struct S {
	S (T vv = 0) : val{vv}{}
	T& get();
	void set (T new_t) {val = new_t;}
	void operator=(const T& s);
	const T& get() const;

private:
	T val;
};

template<typename T>
T& S<T>::get(){
	return val;
}

template<typename T>
const T& S<T>::get() const{
	return val;
}

template<typename T>
void S<T>::operator=(const T& s){
	val = s;
}

template<typename T>
void read_val(T& v){
	cin >> v;
}

template<typename T>
std::ostream& operator<< (ostream& os, vector<T> &v){
	os << "{ ";
	for (int i = 0; i < v.size(); ++i)
	{
		os << v[i] << (i < v.size()-1 ? ", ": " ");
	}
	os << "}\n";
	return os;
}

template<typename T>
std::istream& operator>> (istream& is, vector<T> &v){
	char ch = 0;
	is >> ch;
	if ( ch != '{'){
		is.unget();
		return is;
	}
	for (T val; is >> val;) {
		v.push_back(val);
		is >> ch;
		if (ch != ',') break;
	}

	return is;
}

int main(){

	S<int> s;
	S<int> si {37};
	S<char> sc {'c'};
	S<double> sd {3.2};
	S<std::string> ss {"Hello"};
	S<std::vector<int>> svi {std::vector<int>{1, 1, 2, 3, 5, 8}};

	cout << "S<int> : " << s.get() << endl
		 << "S<int> : " << si.get() << endl
		 << "S<char> : " << sc.get() << endl
		 << "S<double> : " << sd.get() << endl
		 << "S<string> : " << ss.get() << endl;
		 //<< "S<vector> : " << svi.val << endl;

	cout << "S<vector> : ";
	for (auto& a: svi.get()){
		cout << a << ' ';
	}
	cout << endl;

	sc.set('s');
	cout << "S<char> : " << sc.get() << endl;

	sd = 42.1;
	cout << "S<double> : " << sd.get() << endl;

	int ii;
	read_val(ii);
	S<int> si2 {ii};

	double dd;
	read_val(dd);
	S<double> sd2 {dd};

	string ss2;
	read_val(ss2);
	S<string> str {ss2};

	cout << "S<int> : " << si2.get() << endl;
	cout << "S<double> : " << sd2.get() << endl;
	cout << "S<string> : " << str.get() << endl;

	cout << "S<vector<int>> : (format: {val, val, val})";
	vector <int> vi2;
	read_val(vi2);
	//S<vector<int>> svi2 {v}
};
