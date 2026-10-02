#include "Buffer.hpp"

#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstring>

void	print(const Buffer& b) {
	std::printf("Buffer of size: %zu\n", b.size());
	std::for_each_n(b.data(), b.size(), [](std::uint8_t value) { std::printf("%d ", value); });
	std::printf("\n");
}

int main() {
	std::printf("--- T1 ---\n");
	{
		Buffer	a{ 4 };

		std::fill_n(a.data(), a.size(), 42);

		Buffer	b{ a };

		print(a);
		print(b);

		assert(b.data() != a.data());
		assert(!std::memcmp(a.data(), b.data(), a.size()));
	}
	std::printf("\n--- T2 ---\n");
	{
		Buffer	a{ 4 };

		std::fill_n(a.data(), a.size(), 42);

		[[maybe_unused]] const uint8_t*	p = a.data();

		Buffer	b{ std::move(a) };

		print(a);
		print(b);

		assert(b.data() == p);
		assert(a.size() == 0);
	}
	std::printf("\n--- T3 ---\n");
	{
		Buffer	a{ 4 };
		Buffer	b{ 2 };

		std::fill_n(a.data(), a.size(), 42);

		b = a;

		print(a);
		print(b);

		assert(a.data() != b.data());
		assert(b.size() == a.size());
		assert(!std::memcmp(a.data(), b.data(), a.size()));
	}
	std::printf("\n--- T4 ---\n");
	{
		Buffer	a{ 4 };
		Buffer	b{ 2 };

		std::fill_n(a.data(), a.size(), 42);

		b = std::move(a);

		print(a);
		print(b);

		assert(a.size() == 0);
		assert(b.size() == 4);
	}
}
