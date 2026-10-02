#include "Buffer.hpp"

#include <cstdio>

Buffer::Buffer(std::size_t n) :
	bytes_(n, 0)
{
	std::printf("[Buffer] Constructor for size %zu\n", n);
}

std::size_t		Buffer::size() const noexcept { return bytes_.size(); }
const uint8_t*	Buffer::data() const noexcept { return bytes_.data(); }
uint8_t*		Buffer::data() noexcept { return bytes_.data(); }
