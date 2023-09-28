#include "test_eq.h"

size_t id = 0;

template<class T>
void test(const T& x, const T& y, bool t = true){
	string idname = "test" + to_string(id);
	if(test_eq(x, y) == t){
		cout << idname << "\t" << "OK" << endl;
	}else{
		cout << idname << "\t" << "NG" << endl;
	}

	id++;
	return;
}

template<class T>
void test_arr(const vector<T>& x){
	size_t s = x.size();
	bool okflg = true;

	cout << "test_arr" + to_string(id) + " : ";
	for(size_t i1=0; i1<s; i1++){
		for(size_t i2=i1; i2<s;i2++){
			if(test_eq(x[i1], x[i2]) != (i1 == i2)){
				cout << "\nNG " << i1 << ", " << i2;
				okflg = false;
			}
		}
	}

	if(okflg){
		cout << "OK";
	}

	cout << "\n" << endl;

	id++;
	return;
}

int main(){
	// BASIC
	vector<int> intv = {0, -1, 6, 45, 7};
	test_arr(intv);
	vector<unsigned long long> ULLv ={0ULL, 384953495ULL, 84759876ULL, 0xffffffffULL, 38458765480ULL};
	test_arr(ULLv);

	vector<float> floatv = {0.0f, -1.4356f, 546545.85674f, -56465.544f, -1111.4f};
	test_arr(floatv);
	vector<double> dblv = {0.0, 453974.7856745, 25345.48573, -2376492.2};
	test_arr(dblv);

	vector<vector<int>> VIv = {
		{},
		{0, 2, 5, 6, 7},
	 	{0, 2, 6, 5, 7},
		{85739845, 63458374, 238479, 475, 22, -1746},
		{4578374, 487537, -237469, -548768324}
	};

	test_arr(VIv);

	vector<string> strv = {"", "hogehoge", "fuga", "ehrjtg4u039wrf", "38iusodgth8w^\\gg", "esjrfhr"};
	test_arr(strv);

	vector<list<float>> FLv ={
		{},
		{0.0f, -2385.623746f, 8785.123f, -3476.555f},
		{745.333f, -1857.444f, 5765.2222f, 0.0f},
		{-2385.623746f, 0.0f, 8785.123f, -3476.555f},
	};
	test_arr(FLv);

	vector<map<char, int>> cimv = {
		{},
		{{'x', 45}, {'g', 2435}, {')', 7774}, {'O', -2678}},
		{{'x', 45}, {'g', 2435}, {'O', -2678}, {')', 7774}},
		{{'a', 70}, {'b', 884}, {'c', 72191}, {'d', 7773}},
	};
	test_arr(cimv);

	vector<unordered_map<double, string>> dsuv = {
		{},
		{{4.3, "hoge"}, {4.44444, "fuga"}, {284.222, "piyo"}, {-4555.44, "foo"}},
		{{4.44444, "fuga"}, {284.222, "piyo"}, {-4555.44, "foo"}, {4.3, "hoge"}},
		{{-12.333, "hsdgs"}, {4.44444, "hhh"}, {284.222, "piyo"}},
	};
	test_arr(dsuv);

	return 0;
}