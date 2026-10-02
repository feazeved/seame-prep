#pragma once

#include <vector>
#include <cstdint>

class Buffer {
public:
	Buffer(std::size_t n);

	[[nodiscard]] std::size_t		size() const  noexcept;
	[[nodiscard]] const uint8_t*	data() const noexcept;
	[[nodiscard]] uint8_t*			data() noexcept;
	
private:
	std::vector<std::uint8_t>	bytes_;
};
