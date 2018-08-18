#pragma once

#include <array>
#include <cstdint>

namespace lib {

int version_major();
int version_minor();
int version_patch();

size_t factorial(int);

template<typename T, std::size_t storage_size>
struct const_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;


    struct block {
        bool is_used{false};
        uint8_t data[sizeof(value_type)];
    };

    template<typename U>
    struct rebind {
        using other = const_allocator<U, storage_size>;
    };

    const_allocator() = default;
    ~const_allocator() = default;

    pointer allocate(std::size_t n) {
        auto p = find_free_block();
        if (!p)
            throw std::bad_alloc();
        return p;
    }

    void deallocate(pointer p, std::size_t n) {
        for(auto& block : m_storage) {
            if(p == reinterpret_cast<pointer>(block.data) && !block.is_used ) {
                block.is_used = false;
            }
        }
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

private:
    std::array<block, storage_size> m_storage;

    pointer find_free_block()
    {
        for(auto& block : m_storage) {
            if (!block.is_used) {
                block.is_used = true;
                return reinterpret_cast<T*>(block.data);
            }
        }

        return nullptr;
    }
};

template<typename T, typename A = std::allocator<lib::custom_list::node>>
class custom_list
{
    using value_type = T;
    using allocator_type = A;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    struct node {
        pointer data;
        node* next{nullptr};
        node* previous{nullptr};
    };

    void push_back( const T& value ) {
        auto p = m_allocator.allocate(1);

        new(p, value);

        if(m_back){
            m_back->data = p;
        }
    }



private:
    node* m_front{nullptr};
    node* m_back{nullptr};
    size_t m_size{0};
    allocator_type m_allocator;

};

} // namespace lib
