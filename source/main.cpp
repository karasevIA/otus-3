#include <iostream>
#include <vector>

#include <include/my_allocator.hpp>
#include <include/my_container.hpp>

int factorial(int n) {
	return n < 2 ? 1 : n*factorial(n-1);
}

int main()
{
    // std::cout << "Hello" << std::endl;
    
	// My::Allocator<int>::set_block_size(16);
	// std::cout << "Init vector" << std::endl;

	// std::vector<int, My::Allocator<int>> vector;

	// for (int i = 0; i < 10; ++i) {
	// 	vector.push_back(i);
	// }

	// for (const auto& v : vector) {
	// 	std::cout << v << ' ';
	// }
	// std::cout << std::endl;

	// auto other = vector;

	My::Container<int, My::Allocator<int>> myvect;

	for (int i = 0; i < 10; ++i) {
		myvect.push_back(factorial(i));
	}

	for (auto e : myvect) {
		std::cout << e << ' ';
	}
	std::cout << std::endl;

	///std::cout << "aaaa" << std::endl;
	//for (const auto& v : other) {
	//	std::cout << v << ' ';
	//}
	std::cout << std::endl;

    return 0;
}