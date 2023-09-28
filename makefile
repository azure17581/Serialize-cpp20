build:
	g++ main.cpp -std=c++2a
	./a.out

test:
	g++ test.cpp -o test.out -std=c++2a
	./test.out

test_eq:
	g++ test_eq.cpp -o test_eq.out -std=c++2a
	./test_eq.out

gtest:
	g++ -std=c++2a gtest.cpp -o gtest -L/usr/local/lib -lgtest -lgtest_main
	./gtest