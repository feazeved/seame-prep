#include "FileDescriptor.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cerrno>
#include <system_error>
#include <utility>

// ----- Special Member Functions -----

FileDescriptor::FileDescriptor(const char* path, int flags) :
	fd_(::open(path, flags | O_CLOEXEC))
{
	if (fd_ == -1)
		throw std::system_error(errno, std::generic_category(), path);
	std::printf("open %s -> fd %d\n", path, fd_);
}

FileDescriptor::FileDescriptor(int fd) noexcept :
	fd_(fd)
{
	std::printf("taking ownership in already open fd %d\n", fd);
}

FileDescriptor::~FileDescriptor() {
	if (fd_ == -1)
		return ;
	::close(fd_);
	std::printf("close fd %d\n", fd_);
}

FileDescriptor::FileDescriptor(FileDescriptor&& other) noexcept :
	fd_(std::exchange(other.fd_, -1))
{
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
	if (this == &other)
		return *this;

	if (fd_ != -1)
		::close(fd_);
	fd_ = std::exchange(other.fd_, -1);

	return *this;
}

// ----- Public Methods -----

int		FileDescriptor::get() const noexcept { return fd_; }

void	FileDescriptor::read_exact(std::uint8_t* out, std::size_t n) {
	std::size_t		totalBytesRead = 0;
	std::size_t		toRead = n;

	errno = 0;
	while (totalBytesRead != n) {
		ssize_t	tempRead = ::read(fd_, &out[totalBytesRead], toRead);
		if (tempRead == 0)
			return ;
		else if (tempRead == -1) {
			if (errno == EINTR)
				continue ;
			throw std::system_error(errno, std::generic_category());
		}
		toRead -= static_cast<std::size_t>(tempRead);
		totalBytesRead += static_cast<std::size_t>(tempRead);
	}
}
