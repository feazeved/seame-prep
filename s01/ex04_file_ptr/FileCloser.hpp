#pragma once

#include <cstdio>

struct FileCloser {
	void	operator()(std::FILE* fp) const noexcept;
};