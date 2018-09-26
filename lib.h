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

    const_allocator(const const_allocator&) : m_storage{} {}
    const_allocator(const const_allocator&&) : m_storage{} {}

    bool operator!=(const const_allocator& other) {return true;}
    bool operator==(const const_allocator& other) {return false;}

    const_allocator& operator=(const const_allocator&) {}
    const_allocator& operator=(const const_allocator&&) {}

    pointer allocate(std::size_t n) {
        auto p = find_free_block();
        if (!p)
            throw std::bad_alloc();
        return p;
    }

    void deallocate(pointer p, std::size_t n) {
        for(auto& block : m_storage) {
            if(p == reinterpret_cast<pointer>(block.data) && block.is_used ) {
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

template<typename T, typename A = std::allocator<T>>
class custom_list
{
public:
    using value_type = T;
    using allocator_type = A;

    using pointer = T*;
    using reference = T&;
    using const_reference = const T&;

    struct node {

        node() = default;
        explicit node(const_reference data) : m_data{data} {}

        value_type m_data;
        node* m_next{nullptr};
        node* m_previous{nullptr};
    };
    struct iterator : std::iterator<std::bidirectional_iterator_tag, T> {
        
        explicit iterator(node* current) : m_current(current) {}
        
        iterator& operator++() {
            if (m_current != nullptr) {
                m_current = m_current->m_next;
            }
            
            return *this;
        }

        iterator& operator--() {
            if (m_current != nullptr) {
                m_current = m_current->m_previous;
            }
            
            return *this;
        }

        reference operator*() {
            return m_current->m_data;
        }

        bool operator==(iterator &other) {
            return m_current == other.m_current;
        }

        bool operator!=(iterator &other) {
            return !(*this == other);
        }

      private:
        node* m_current;
    };
    custom_list() = default;

    ~custom_list() {
        auto p = m_front;
        while(p != nullptr) {
            auto next = p->m_next;
            m_allocator.destroy(p);
            m_allocator.deallocate(p, 1);
            p = next;
        }
        m_front = m_back = nullptr;
    }

    void push_back(const_reference value) {

        auto p = m_allocator.allocate(1);

        m_allocator.construct(p, value);

        if(m_back == nullptr) {
            m_back = p;
            m_front = p;
        }
        else {
            m_back->m_next = p;
            p->m_previous = m_back;
            m_back = p;
        }

        m_size++;
    }

    void push_front(const_reference value) {

        auto p = m_allocator.allocate(1);

        m_allocator.construct(p, value);

        if(m_front == nullptr) {
            m_front = p;
            m_back = p;
        }
        else {
            m_back->m_previous = p;
            p->m_next = m_front;
            m_front = p;
        }

        m_size++;
    }

    iterator begin() {
        return iterator(m_front);
    }

    iterator end() {
        return iterator(nullptr);
    }

    size_t size()
    {
        return m_size;
    }

private:
    node* m_front{nullptr};
    node* m_back{nullptr};
    size_t m_size{0};

    using alloc_t = typename allocator_type::template rebind<node>::other;
    alloc_t m_allocator;
};

} // namespace lib