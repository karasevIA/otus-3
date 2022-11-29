#pragma once

#include <iostream>

namespace My {
    template <typename T>
    struct Iterator {
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;
        
        pointer p;

        Iterator() : p(nullptr) {};

        Iterator(T* _p) : p(_p) {};

        reference operator*() {
            return *p;
        }

        pointer operator->() {
            return p;
        }

        Iterator<T>& operator++() {
            if (p) {
                p += 1;
            }
            return *this;
        }

        bool operator==(const Iterator<T>& other) const {
            return p == other.p;
        }

        bool operator!=(const Iterator<T>& other) const {
            return p != other.p;
        }
    };

    template<typename T, typename ALL = std::allocator<T>>
    class Container {
    public:
        Container() : data(nullptr), count(0), alloc() {}
        ~Container() {
            if (count) {
                alloc.deallocate(data, count);
            }
        }
        void push_back(const T& e) {
            T* tmp = alloc.allocate(count + 1);
            for (std::size_t i = 0; i < count; ++i) {
                tmp[i] = data[i];
            }
            tmp[count] = e;
            if (count) {
                alloc.deallocate(data, count);
            }
            data = tmp;
            count += 1;
        }
        Iterator<T> begin() const noexcept {
            return Iterator<T>(data);
        }
        Iterator<T> end() const noexcept {
            return Iterator<T>(data + count);
        }
    private:
        T* data;
        std::size_t count;
        ALL alloc;
    };
}