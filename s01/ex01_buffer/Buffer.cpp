#include "Buffer.hpp"

#include <cstdio>
#include <algorithm>
#include <utility>

Buffer::Buffer(std::size_t n) :
	data_(new std::uint8_t[n]()),
	size_(n)
{
	std::printf("[Buffer] Constructor (size %zu)\n", size_);
}

Buffer::Buffer(const Buffer& other) :
	data_(new std::uint8_t[other.size_]),
	size_(other.size_)
{
	std::printf("[Buffer] Copy constructor (size %zu)\n", size_);
	std::copy_n(other.data_, other.size_, data_);
}

Buffer::Buffer(Buffer&& other) noexcept {
	std::printf("[Buffer] Move constructor (size %zu)\n", other.size_);
	Buffer::swap(other);
}

Buffer&	Buffer::operator=(const Buffer& other) {
	std::printf("[Buffer] Copy assignment (size %zu)\n", other.size_);
	Buffer	temp(other);
	swap(temp);
	return *this;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept {
	std::printf("[Buffer] Move assignment (size %zu)\n", other.size_);
	if (this == &other)
		return *this;

	delete[] data_;

	data_ = other.data_;
	size_ = other.size_;
	other.data_ = nullptr;
	other.size_ = 0;

	return *this;
}

Buffer::~Buffer() {
	std::printf("[Buffer] Destructor (size %zu)\n", size_);
	delete[] data_;
}

// ----- Public member functions -----

void				Buffer::swap(Buffer& other) noexcept {
	other.size_ = std::exchange(size_, other.size_);
	other.data_ = std::exchange(data_, other.data_);
}

std::size_t			Buffer::size() const noexcept { return size_; }
std::uint8_t*				Buffer::data() noexcept { return data_; }
const std::uint8_t*		Buffer::data() const noexcept { return data_; }
