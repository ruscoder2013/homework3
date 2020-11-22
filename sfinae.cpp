#include <string>
#include <type_traits>
#include <iostream>
#include <vector>
#include <list>

namespace is_stl_container_impl{
  template <typename T>       struct is_stl_container:std::false_type{};
  template <typename... Args> struct is_stl_container<std::vector            <Args...>>:std::true_type{};
  template <typename... Args> struct is_stl_container<std::list              <Args...>>:std::true_type{};
}

//type trait to utilize the implementation type traits as well as decay the type
template <typename T> struct is_stl_container {
  static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
};

template<typename T, 
		typename Fake = 
			typename std::enable_if<!is_stl_container<T>::value, void>::type
	>
void print_ip(T&& container) {
	std::cout << "container" << std::endl;
}


template<typename T, 
		typename Fake = 
			typename std::enable_if<!std::is_integral<T>::value, void>::type
	>
void print_ip(T&& ip) {
	std::cout << +ip << std::endl;
}

// template <typename T>
// struct is_string
//     : public mpl::or_< // is "or_" included in the C++11 library?
//         std::is_same<       char *, typename std::decay< T >::type >,
//         std::is_same< const char *, typename std::decay< T >::type >
//      > {};


void print_ip(std::string str) {
	std::cout << "str" << std::endl;
}


// template<typename T>
// void print_ip(std::vector<T> v) {
// 	std::cout << "vector" << std::endl;
// }

// template<typename T>
// void print_ip(std::list<T> l) {
// 	std::cout << "list" << std::endl;
// }



int main() {

	// std::cout << "hw" << std::endl;
	// SomeStruct first("Hello, World!");
	// SomeStruct second = first;

	char c = -1;
	print_ip(c);
	short s = 0;
	print_ip(s);
	int i = 2130706433;
	print_ip(i);
	long long l = 8875824491850138409;
	print_ip(l);
	print_ip(std::string("hello world"));
	std::vector<int> v {1, 2, 3, 4};
	print_ip(v);
	std::list<int> l2 {1, 2, 3, 4, 5};
	print_ip(l2);

	std::cout << char(-1) << std::endl;

	return 0;
}
