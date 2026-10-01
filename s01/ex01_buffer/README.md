This exercise's goal is to learn about move semantics.

Why not write a copy assignment as Buffer& operator=(Buffer other) while also keeping the move assignment? The compiler will say that this is ambiguous. Both the copy assignment and move would accept the same things! But I liked the version taking it by value more, making the copy responsability of the compiler.

I wrote a predictions.md with what I expected of the out tests outputs. Some things annoy me. The output for the T9 test seems wrong...
