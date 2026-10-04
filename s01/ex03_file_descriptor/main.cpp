#include "FileDescriptor.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdint>
#include <array>
#include <algorithm>
#include <cerrno>
#include <cassert>
#include <thread>
#include <chrono>
#include <stdexcept>

void	experiment();

int main() {
	std::printf("--- T1 ---\n");
	{
		FileDescriptor	fd{ "/dev/urandom", O_RDONLY };

		constexpr std::size_t toRead = 16;
		std::array<std::uint8_t, toRead>	arr;

		fd.read_exact(arr.data(), toRead);

		std::for_each_n(arr.data(), arr.size(), [](std::uint8_t byte) { std::printf("%02x ", byte); });
		std::printf("\n");
	}
	std::printf("\n--- T2 ---\n");
	{
		experiment();
	}
	std::printf("\n--- T3 ---\n");
	{
		int	pipefd[2];

		if (::pipe(pipefd) == -1)
			throw std::system_error(errno, std::generic_category());

		FileDescriptor	reader(pipefd[0]);

		std::thread	writer([fd = pipefd[1]]() {
			ssize_t	bytes = ::write(fd, "AB", 2);

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			bytes += ::write(fd, "CD", 2);

			::close(fd);

			assert(bytes == 4);
		});

		std::uint8_t	buf[4] = {};

		reader.read_exact(buf, 4);

		assert(buf[0] == 'A');
		assert(buf[1] == 'B');
		assert(buf[2] == 'C');
		assert(buf[3] == 'D');

		writer.join();
	}
	std::printf("\n--- T4 ---\n");
	{
		int	pipefd[2];

		if (::pipe(pipefd) == -1)
			throw std::system_error(errno, std::generic_category());

		FileDescriptor	reader(pipefd[0]);

		std::thread	writer([fd = pipefd[1]]() {
			ssize_t	bytes = ::write(fd, "AB", 2);

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			::close(fd);

			static_cast<void>(bytes);
			assert(bytes == 2);
		});

		std::uint8_t	buf[4] = {};

		[[maybe_unused]] bool	caught = false;

		try {
			reader.read_exact(buf, 4);
		} catch (const std::runtime_error& e) {
			caught = true;
		}

		writer.join();

		assert(caught == true);
	}
}
