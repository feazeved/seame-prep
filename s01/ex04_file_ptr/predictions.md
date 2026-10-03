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
	sizeof FilePtr: 8
	sizeof std::unique_ptr<std::FILE, void(*)(std::FILE*)>: 16


Why was I wrong? I was not aware of the EBO (Empty-Base Optimization).

Actually, the FilePtr with the custom deleter does not pay anything in space to have it. The size continues as if it was a single unique_ptr to a file stream!

Since the deleter struct FileCloser does not occupy any space and only defines behavior with its operator(), unique and shared ptr are able to optimze the deleter behavior.

C++ implementations can take an empty class and store it as a base class rather than as a normal data member. Therefore, the unique_ptr in this exercise does not have a deleter data member or a pointer to a deleter. The unique_ptr has the FileCloser as a base class and utilizes its behavior to delete the class T not paying anything for it!