#include "FileDescriptor.hpp"

#include <fcntl.h>
#include <memory>
#include <cstdio>
#include <cstdint>
#include <utility>

void	experiment() {
	auto a = std::make_unique<FileDescriptor>("/dev/urandom", O_RDONLY);
	{
		FileDescriptor	b(std::move(*a));
	}
	FileDescriptor	c("/dev/zero", O_RDONLY);
	a.reset();
	std::uint8_t	buf[4];
	c.read_exact(buf, 4);
	std::printf("read from c OK\n");
}
