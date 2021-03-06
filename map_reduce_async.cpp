
#include <iostream>
#include <list>
#include <vector>
#include <future>

// заголовок <future> уже подключён.
// заново подключать не нужно

// реализация функции mapreduce
template<typename It, typename func1, typename func2>
auto map_reduce(It p, It q, func1 f1, func2 f2, size_t threads)->decltype(f1(*p))
{
	using r_type = decltype(f1(*p));
	r_type res = {};

	size_t dist = std::distance(p, q);

	int delta = dist / threads;
	int rem = dist % threads;

	std::vector<std::future<r_type>> v;

	for (size_t i = 0; i != threads; ++i)
	{
		It end = std::next(p, delta);

		if (i == threads - 1)
			end = std::next(end, rem);

		 v.emplace_back(std::async(std::launch::async, [](It b, It e, func1 ff1, func2 ff2) {
			r_type res = ff1(*b);
			while (++b != e)
				res = ff2(res, ff1(*b));
			return res;
		}, p, end, f1, f2));

		p = std::next(p, delta);
	}

	for (int i = 0;i!=v.size();++i)
	{
		res = f2(res, v[i].get());
	}

	return res;
}

int main()
{
	std::list<int> l = { 1,2,3,4,5,6,7,8,9,10 };//55 45
	// параллельное суммирование в 3 потока
	auto sum = map_reduce(l.begin(), l.end(),
		[](int i) {return i; },
		std::plus<int>(), 3);

		std::cout << sum << std::endl;

	// проверка наличия чётных чисел в четыре потока
	auto has_even = map_reduce(l.begin(), l.end(),// true
		[](int i) {return i % 2 == 0; },
		std::logical_or<bool>(), 4);

	std::cout << has_even << std::endl;

	return 0;
}
