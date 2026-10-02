This exercise's goal is to learn about move semantics.

Why not write a copy assignment as Buffer& operator=(Buffer other) while also keeping the move assignment? The compiler will say that this is ambiguous. Both the copy assignment and move would accept rvalues!

So there needs to be a rule. Only one operator= taking it by-value! Either a single by-value operator= or the const& + && pair. I still don't understand rvalue costing more in the first case.

I wrote a predictions.md with what I expected of the tests outputs.
