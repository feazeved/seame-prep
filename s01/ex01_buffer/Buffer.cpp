#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <utility>

#include "Buffer.hpp"

Buffer::Buffer(std::size_t n) : size_(n) {
	std::printf("[Buffer] Constructor (size %zu)\n", size_);
	data_ = new uint8_t[n]();
	if (!data_)
		std::abort();
}

Buffer::Buffer(const Buffer& other) : size_(other.size_) {
	std::printf("[Buffer] Copy constructor (size %zu)\n", size_);
	data_ = new uint8_t[other.size_]();
	if (!data_)
		std::abort();
	std::copy_n(other.data_, other.size_, data_);
}

Buffer::Buffer(Buffer&& other) noexcept {
	std::printf("[Buffer] Move constructor (size %zu)\n", other.size_);
	swap(other);
}

// I learnt this way of doing copy swap. It seems better
// Buffer&	Buffer::operator=(Buffer other) {
// 	std::printf("[Buffer] Copy assignment (size %zu)\n", other.size_);
// 	swap(other);
// 	return (*this);
// }

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

	return (*this);
}

Buffer::~Buffer() {
	std::printf("[Buffer] Destructor (size %zu)\n", size_);
	delete[] data_;
}

// ----- Public member functions -----

// Saw this implementation as well
// friend void swap(Buffer& first, Buffer& second) // nothrow
// {
//     // enable ADL (not necessary in our case, but good practice)
//     using std::swap;
//
//     // by swapping the members of two objects,
//     // the two objects are effectively swapped
//     swap(first.size_, second.size_);
//     swap(first.data_, second.data_);
// }

void				Buffer::swap(Buffer& other) noexcept {
	std::swap(size_, other.size_);
	std::swap(data_, other.data_);
}

std::size_t			Buffer::size() const noexcept { return size_; }
std::uint8_t*		Buffer::data() noexcept { return data_; }
const std::uint8_t*	Buffer::data() const noexcept { return data_; }
