#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>

#include "Buffer.hpp"

void	print(const Buffer& b) {
	std::printf("Buffer of size: %zu\n", b.size());
	std::for_each_n(b.data(), b.size(), [](uint8_t value) { std::printf("%d ", value); });
	std::printf("\n");
}

Buffer makeBuffer(std::size_t n) { Buffer b(n); return b; }

int	main() {
	std::printf("--- T1 ---\n");
	{
		Buffer a{ 4 };
		a.data()[1] = 1;
		print(a);
	}
	std::printf("\n--- T2 ---\n");
	{
		Buffer a{ 4 };
		Buffer b{ a };

		print(a);
		print(b);

		assert(a.data() != b.data());
	}
	std::printf("\n--- T3 ---\n");
	{
		Buffer a{ 4 };
		const std::uint8_t* p = a.data();

		Buffer b{ std::move(a) };

		assert(b.data() == p && a.data() == nullptr && a.size() == 0);
	}
	std::printf("\n--- T4 ---\n");
	{
		Buffer a{ 4 };
		Buffer b{ 2 };

		b = a;

		print(a);
		print(b);

		assert(a.size() == b.size() && a.data() != b.data() && a.data()[0] == b.data()[0]);
	}
	std::printf("\n--- T5 ---\n");
	{
		Buffer a{ 4 };
		Buffer b{ 2 };

		b = std::move(a);

		print(a);
		print(b);

		assert(a.size() == 0 && a.data() == nullptr);
	}
	std::printf("\n--- T6 ---\n");
	{
		Buffer a{ 4 };

		a = a;

		print(a);
	}
	std::printf("\n--- T7 ---\n");
	{
		Buffer e = makeBuffer(8);

		print(e);
	}
	std::printf("\n--- T8 ---\n");
	{
		std::vector<Buffer>	v;

		for (int i = 0; i < 4; i++) {
			v.push_back(Buffer(i));
		}
	}
	std::printf("\n--- T9 ---\n");
	{
		std::vector<Buffer> v;

		v.reserve(3);
		for (int i = 0; i < 4; i++) {
			v.push_back(Buffer(i));
		}
	}
}
