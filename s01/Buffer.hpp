#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>

typedef	std::size_t size_t;

class Buffer {
	public:
		uint8_t*	arr;
		size_t		size;

		explicit Buffer(const size_t n) : arr(nullptr), size(n) {
			std::cout << "constructor (size " << n << ")\n";
			arr = new uint8_t[n]();
		}

		Buffer(const Buffer& other) : arr(nullptr), size(other.size) {
			std::cout << "copy constructor (size " << other.size << ")\n";
			arr = new uint8_t[other.size]();
			*arr = *other.arr;
		}

		Buffer(Buffer&& other) noexcept : arr(other.arr), size(other.size) {
			std::cout << "move constructor (size " << other.size << ")\n";
			other.arr = nullptr;
			other.size = 0;
		}

		Buffer&	operator=(const Buffer& other) {
			std::cout << "copy assignment operator (size " << other.size << ")\n";
			if (this == &other)
				return *this;

			if (arr)
				delete[] arr;
			arr = new uint8_t[other.size]();
			*arr = *other.arr;
			size = other.size;

			return (*this);
		}

		Buffer&	operator=(Buffer&& other) noexcept {
			std::cout << "move assignment operator (size " << other.size << ")\n";
			if (this == &other)
				return *this;

			arr = other.arr;
			size = other.size;
			other.arr = nullptr;

			return (*this);
		}

		~Buffer() {
			std::cout << "destructor (size " << size << ")\n";
			if (arr)
				delete[] arr;
		}
};
