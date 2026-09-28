#include <utility>
#include <vector>

#include "Buffer.hpp"

uint8_t*	pop_value(Buffer& buf) {
	Buffer temp = std::move(buf);

	return temp.arr;
}

int main() {
	Buffer	First(10);

	Buffer b = 5;

	Buffer Copy(First);

	Buffer Second = std::move(First);
	First = Copy;
	First = std::move(Second);

	uint8_t*	a = pop_value(First);

	Buffer	one(1);
	Buffer	two(2);
	Buffer	three(3);
	Buffer	four(4);
	Buffer	five(5);

	std::vector<Buffer>	vec;
	vec.push_back(one);
	vec.push_back(two);
	vec.push_back(three);
	vec.push_back(four);
	vec.push_back(five);

	std::cout << "----- Main -----\n\n"
			  << a << "\n";
}
