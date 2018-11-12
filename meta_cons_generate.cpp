template<int H, typename IL>
struct IntCons;

template<int H, int... Types>
struct IntCons<H, IntList<Types...>>
{
	using type = IntList<H, Types...>;
};

template<int N, int E=N>
struct Generate
{
	using type = typename IntCons<N - E, typename Generate<N, E-1>::type>::type;
};

template<int N>
struct Generate<N, 0>
{
	using type = IntList<>;
};
