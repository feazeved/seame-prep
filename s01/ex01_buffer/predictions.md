Predictions of what will happen in each test case line by line.

T1:
	Constructor for size 4
	Print Buffer of size 4 (0 1 2 3)
	Destructor of size 4

T2:
	Constructor for size 4 (a)
	Copy constructor for size 4 (b)
	Print Buffer of size 4 (a)
	Print Buffer of size 4 (b)
	Destructor for size 4 (b)
	Destructor for size 4 (a)

T3:
	Constructor for size 4 (a)
	Move constructor for size 4 (b)
	Destructor for size 4 (b)
	Destructor for size 0 (a)

T4:
	Constructor for size 4 (a)
	Constructor for size 2 (b)
	Copy assign for size 4
	Copy constructor for size 4 (temp)
	Destructor for size 4 (temp) -> output: Destructor for size 2 (temp) since copy assign does a swap, when temp gets destroyed, it has a size of 2.
	Print Buffer for size 4 (a)
	Print Buffer for size 4 (b)
	Destructor for size 4 (b)
	Destructor for size 4 (a)

T5:
	Constructor for size 4 (a)
	Constructor for size 2 (b)
	Move assign for size 4
	Print Buffer for size 0 (a)
	Print Buffer for size 4 (b)
	Destructor for size 4 (b)
	Destructor for size 0 (a)

T6:
	Constructor for size 4 (a)
	Copy assign for size 4
	Copy constructor for size 4 (temp)
	Destructor for size 4 (temp)
	Print Buffer for size 4
	Destructor for size 4 (a)
	
T7:
	Constructor for size 8 (e)
	Print Buffer for size 8
	Destructor for size 8

T8:
what I predicted:
	Constructor for size 0 (0)
	Move constructor for size 0 (0)
	Move constructor for size 0 (0)
	Destructor for size 0 (0)
	Constructor for size 1 (1)
	Move constructor for size 1 (1)
	Move constructor for size 0 (0)
	Move constructor for size 1 (1)
	Constructor for size 2 (2)
	Move constructor for size 2 (2)
	Destructor for size 0 (0)
	Destructor for size 0 (1)
	Constructor for size 3 (3)
	Move constructor for size 3 (3)
	Destructor for size 0 (3)
	Destructor for size 0 (2)
	Destructor for size 0 (1)
	Destructor for size 0 (0)
	Destructor for size 3 (3)
	Destructor for size 2 (2)
	Destructor for size 1 (1)
	Destructor for size 0 (0)

what happened:
	Constructor for size 0 (0)
	Move constructor for size 0 (0)
	Destructor for size 0 (0)
	
	// Right now the vector is: 0
	
	Constructor for size 1 (1)
	Move constructor for size 1 (1)
	Move constructor for size 0 (0)
	Destructor for size 0 (1)
	Destructor for size 0 (0)

	// Right now the vector is: 0 1

	Constructor for size 2 (2)
	Move constructor for size 2 (2)
	Move constructor for size 0 (0)
	Destructor for size 0 (2)
	Move constructor for size 1 (1)
	Destructor for size 0 (1)
	Destructor for size 0 (0)

	// Right now the vector is: 0 1 2

	Constructor for size 3 (3)
	Move constructor for size 3 (3)
	Destructor for size 0 (3)

	// Right now the vector is: 0 1 2 3. No reallocations due to already having enough space

	Destructor for size 0 (0)
	Destructor for size 1 (1)
	Destructor for size 2 (2)
	Destructor for size 3 (3)

what I learned: The flow of addition when there is space for the new element is: Construction of the new element -> Move constructor of that element in the vector space -> Destructor of the first object. And I learned that the flow for when there is no space left and reallocation is necessary is: Construction of the new element -> Move constructor of that element -> Destructor of the first instance of it -> and then Move constructor of all the elements that were present in the vector -> lastly, Destructor of the instances of those elements in the previous region.
I predicted objects would be destroyed in reverse order after the vector would run out of scope but what actually happened was a destruction in ascending order. This does not seem reliable though, apparently this is not standardized.
	
T9:
	Constructor for size 0 (0)
	Move constructor for size 0 (0)
	Destructor for size 0 (0)
	Constructor for size 1 (1)
	Move constructor for size 1 (1)
	Destructor for size 0 (1)
	Constructor for size 2 (2)
	Move constructor for size 2 (2)
	Destructor for size 0 (2)
	Constructor for size 3 (3)
	Move constructor for size 3 (3)
	Destructor for size 0 (3)
	Destructor for size 3 (3)
	Destructor for size 2 (2)
	Destructor for size 1 (1)
	Destructor for size 0 (0)

Regarding T9, the only error is present in the last lines regarding order of destruction. I predicted objects would be destroyed in reverse order. I had in mind destruction would be LIFO. But I learned this is not standardized and what happened was a destruction in ascending order: 0 1 2 3.
