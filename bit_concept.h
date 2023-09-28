#include <iostream>
#include <utility>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <map>

namespace bitRW {
	using namespace std;

	template <class T>
	concept BASIC = is_integral_v<T> || is_floating_point_v<T>;

	// pair #############################################################
	template <class>
	struct is_p : bool_constant<false> {};

	template<class T1, class T2>
	struct is_p <pair<T1, T2>> : bool_constant<true> {};

	template <class T>
	inline constexpr bool is_p_v = is_p<T>::value;

	template<class T>
	concept Pair = is_p_v<T>;

	// vector, string ###################################################
	// template<class>
	// struct is_vs_c : bool_constant<false>{};

	// template<class T, class Allocator>
	// struct is_vs_c <vector<T, Allocator>> : bool_constant<true> {};
	// template <class T, class traits, class Allocator>
	// struct is_vs_c<basic_string<T, traits, Allocator>> : bool_constant<true> {};

	// template <class T>
	// inline constexpr bool is_vs_c_v = is_vs_c<T>::value;

	// template <class T>
	// concept VS_c = is_vs_c_v<T>;

	// vector, string, list #############################################
	template <class>
	struct is_seq_container : bool_constant<false> {};

	template <class T, class Allocator>
	struct is_seq_container<vector<T, Allocator>> : bool_constant<true> {};
	template <class T, class Allocator>
	struct is_seq_container<list<T, Allocator>> : bool_constant<true> {};
	template <class T, class traits, class Allocator>
	struct is_seq_container<basic_string<T, traits, Allocator>> : bool_constant<true> {};

	template <class T>
	inline constexpr bool is_seq_container_v = is_seq_container<T>::value;

	template <class T>
	concept S_Container = is_seq_container_v<T>;
	// ##################################################################

	// std::array #######################################################
	template <class>
	struct is_farr : bool_constant<false> {};
	template <class T, size_t s>
	struct is_farr<array<T, s>> : bool_constant<true> {};

	template <class T>
	inline constexpr bool is_farr_v = is_farr<T>::value;
	// ##################################################################

	// map / unordered_map / multimap / unordered_multimap ##############
	template <class>
	struct is_dictionary : bool_constant<false> {};

	//map
	template <class Key, class T, class Compare, class Allocator>
	struct is_dictionary<map<Key, T, Compare, Allocator>> : bool_constant<true> {};
	//unordered_map
	template <class Key, class T, class Hash, class Pred, class Allocator>
	struct is_dictionary<unordered_map<Key, T, Hash, Pred, Allocator>> : bool_constant<true> {};
	//multimap
	// template <class Key, class T, class Compare, class Allocator>
	// struct is_dictionary<multimap<Key, T, Compare, Allocator>> : bool_constant<true> {};
	//unordered_multimap
	// template <class Key, class T, class Hash, class Pred, class Allocator>
	// struct is_dictionary<unordered_multimap<Key, T, Hash, Pred, Allocator>> : bool_constant<true> {};

	template <class T>
	inline constexpr bool is_dictionary_v = is_dictionary<T>::value;

	template <class T>
	concept Dictionary = is_dictionary_v<T>;
	// ##################################################################


	// S_Container + Dictionary #########################################
	template <class T>
	concept Container = is_seq_container_v<T> || is_dictionary_v<T>;
	// ##################################################################
}

template <bitRW::S_Container T>
void scf(T x) {
	std::cout << "S_container\n";
}

template <bitRW::Dictionary T>
void df(T x) {
	std::cout << "Dictionary\n";
}