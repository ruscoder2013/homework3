#include <string>
#include <type_traits>
#include <iostream>
#include <vector>
#include <list>

void print_ip(int ip) {
	std::cout << "int" << std::endl;
}

void print_ip(std::string str) {
	std::cout << "str" << std::endl;
}

template<typename T>
void print_ip(std::vector<T> v) {
	std::cout << "vector" << std::endl;
}

template<typename T>
void print_ip(std::list<T> l) {
	std::cout << "list" << std::endl;
}

template<typename TT, 
	typename Fake = 
		typename std::enable_if<
			!std::is_same<typename std::remove_reference<TT>::type, 
				SomeStruct>::value, void>::type
>
void print_ip(TT&& value) {
	std::cout << "list" << std::endl;
}

int main() {

	print_ip(char(-1));
	print_ip(short(0));
	print_ip(int(213));
	print_ip(long(8875));
	print_ip(std::string("hello world"));
	std::vector<int> v {1, 2, 3, 4};
	print_ip(v);
	std::list<int> l {1, 2, 3, 4, 5};
	print_ip(l);

	return 0;
}
