#include "FileCloser.hpp"

#include <cstdio>

void FileCloser::operator()(std::FILE* fp) const noexcept {
	if (fp)
		std::fclose(fp);
}
