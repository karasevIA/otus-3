#include "include/my_allocator.h"

#include <iostream>
#include <memory>
#include <vector>

namespace My {
	template <typename T>
	Allocator<T>::Allocator() {
	}

	template <typename T>
	template <typename U>
	Allocator<T>::Allocator(const Allocator<U>& ) {
		// should we make a copy of the rhs.m_buffer ?
		// No, we should not!
	}

	template <typename T>
	T* Allocator<T>::allocate (std::size_t n) {
		auto p = std::malloc(n * sizeof(T));
		if (!p)
			throw std::bad_alloc();
		return reinterpret_cast<T *>(p);
	}

	template <typename T>
	void Allocator<T>::deallocate (T* p, std::size_t ) {
		std::free(p);
	}

	template <class T, class U>
	constexpr bool operator== (const Allocator<T>&, const Allocator<U>&) noexcept {
		return false;
	}

	template <class T, class U>
	constexpr bool operator!= (const Allocator<T>&, const Allocator<U>&) noexcept {
		return false;
	}
}