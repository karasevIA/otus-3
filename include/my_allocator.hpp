#pragma once

#include <iostream>

namespace {
    struct MemoryNode {
        MemoryNode* next;
        std::size_t size;
        std::size_t capacity;
        void* data;
        MemoryNode(std::size_t cap, void* dat) : capacity(cap), data(dat), next(nullptr) {}
        MemoryNode(MemoryNode* n) : next(n) {}
    };

    struct MemoryBank {
        MemoryNode* list = nullptr;
        std::size_t used = 0;
        std::size_t allocated = 0;
        void* alloc(std::size_t bytes) {
            if (list == nullptr) {
                void* p = std::malloc(sizeof(MemoryNode) + bytes);
                if (!p)
                    throw std::bad_alloc();
                list = new (p) MemoryNode(bytes, (char*)p + sizeof(MemoryNode));
                list->size = bytes;
                allocated += bytes;
                used += bytes;
                return list->data;
            }
            MemoryNode tmp(list);
            MemoryNode* current = &tmp;
            do {
                current = current->next;
                if (current->size == 0 && current->capacity >= bytes) {
                    current->size = bytes;
                    used += bytes;
                    return current->data;
                }
            } while (current->next != nullptr);
            
            void* p = std::malloc(sizeof(MemoryNode) + bytes);
            if (!p)
                throw std::bad_alloc();
            current->next = new (p) MemoryNode(bytes, (char*)p + sizeof(MemoryNode));
            current->next->size = bytes;
            allocated += bytes;
            used += bytes;
            return current->next->data;
        }
        
        void free(void* p) {
            if (p == nullptr)
                throw std::bad_alloc();

            MemoryNode tmp(list);
            MemoryNode* current = &tmp;
            do {
                current = current->next;
                if (current->data == p) {
                    used -= current->size;
                    current->size = 0;
                    return; // success free
                }
            } while (current->next != nullptr);

            throw std::bad_alloc();
        }

        void destruct() {
            MemoryNode* current = list;
            do {
                MemoryNode* next = current->next;
                std::free(current);
                current = next;
            } while (current->next != nullptr);
            std::free(current);
        }

        void print() {
            MemoryNode tmp(list);
            MemoryNode* current = &tmp;
            do {
                current = current->next;
                std::cout << "[" << current->size << "/" << current->capacity << "]->";
            } while (current->next != nullptr);
            std::cout << "|  " << used << "/" << allocated << std::endl;
        }
    };
}

namespace My {
    template <typename T>
    struct Allocator {
        using value_type = T;
        Allocator() {
            //std::cout << "constructor" << std::endl;
            bank = reinterpret_cast<MemoryBank*>(std::calloc(1, sizeof(MemoryBank)));
            std::size_t bs = block_size ? block_size : default_block_size;
            T* p1 = allocate(bs);
            T* p2 = allocate(bs);
            deallocate(p1, bs);
            deallocate(p2, bs);
            //bank->print();
        }

        ~Allocator() {
            //std::cout << "destructor " << bank->used << "/" << bank->allocated << std::endl;
            if (bank->allocated == 0) {
                bank->destruct();
            }
        }

        Allocator(const Allocator& A) {
            //std::cout << "copy constructor" << std::endl;
            bank = A.bank;
        }

        template <typename U>
        Allocator(const Allocator<U>&) {}

        T* allocate (std::size_t n) {
            //std::cout << "allocate " << n << std::endl;
            return reinterpret_cast<T*>(bank->alloc(sizeof(T) * n));
        }

        void deallocate (T* p, std::size_t n) {
            //std::cout << "dealocate " << n << std::endl;
            bank->free(p);
            //bank->print();
        }

        void print() {
            bank->print();
        }

        static void set_block_size(std::size_t s) { if (s > 0) block_size = s; }
        
    private:
        static constexpr std::size_t default_block_size = 10;
        inline static std::size_t block_size = 10;
        MemoryBank* bank;
    };
}

template <class T, class U>
constexpr bool operator== (const My::Allocator<T>&, const My::Allocator<U>&) noexcept {
    return false;
}

template <class T, class U>
constexpr bool operator!= (const My::Allocator<T>&, const My::Allocator<U>&) noexcept {
    return false;
}