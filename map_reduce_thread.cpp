#include <vector>
// заголовок <thread> уже подключён.
// заново подключать не нужно

// реализация функции mapreduce
template<typename It, typename func1, typename func2>
auto map_reduce(It p, It q, func1 f1, func2 f2, size_t threads)->decltype(f1(*p))
{
	using r_type = decltype(f1(*p));
	r_type res = {};

	size_t dist = std::distance(p, q);

	int delta = dist / threads;

	std::vector<std::thread> thrd;

	for (size_t i = 0; i != threads; ++i)
	{
		It end = std::next(p, delta);

		if (i == threads - 1) 
			end = q;

		thrd.emplace_back([&res](It b, It e, func1 ff1, func2 ff2) {
			if (res == r_type{})
			{
				res = ff1(*b);
				b++;
			}
			while (b != e)
			{
				res = ff2(res, ff1(*b));
				b++;
			}
		}, p, end, f1, f2);

		p = std::next(p, delta);
	}

	for (auto& th : thrd)
		th.join();

	return res;
}
