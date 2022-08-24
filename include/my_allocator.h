#pragma once

#include <cstddef>

namespace My {
	template <typename T>
	struct Allocator {
		using value_type = T;

		Allocator();

		template <typename U>
		Allocator(const Allocator<U>&);

		T* allocate (std::size_t n);
		
		void deallocate (T* p, std::size_t n);
	};
}