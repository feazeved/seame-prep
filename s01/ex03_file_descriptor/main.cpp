#include "FileDescriptor.hpp"

#include <fcntl.h>
#include <cstdio>
#include <cstdint>
#include <array>
#include <algorithm>

void	experiment();

int main() {
	std::printf("--- T1 ---\n");
	{
		FileDescriptor	fd{ "/dev/urandom", O_RDONLY };

		constexpr std::int32_t toRead = 16;
		std::array<std::uint8_t, toRead>	arr;

		fd.read_exact(arr.data(), toRead);

		std::for_each_n(arr.data(), arr.size(), [](uint8_t byte) { std::printf("%02x ", byte); });
	}
	std::printf("\n--- T2 ---\n");
	{
		experiment();
	}
}
