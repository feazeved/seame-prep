Predictions of what will happen in each test case line by line.

T1:
	open "/dev/urandom" -> fd 3
	<16 random bytes printed here>
	close fd 3

T2:
	open "/dev/urandom" -> fd 3
	// move construct and fd's ownership goes to FD b
	close fd 3 (because FD b goes out of scope)
	open "/dev/zero" -> fd 3
	// a.reset() calls destructor for a and nothing happens because it's fd is already -1 due to move logic in class
	read from c OK
	close fd 3 (/dev/zero)
