#include "FileCloser.hpp"

#include <cstdio>

void FileCloser::operator()(std::FILE* fp) const noexcept {
	if (std::fclose(fp) == EOF)
		std::fprintf(stderr, "warning: fclose failed\n");
}
