Predictions of what will happen in each test case line by line.

T1:
	construction of Buffer a (size 4)
	copy construction of Buffer b from a (size 4)
	
	print Buffer a: 42 42 42 42 (size 4)
	print Buffer b: 42 42 42 42 (size 4)
	
	destruction Buffer b
	destruction Buffer a

T2:
	construction of Buffer a (size 4)
	move construction of Buffer b from a (size 4)

	print Buffer a: (size 0)
	print Buffer b: 42 42 42 42 (size 4)

	destruction Buffer b
	destruction Buffer a

T3:
	construction Buffer a (size 4)
	construction Buffer b (size 2)
	copy assignment of b from a (size 4)

	print Buffer a: 42 42 42 42 (size 4)
	print Buffer b: 42 42 42 42 (size 4)

	destruction Buffer b
	destruction Buffer a

T4:
	construction Buffer a (size 4)
	construction Buffer b (size 2)
	move assignment of b from a (size 4)

	print Buffer a: (size 0)
	print Buffer b: 42 42 42 42 (size 4)

	destruction Buffer b
	destruction Buffer a

I predict all assertions will pass.