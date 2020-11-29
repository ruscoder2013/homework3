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

/*!
Метафункция определяющая, является ли тип T, контейнером типа list или vector
\param[in] T - тип
*/
template <typename T> struct is_stl_container {
  static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
};

template<class...> struct disjunction : std::false_type { };
template<class B1> struct disjunction<B1> : B1 { };
template<class B1, class... Bn>
struct disjunction<B1, Bn...> 
    : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>>  { };

/*!
Метафункция определяющая, является ли тип T строкой
\param[in] T - тип
*/
template<typename T>
struct is_string
        : public disjunction<
                std::is_same<char *, typename std::decay<T>::type>,
                std::is_same<const char *, typename std::decay<T>::type>,
                std::is_same<std::string, typename std::decay<T>::type>
        > {
};

/*!
Шаблон функции, печатающий ip адрес
*/
template<typename T,
         typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
void print_ip(T number)
{
	std::cout << ((number>>(8*(sizeof(T)-1))) & 0xff);
	for(int i = (sizeof(T) - 1); i >= 0; i--)
    	std::cout << "." << ((number>>(8*i)) & 0xff) ;
	std::cout << std::endl;
}

template<typename T, typename std::enable_if<is_string<T>::value, int>::type = 0>
void print_ip(T str) {
	std::cout << str << std::endl;
}

template<typename T, typename std::enable_if<is_stl_container<T>::value, int>::type = 0>
void print_ip(T container) {
	for(const auto& element: container)
		std::cout << element << ".";
	std::cout << std::endl;
}

int main() {
	char c = -1;
	print_ip(c);
	short s = 0;
	print_ip(s);
	int i = 2130706433;
	print_ip(i);
	long long l = 8875824491850138409;
	print_ip(l);
	print_ip(std::string("1.1.1.1"));
	std::vector<int> v {1, 2, 3, 4};
	print_ip(v);
	std::list<int> l2 {1, 2, 3, 4, 5};
	print_ip(l2);
	return 0;
}
