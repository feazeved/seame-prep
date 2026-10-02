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

	void							swap(Buffer& other) noexcept;

	[[nodiscard]] std::size_t		size() const noexcept;
	[[nodiscard]] uint8_t*			data() noexcept;
	[[nodiscard]] const uint8_t*	data() const noexcept;

private:
	uint8_t*		data_ = nullptr;
	std::size_t		size_ = 0;
};
