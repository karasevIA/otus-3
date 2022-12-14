#include <iostream>
#include <map>

#include <include/my_allocator.hpp>
#include <include/my_container.hpp>

int factorial(int n) {
	return n < 2 ? 1 : n*factorial(n-1);
}

int main()
{
	std::map<int, int> mp;
	
	for (int i = 0; i < 10; ++i) {
		mp[i] = factorial(i);
	}

	My::Allocator<int>::set_block_size(10);
	std::map<int, int, std::less<int>, My::Allocator<int>> mpa;
	
	for (int i = 0; i < 10; ++i) {
		mpa[i] = factorial(i);
	}

	for (auto&& m : mpa) {
		std::cout << m.first << " " << m.second << std::endl;
	}

	My::Container<int> cont;
	for (int i = 0; i < 10; ++i) {
		cont.push_back(factorial(i));
	}

	My::Container<int, My::Allocator<int>> conta;
	for (int i = 0; i < 10; ++i) {
		conta.push_back(factorial(i));
	}

	for (auto&& c : conta) {
		std::cout << c << std::endl;
	}

    return 0;
}