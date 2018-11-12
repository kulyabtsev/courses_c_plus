// тип IntList уже определён

// определите метафункцию Length для вычисления длины списка
template<typename TL>
struct Length
{
	static int const value = 1 +
		Length<typename TL::Tail>::value;
};

template<>
struct Length<IntList<>>
{
	static int const value = 0;
};
