#include <iostream>
#include <vector>

#include <include/my_allocator.hpp>

int main()
{
    std::cout << "Hello" << std::endl;
    
	My::Allocator<int>::set_block_size(16);
	std::cout << "Init vector" << std::endl;
	std::vector<int, My::Allocator<int>> vector;

	for (int i = 0; i < 10; ++i) {
		vector.push_back(i);
		//vector.get_allocator().print();
	}

	for (const auto& v : vector) {
		std::cout << v << ' ';
	}
	std::cout << std::endl;

	auto other = vector;
	///std::cout << "aaaa" << std::endl;
	//for (const auto& v : other) {
	//	std::cout << v << ' ';
	//}
	std::cout << std::endl;

    return 0;
}