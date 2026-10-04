Predictions of what will happen in each test case line by line.

T1:
	Reading 16 bytes into arr...
	*random 16 bytes written in hex*

T2:
	Comparing sizes...
	sizeof std::FILE*: 8
	sizeof FilePtr: 16
	sizeof std::unique_ptr<std::FILE, void(*)(std::FILE*)>: 16

What actually happened:
	sizeof std::FILE*: 8
	sizeof FileCloser: 1
	sizeof FilePtr: 8
	sizeof void(*)(std::FILE*): 8
	sizeof std::unique_ptr<std::FILE, void(*)(std::FILE*)>: 16

Important to notice that the version with the function pointer is 16 bytes because every instance must store which function to call, and the call can't be inlined.

Why was I wrong? I was not aware of the EBO (Empty-Base Optimization) principle.

Actually, the FilePtr with the custom deleter does not pay anything in space to have it. The size continues as if it was a single unique_ptr to a file stream!

Since the deleter struct FileCloser does not occupy any space and only defines behavior with its operator(), unique ptr is able to optimize the deleter behavior.

C++ implementations can take an empty class and store it as a base class rather than as a normal data member. Therefore, the unique_ptr in this exercise does not have a deleter data member or a pointer to a deleter. The unique_ptr has the FileCloser as a base class and utilizes its behavior to delete the class T not paying anything for it!

In this case, libstdc++ stores the pointer and the deleter in an internal std::tuple, and the tuple is what applies the optimization. 

You're able to get the same effect since C++ 20 with attribute "[[no_unique_address]]" on your own members. For example, let's say you have a class X with an int and a member variable y of data type Empty:

class Empty {};

class X {
	int		x;
	Empty	y;
};

Empty's size is guaranteed to be 1, since a class needs at least a byte to have a valid address. That way, class X will be 8 in an 64 bit architecture (int sizes 4, Empty 1 and 3 bytes of padding). If you use the newly learned attribute:

class X {
	int							x;
	[[no_unique_address]] Empty	y;
};

X's size will be 4, the int's size. The member variable y will share x's address.
