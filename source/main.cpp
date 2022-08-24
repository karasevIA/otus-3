#include <iostream>
#include <vector>
#include "include/my_allocator.h"

int main()
{
    std::cout << "Hello" << std::endl;
    
    std::vector<int, My::Allocator<int>> vector;

	// for (int i = 0; i < 10; ++i) {
	// 	vector.push_back(i);
	// }

	// for (const auto& v : vector) {
	// 	std::cout << v << ' ';
	// }

	// std::cout << std::endl;

	// auto other = vector;

	// for (const auto& v : other) {
	// 	std::cout << v << ' ';
	// }
	// std::cout << std::endl;
    
    return 0;
}