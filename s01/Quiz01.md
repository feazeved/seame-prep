Quiz:

1. Why can't unique_ptr be copied, and what would go wrong if it could?
2. After std::string s = "hi"; std::string t = std::move(s); what can you safely do with s?
3. When do you pass a shared_ptr by value, and when by const&?
4. Why do many embedded projects forbid heap allocation after initialisation?


Answers:

1. It can't be copied because it defeats unique_ptr's purpose. If you copy a unique_ptr and also point to the same allocated object, the whole idea of only one place owning that and being responsible for its deletion is broken. Things like a fd can be sinlently closed by a first unique_ptr and the second one would not have no way of knowing this happened. Unique_ptr don't have a control block and lock() like a weak_ptr. This can lead to hard to debug bugs. The problem would be in a silent close while the loud crash would happen when another unique_ptr would try to use that fd.

2. The idea of std::move is that the object that got moved is left in a valid (yet unknown) state. This is also true in this question. After the move, you're safe to check s.size(), s.append(), s.swap()... In case of a std::string after a move, s is simply an empty std::string!

3. You pass a shared_ptr by value when you want to increase the number of owners in the control block. You might do this to extend the object's lifetime. You should pass it by a const& when you don't want to increase the number of owners (and you're also not allocating any new memory nor copying unnecessary memory).

4. Many embedded project forbid heap allocation after initialisation because it gives room to non determinism. You'd need to be aware of any potential error in a lot of places in code. Also, most of the times in embedded projects, you have a small capacity for storage, you have strictly restrained resources and relying in heap allocations is not a great idea. Also, in general, accessing memory from the stack is quicker than accessing heap memory and embedded systems do care about this defference.
