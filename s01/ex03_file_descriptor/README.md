In this exercise, the idea is to encapsulate a system resource in a class and understand how to properly manage it's lifetime and ownership.

You should run the binary with "strace -e trace=openat,read,close ./program"

In the output, you should see what are the steps done by the system. Which file is openned and what fd it gets etc.

The first 5 "openat" + read + close operations are interesting. All of them happen before your program execution. They are shared libraries dependencies. You can get them running "ldd ./program":

fesuassuna@seame-vm:~/Projects/seame-prep/s01/ex03_file_descriptor$ ldd ./test
	linux-vdso.so.1 (0x0000feaae9bf7000)
	libstdc++.so.6 => /lib/aarch64-linux-gnu/libstdc++.so.6 (0x0000feaae98f0000)
	libgcc_s.so.1 => /lib/aarch64-linux-gnu/libgcc_s.so.1 (0x0000feaae98b0000)
	libc.so.6 => /lib/aarch64-linux-gnu/libc.so.6 (0x0000feaae96f0000)
	/lib/ld-linux-aarch64.so.1 (0x0000feaae9bb0000)
	libm.so.6 => /lib/aarch64-linux-gnu/libm.so.6 (0x0000feaae9640000)

or "readelf -d ./program":


fesuassuna@seame-vm:~/Projects/seame-prep/s01/ex03_file_descriptor$ readelf -d ./test | grep "NEEDED"
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libgcc_s.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [ld-linux-aarch64.so.1]

Here, we can see that our executable depends on these shared libraries. They are:

1. libstdc++ (located in "/lib/aarch64-linux-gnu/libstdc++.so.6") -> It provides implementations of things such as std::string, std::vector, std::iostream, std::exception etc.
2. libgcc -> It provides support for things related to exception handling, stack unwinding, certain runtime operations etc.
3. libc -> It provides the standard C library. Things like printf, malloc, free, memcpy, strlen etc are linked from here.
4. libm -> Despite not being in "NEEDED", it was still linked, as you can see from ldd and strace outputs. It provides functions related to mathematics. Such as sin(), cos(), tan(), sqrt(), pow()...

And if you pay attention to strace's first output line, it references "/etc/ld.so.cache". This is the dynamic's linker cache. It keeps stored the location of these shared libraries so that the dynamic linker does not need to search every directory one by one.

Its also interesting to see the inputs from the "read()"s into those libraries. They show us something like "\177ELF\2\1\1\0\0\0\0...". This first read's purpose is to understand how to load this library. ELF means "Executable and Linkable Format". That way, the loader is basically understanding that "this is a 64-bit little-endian AArch64 ELF shared object".
