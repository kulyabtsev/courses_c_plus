#include <iostream>

// Fib(0)=0
// Fib(1) = 1
// Fib(N) = Fib(N−1) + Fib(N−2)
template <int N>
struct Fib
{
	static int const
		value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template <>
struct Fib<0>
{
	static int const value = 0;
};

template <>
struct Fib<1>
{
	static int const value = 1;
};


int main()
{
	std::cout << Fib<10>::value;     // 55

	return 0;
}
