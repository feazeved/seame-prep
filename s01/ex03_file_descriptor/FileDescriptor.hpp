#pragma once

#include <cstdint>
#include <cstddef>

class FileDescriptor {
public:
	FileDescriptor(const char* path, int flags);
	~FileDescriptor();
	FileDescriptor(const FileDescriptor&) = delete;
	FileDescriptor& operator=(const FileDescriptor&) = delete;
	FileDescriptor(FileDescriptor&& other) noexcept;
	FileDescriptor& operator=(FileDescriptor&& other) noexcept;

	int		get() const noexcept;
	void	read_exact(std::uint8_t* out, std::size_t n);

private:
	int	fd_ = -1;
};
