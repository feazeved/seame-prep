Quiz:

1. Why can't unique_ptr be copied, and what would go wrong if it could?
2. After std::string s = "hi"; std::string t = std::move(s); what can you safely do with s?
3. When do you pass a shared_ptr by value, and when by const&?
4. Why do many embedded projects forbid heap allocation after initialisation?


Answers:

1. It can't be copied because it defeats unique_ptr's purpose. If you copy a unique_ptr and also point to the same allocated object, the whole idea of only one place owning that and being responsible for its deletion is broken. Things like a fd can be sinlently closed by a first unique_ptr and the second one would not have no way of knowing this happened. Unique_ptr don't have a control block and lock() like a weak_ptr. This can lead to hard to debug bugs. The problem would be in a silent close while the loud crash would happen when another unique_ptr would try to use that fd. A more concrete failure is a double delete! That's undefined behaviour. Regardless, it's important to know that if you want to transfer ownership you can explicitly use std::move since the copy constructor is "= delete".

2. The idea of std::move is that the object that got moved is left in a valid (yet unknown) state. This is also true in this question. After the move, you're safe to check s.size(), s.append(), s.swap()... But you're not safe to try s[0], s.front(), s.back()... So, before assuming that s became empty, you should always call s.clear().

3. You pass a std::shared_ptr by value when the function is meant to participate in shared ownership—for example, when it needs to keep a copy, pass ownership to another object/thread, or otherwise extend the object's lifetime. Passing by value creates another shared_ptr owner, increasing the reference count.
You pass a std::shared_ptr by const& when the function needs to access the shared_ptr itself but does not need to create another owner. This avoids the reference-count increment/decrement caused by copying the shared_ptr.
If the function only needs to use the pointed-to object and does not care about ownership, it is usually better to pass T& or const T& instead of a shared_ptr at all.

Copying a shared_ptr does not copy the pointed-to object or allocate new memory for it. The cost is mainly the reference-count update (typically an atomic operation) and the matching decrement when the copy is destroyed.
4. Many embedded project forbid heap allocation after initialisation because it gives room to non determinism. You'd need to be aware of any potential error in a lot of places in code. Also, most of the times in embedded projects, you have a small capacity for storage, you have strictly restrained resources and relying in heap allocations is not a great idea. Other valid points against heap allocation:
- Unpredictable malloc timing can break real-time deadlines
- Failure at startup is safe; Failure mid-flight has no good recovery.
- Fragmentation: A running for days program can have enough free memory according to your calculations but no single block big enough.
