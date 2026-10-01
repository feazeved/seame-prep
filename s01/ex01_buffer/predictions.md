T1: I predict everything will occur like expected. constructor for size 4, then a change in the first value and this being printed.

T2: I predict we'll see constructor for a and then copy constructor for b. Assert will catch nothing

T3: Normal constructor with size 4 for a then move constructor for b. 

T4: Normal constructors for a and b. Then copy assignment operator for b (size 4)

T5: Normal constructor a (4) and b (2). Then move operator from a to b, leaving a empty with size 0 and b having size 4. No leaks should happen.

T6: Normal constructor and then copy assignment operator called but nothing happens.

T7: Normal constructor for e.

T8: I predict a Normal constructor for 0 and move to vec. Then a move operator for this 0 and construction of 1 -> move to vec. Then move of those 2 and construction of 2 -> move to vec. Then simple construction of 3 -> move to vec.

T9: This one, since memory is being reserved earlier, shouldn't do unnecessary moves! So, normal construction -> move to vec for all of them and no unnecessary moves.
