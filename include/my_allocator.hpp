#pragma once

#include <cstddef>
#include <memory>

namespace My {
	template <typename T>
	class Allocator {
	public:
		using value_type = T;

		Allocator();
		~Allocator();

		template <typename U>
		Allocator(const Allocator<U>&);

		T* allocate (std::size_t n);
		void deallocate (T* p, std::size_t n);
		
		static void set_block_size(std::size_t s) { if (s > 0) block_size = s; }
	private:
		void _deallocate();
		void _allocate(std::size_t blocks);

		inline static std::size_t block_size = 10;
		void* pointer;
		std::size_t allocated = 0;
	};
}


#include <iostream>
#include <memory>
#include <vector>

template <typename T>
My::Allocator<T>::Allocator() {
    _allocate(1);
}

template <typename T>
My::Allocator<T>::~Allocator() {
    std::free(pointer);
}

template <typename T>
template <typename U>
My::Allocator<T>::Allocator(const Allocator<U>& ) {
    // should we make a copy of the rhs.m_buffer ?
    // No, we should not!
}

template <typename T>
T* My::Allocator<T>::allocate (std::size_t n) {
    if (n > allocated) {
        _deallocate();
        std::size_t blocks = n / block_size;
        if (n > blocks * block_size) {
            blocks += 1;
        }
        _allocate(blocks);
    }
    return reinterpret_cast<T*>(pointer);
}

template <typename T>
void My::Allocator<T>::_deallocate() {
    auto tmp = pointer;
    pointer = nullptr;
    allocated = 0;
}
	
template <typename T>
void My::Allocator<T>::_allocate(std::size_t blocks) {
    pointer = std::malloc(block_size * blocks * sizeof(T));
    if (!pointer)
        throw std::bad_alloc();
    allocated = block_size * blocks;
}

template <typename T>
void My::Allocator<T>::deallocate (T*, std::size_t) {
    _deallocate();
}

template <class T, class U>
constexpr bool operator== (const My::Allocator<T>&, const My::Allocator<U>&) noexcept {
    return false;
}

template <class T, class U>
constexpr bool operator!= (const My::Allocator<T>&, const My::Allocator<U>&) noexcept {
    return false;
}