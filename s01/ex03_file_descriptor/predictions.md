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


Experiment: I tried removing std::exchange from move constructor initialization list and not making other.fd_ = -1.

I predict FD a will have fd_ 3 from "/dev/urandom". Then, b will have fd_ 3 as well but will fall out of scope and CLOSE fd 3. But, a will continue with fd_ == 3.
Sequentially, FD c will have fd_ 3 from "/dev/zero". But then, a.reset() will call a's destructor (which closes fd 3 that now was c's).
Therefore, c.read_exact will have a closed fd as reference and read will fail with -1 -> throwing a system_error EBADF. This is even worse than it looks when you realize that the bug was present in the special move member function of FD bbut the problem and crash only happened far after that, during a read!
There is a log.txt file showing the error.

This is exaclty what happened.

This is a dengerous bug and shows, in practice, why managing resources in move functions is tricky. Having only one owner is important to assure something like this is impossible of happening and not making "other.fd_" == -1, the ownership was not given!
