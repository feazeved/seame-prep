This exercise's purpose is to understand the second parameter of a unique/shared pointer, a custom deleter! The default deleter will only call delete on the object and sometimes this is not enough. On this exercise, we work with a file stream and calling ::fclose() is necessary.

Therefore, I created the struct "FileCloser" that will serve as a custom deleter to the unique_ptr in main, FilePtr.

Which do I prefer between this file stream wrapper and the previous exercise's fd wrapper?
I prefer ex03's class. I find it clearer and more intuitive looking at a class constructor and destructor to understand the resource's lifetime. I also find it easier to work with fd rather than file streams.

Though, the point is not which one I prefer. But rather the incapacity of smart pointers wrapping an fd because they're unable to represent the value -1! They absence of value for them is a nullptr. Also, having this version is "Rule of Zero". We needed to write less code and got special members for free.

Doing this exercise, I also learned about EBO (Empty-Base Optimization). The unique_ptr does not pay anything for having a custom deleter instead of its default one! That way, we programmers are free to implement our custom deleters and not pay anything in space for doing so.
