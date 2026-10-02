#include "Buffer.hpp"

#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#include <cstring>


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
		for (uint8_t i = 0; static_cast<std::size_t>(i) < a.size(); i++)
			a.data()[i] = i;
		print(a);
	}
	std::printf("\n--- T2 ---\n");
	{
		Buffer a{ 4 };
		Buffer b{ a };

		print(a);
		print(b);

		assert(a.data() != b.data());
		assert(!std::memcmp(a.data(), b.data(), a.size()));
	}
	std::printf("\n--- T3 ---\n");
	{
		Buffer a{ 4 };
		[[maybe_unused]] const std::uint8_t* p = a.data();

		Buffer b{ std::move(a) };

		assert(b.data() == p);
		assert(a.data() == nullptr);
		assert(a.size() == 0);
	}
	std::printf("\n--- T4 ---\n");
	{
		Buffer a{ 4 };
		Buffer b{ 2 };

		std::fill_n(a.data(), a.size(), 42);

		b = a;

		print(a);
		print(b);

		assert(a.size() == b.size());
		assert(a.data() != b.data());
		assert(!std::memcmp(a.data(), b.data(), a.size()));
	}
	std::printf("\n--- T5 ---\n");
	{
		Buffer a{ 4 };
		Buffer b{ 2 };

		b = std::move(a);

		print(a);
		print(b);

		assert(a.size() == 0);
		assert(a.data() == nullptr);
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

		for (std::size_t i = 0; i < 4; i++) {
			v.push_back(Buffer(i));
		}
	}
	std::printf("\n--- T9 ---\n");
	{
		std::vector<Buffer> v;

		v.reserve(4);
		for (std::size_t i = 0; i < 4; i++) {
			v.push_back(Buffer(i));
		}
	}
}
