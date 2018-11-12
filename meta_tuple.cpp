#include <tuple>
template <typename Func, typename T, int... Indices >
auto apply_internal(Func f, T &t, IntList<Indices...> I) -> decltype(f(std::get<Indices>(t)...)) 
{
	return f(std::get<Indices>(t)...);
}

template <typename Func, typename T, typename Indices = typename Generate<std::tuple_size<T>::value>::type>
auto apply(Func f, T t) -> decltype( apply_internal(f, t, Indices()))
{
	auto res = apply_internal(f, t, Indices());
	return res;
}
