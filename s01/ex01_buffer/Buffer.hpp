#pragma once

#include <cstdint>
#include <cstddef>

class Buffer {
public:
	explicit Buffer(std::size_t n);
	Buffer(const Buffer& other);
	Buffer(Buffer&& other) noexcept;
	Buffer& operator=(const Buffer& other);
	Buffer& operator=(Buffer&& other) noexcept;
	~Buffer();

	void				swap(Buffer& other) noexcept;

	std::size_t			size() const noexcept;
	std::uint8_t*		data() noexcept;
	const std::uint8_t*	data() const noexcept;

private:
	std::uint8_t*	data_ = nullptr;
	std::size_t		size_ = 0;
};
