//g++ vector_006.cpp -o vector_006 -Wall -fno-elide-constructors

#include "../../std_lib_facilities.h"

class My_out_of_range{};

struct No_default {
	No_default(int k) { a = k; }
	int a = 0;
	int b = 0;
};

template<typename T, typename A = allocator<T>>  // az A egy T tipusu elemeknek segít memóriát foglalni
class My_vector {
	A alloc;
	long unsigned int sz;		//mennyi elem van most a lefoglalt max helybe pl 20 elemnek foglaltunk helyet de csak 10 elemmünk vna ezt adja vissza
	T* elem;
	int space;		//mennyi elemnek foglaltunk helyet
	//unsigned long space;

	void debug(const string& str)
	{
		cerr << this << "->" << str << " elem ptr: "  // this-> kiírjuk az objektum címét , str-> üzenetet , elem ptr címét.
			<< elem << endl;
	}

public:

	using size_type = unsigned long;
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;

	iterator begin() { return elem; }
	const_iterator begin() const { return elem; }
	iterator end() { return elem+sz; }
	const_iterator end() const { return elem+sz; }
	iterator back() { return elem+sz-1; }

	My_vector(): sz{0}, elem{nullptr}, space{0} {}

	explicit My_vector(int s): sz(s), elem{alloc.allocate(s)}, space(s) // elem alloc.allocate(s) -> ez itt az adott típusu (T) elemünknek foglal memóriát
	{
		for (int i = 0; i < s; ++i) alloc.construct(&elem[i], T());  // a construc segítségével letrehozzuk az objektumokat az adott memória területre construct-nak megadjuk az elem címét (&elem[i]) ahova létreakarjuk hozni az "objektumot"
										// illetve meg kell hívni az alapértelmezett típus konstruktorát (T())
		//debug("int constructor");
	}

	My_vector(initializer_list<T> lst): 
		sz(lst.size()), elem{alloc.allocate(sz)}, space(lst.size()) //sz-darab helyet foglalunk
	{
		//copy(lst.begin(), lst.end(), elem);
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], *(lst.begin()+i)); // itt azért nem T() mert másolunk a lista iterátorát adjuk meg (.begin)
		//debug("lst constructor");
	}

	My_vector(const My_vector& arg): 
		sz{arg.sz}, elem{alloc.allocate(sz)}, space{arg.sz}
	{
		//copy(arg.elem, arg.elem+arg.sz, elem);
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], arg[i]); // const referenciát használunk arg-tol
		//debug("copy constructor");
	}

	My_vector& operator=(const My_vector& arg)   //másolás függvény
	{
		if (this == &arg) return *this;		//ha self assigment-et akarunk akkor csak szimplán vissza adjuk az alap értékeket
		// v=v;

		if (arg.sz <= space)  //ha az elemein számára elengendő hely van lefoglava csak simán átmásoljuk
		{
			for (int i = 0; i < arg.sz; ++i)     //itt kevesebb elemunk van mint tárhely amit foglalunk
				alloc.construct(&elem[i], arg[i]);
			for (int i = arg.sz; i < sz; ++i)	//kitöröljük a felselgese alap érétkkel rendelkező elemeket de a memória terület lefoglalva marad az nem változik
				alloc.destroy(&elem[i]);
			sz = arg.sz;	//elemek számát egyenlővé tesszük
			return *this;
		}

		T* p = alloc.allocate(arg.sz); //memóriát foglalunk arg.sz elemnek átmenetileg
		//copy(arg.elem, arg.elem+arg.sz, p);
		for(int i = 0; i < arg.sz; ++i) alloc.construct(&p[i], arg[i]); // felmásoljuk az átmeneti memóriára az elmeinket
		alloc.deallocate(elem, space);	//felszabadítunk
		//delete[] elem;
		elem = p; //swappelünk
		sz = arg.sz;
		space = arg.space;
		//debug("copy assignment");
		return *this;
	}

	My_vector(My_vector&& arg):
		sz{arg.sz}, elem{arg.elem}, space{arg.space}
	{
		arg.sz = 0;
		arg.space = 0;
		arg.elem = nullptr;
		//debug("move constructor");
	}

	My_vector& operator=(My_vector&& arg)  //mozgató értékadás
	{
		//delete[] elem;
		for(int i = 0; i < sz; ++i) alloc.destroy(&elem[i]); 
		alloc.deallocate(elem, space);  //memória felszabadítás
		space = arg.space;
		sz = arg.sz;
		elem = arg.elem;
		arg.sz = 0;
		arg.space = 0;
		arg.elem = nullptr;
		//debug("move assignment");
		return *this;
	}

	~My_vector() 
	{ 
		//debug("destructor");
		//delete[] elem; 
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]); //felszabadítjuk a nem használt/nem szükséges foglalt memóriát
		alloc.deallocate(elem, space);
	}
	
	long unsigned int size() const { return sz; }	//vissza adja a vektorunk méretét
	int capacity() const { return space; }  //vissza adja a lefoglat helyünket(ez az a hely amit megtölthetünk az adott elemeinkel.)

	T& operator[](int n){ return elem[n]; }               //access operatorok , ennek segitségével tudunk vektorunk i-edik elemére hivatkozni
	const T& operator[](int n) const { return elem[n]; }	// tomb[i] 

	T& at(int n)
	{
		if (n < 0 || n >= sz) throw My_out_of_range();     //túlcsordulás ha tömb méretnén kívülre akarunk hivatkozni ezt így letudjuk kezelni
		return elem[n];
	}

	const T& at(int n) const
	{
		if (n < 0 || n >= sz) throw My_out_of_range();
		return elem[n];
	}

	void reserve(int newalloc)			//ennek a függvénynek a segítségével foglalunk memóriát
	{
		if (newalloc <= space) return;	//hibakezelés ha kevesebb helyünk lenne mint amennyi kell.
		//T* p = new T[newalloc];	//memória foglalás
		//T* p = alloc.allocate(newalloc);
		unique_ptr<T[]> p { alloc.allocate(newalloc) };
		//for (int i = 0; i < sz; ++i) p[i] = elem[i]; //elemek átmásolása
		for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);	//lemásoljuk/lefoglaljuk a memóriát régi memória területről az újra
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]); //destroy felszabadítjuk a memóriát. csak az adott elem által foglalt memóriát
		alloc.deallocate(elem, space);	//itt szabadítjuk fel igazán a deallocate-vel a memóriát
		//delete[] elem;	//memória felszabadítása
		elem = p.release();
		space = newalloc;	
	}

	void resize(int newsize, T val = T())	//újraméretezzük a konténerünket és az új értékeknek alapértelmezett értékeket tudunk megadni pl valami.resize(5,0) 5 elemre növeljük és az új értékek 0-k lesznek
	{
		reserve(newsize); //memória lefoglalása
		for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val); // ha növeljük akkor azt a pár elemnek lefogllajuk a helyet
		for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]); // ha csökkentjük a méretet akkor a kimaradó értékeket felszabadítjuk

		sz = newsize;	// az elem számot átálítjuk az új elemszámra
	}

	void push_back(const T& d)	
	{
		if(space==0)  //vizsgáljuk hogy van e még hely a lefoglat helyből
			reserve(8);	//ha nincs akkor 8 helyet foglalunk
		else if (sz==space)	// ha nincs több hely
			reserve(2*space);	// akkor megduplázzuk a tárhelyünket
		//elem[sz] = d;			//egyébként az utolsó elemnek átadjuk az adott értéket
		alloc.construct(&elem[sz], d); //megadjuk az értékeket az adott területre
		++sz;				//végül növeljük a helyet
	}

	iterator erase(iterator p) //ahova az iterator mutat azt az elemet töröljük
	{
		if(p==end()) return p;	//hiba kezelés ha nincs benne a lsitába amit ekresünk
		for (auto pos = p+1; pos != end(); ++pos)//végigmegyünk a lsitán és előrehozzuk a törölt elem hejétöl keződően az elemeket
			*(pos-1) = *pos;
		alloc.destroy(&*(end()-1));	// az utoljára előreébbhozott elem helyét felszabadítjuk
		--sz;				//csökkentjük a méretet
		return p;
	}

	iterator insert(iterator p, const T& val) //megadjuk hova akarjuk beilleszteni és mit
	{
		int index = p-begin(); //pböl kivonjuk az első helsyet megkpajuk hova akrjuk beilleszteni
		if(size()==capacity()) //ha nincs több hely akkor növeljük a területünket
			reserve(size()==0?8:2*capacity());		// ha 0 azaz az első elemünk akkor 8ra növeljük egyébként duplázzuk a területünket
		alloc.construct(elem+sz, *back());
		++sz;					//növeljük a szizeot
		iterator pp = begin()+index;	//ahova beszeretnénk szúrni az elemet
		for (auto pos = end()-1; pos != pp; --pos)  //innentöl ekzdve minden elemet 1-el hátra tolunk
			*pos = *(pos-1);
		*(begin()+index) = val;  //beszurjuk az elemet amit beakarunk
		return pp;		//vissza adjuk az iterátorunkat
	}
};


My_vector<double> fill() 
//For testing move semantics use command line option -fno-elide-constructors
{
	My_vector<double> t{10.2, 14.6, 20.1};

	return t;
}

void test_constructors()
{
	// Test 1:
	My_vector<double> mv;
	cout << "Mv.capacity: " << mv.capacity() << endl;

	for (int i = 0; i < 18; ++i)
	{
		mv.push_back(8.5);
		cout << mv.capacity() << endl;
	}
	// Test 2:
	My_vector<double> mv2 (mv);
	
	for(int i = 0; i < mv2.size(); ++i)
		cout << mv2.at(i) << ' ';
	cout << endl;
	// Test 3:
	My_vector<double> mv3 {15.2, 18.6, 120.1};

	mv3 = mv;

	for(int i = 0; i < mv3.size(); ++i)
		cout << mv3.at(i) << ' ';
	cout << endl;

	// Test 4:
	My_vector<double> mv4 = fill();

	for(int i = 0; i < mv4.size(); ++i)
		cout << mv4.at(i) << ' ';
	cout << endl;

	// Test 5:
	My_vector<double> mv5 {15.2, 18.6, 120.1};

	mv5 = fill();

	for(int i = 0; i < mv5.size(); ++i)
		cout << mv5.at(i) << ' ';
	cout << endl;

	// Test 6:
	My_vector<double> mv6 (10);
}

My_vector<double> glob(10);

int main()
try {

	My_vector<string> smv {"Jack", "Jill", "Béla", "John", "Jenny"};

	for(int i = 0; i < smv.size(); ++i)
		cout << smv.at(i) << endl;
	cout << endl;
	auto p = find(smv.begin(), smv.end(), "Béla");

	smv.erase(p);

	smv.insert(p, "Joseph");

	for(const auto& element : smv)
		cout << element << endl;
	
	test_constructors();
	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}