//#include <vector>
//#include <memory>
//#include <tuple>
//#include <utility>
//#include <iostream>
//
//
//struct Node {
//	std::string key;
//	std::vector<int> value;
//	float f;
//};
//
//#define STRINGIZE_2(A) #A
//
//#define STRINGIZE(A) STRINGIZE_2(A)
//
//#define REFLECT_MEMBER(OBJ, MEM) std::make_pair(STRINGIZE(MEM), std::ref(OBJ . MEM))
//
//auto reflect_tuple(Node& n) {
//	return make_tuple(REFLECT_MEMBER(n, key), REFLECT_MEMBER(n, value), REFLECT_MEMBER(n, f));
//}
//
//template <class F, class T, std::size_t ... Is>
//void reflect_impl(T& t, F f, std::index_sequence<Is...>) {
//	int x[] = { (f(std::get<Is>(t).first, std::get<Is>(t).second), 0)... };
//}
//
//template <class F, class T>
//void reflect(T& t, F f) {
//	auto tup = reflect_tuple(t);
//	reflect_impl(tup, f, std::make_index_sequence<std::tuple_size<decltype(tup)>::value>{});
//}
//
//
//int main()
//{
//	Node n{};
//	n.key = "hello";
//	n.value = { 5 };
//	n.f = 67.54f;
//	reflect(n, [](const char* name, auto& property) {
//		std::cerr << name << " : " << property << "\n";
//		});
//	return 0;
//}