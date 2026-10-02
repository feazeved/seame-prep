#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

class Buffer {
public:
	explicit Buffer(std::size_t n);

	[[nodiscard]] std::size_t			size() const  noexcept;
	[[nodiscard]] const std::uint8_t*	data() const noexcept;
	[[nodiscard]] std::uint8_t*			data() noexcept;

private:
	std::vector<std::uint8_t>	bytes_;
};
