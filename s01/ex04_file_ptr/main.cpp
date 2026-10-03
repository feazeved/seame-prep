#include "FileCloser.hpp"

#include <cstdio>
#include <memory>
#include <system_error>
#include <cerrno>
#include <cstdint>
#include <cstddef>
#include <array>
#include <cassert>

using FilePtr = std::unique_ptr<std::FILE, FileCloser>;

FilePtr	open_file(const char* path, const char* mode) {
	std::FILE* fptr = std::fopen(path, mode);
	if (!fptr)
		throw std::system_error(errno, std::generic_category());
	return FilePtr(fptr);
}

int	main() {
	std::printf("--- T1 ---\n");
	{
		FilePtr	fptr = open_file("/dev/urandom", "rb");

		constexpr std::size_t	size = 16;
		std::array<std::uint8_t, size>	arr{};


		std::size_t	n = std::fread(
			arr.data(),
			sizeof(arr[0]),
			arr.size(),
			fptr.get()
		);

		std::printf("Reading 16 bytes into arr...\n");

		assert(n == size);

		for (std::uint8_t byte : arr)
			std::printf("%02x ", byte);

		std::printf("\n");
	}
	std::printf("\n--- T2 ---\n");
	{
		std::printf("Comparing sizes...\n");

		std::printf("sizeof std::FILE*: %zu\n", sizeof(std::FILE*));
		std::printf("sizeof FileCloser: %zu\n", sizeof(FileCloser));
		std::printf("sizeof FilePtr (std::unique_ptr<std::FILE, FileCloser>): %zu\n", sizeof(FilePtr));
		std::printf("sizeof void(*)(std::FILE*): %zu\n", sizeof(void(*)(std::FILE*)));
		std::printf("sizeof std::unique_ptr<std::FILE, void(*)(std::FILE*)>: %zu\n", sizeof(std::unique_ptr<std::FILE, void(*)(std::FILE*)>));
	}
}
