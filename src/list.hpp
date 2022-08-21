#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdlib>

constexpr size_t INIT_MEM = 16;

template<typename T>
struct List {
    const size_t elem_size;
    size_t size;
    size_t mem;
    T* data;

    auto begin() -> T*
    {
        return data;
    }

    auto end() -> T*
    {
        return (data+size+1);
    }

    auto first() -> T&
    {
        return data[0];
    }

    auto last() -> T&
    {
        return data[size];
    }

    auto alloc(const size_t _mem) -> T*
    {
        return (_mem) ? (T*)std::malloc(elem_size*_mem) : data;
    }

    auto resize(const size_t _mem) -> const void
    {
        switch (_mem) { // realloc 0 guard
            case 0: return data;
            default: break;
        }

        T* new_data = this->alloc(_mem);
        std::copy(this->begin(), data->end(), new_data);
        std::free(data);

        mem = _mem;
        data = new_data;
    }

    auto realloc() -> const void
    {
        this->resize((mem*0.5)+1);
    }

    auto push(const T& _elem) -> const void
    {
        if (size >= mem) this->realloc();

        data[++size] = _elem;
    }

    auto pop() -> T
    {
        --size;
        return data[size+1];
    } 

    auto at(const size_t _idx) -> T&
    {
        if (_idx >= size) std::abort(); // OOB TODO
        return data[_idx];
    }

    auto operator[](const size_t _idx) -> T&
    {
        return this->at(_idx);
    }

    explicit List()
    : elem_size(sizeof(T)), size(0), mem(INIT_MEM), data(this->alloc(mem))
    {}

    explicit List(const size_t _mem)
    : elem_size(sizeof(T)), size(0), mem(_mem), data(this->alloc(mem))
    {}

    ~List()
    {
        size = 0;
        mem = 0;
        std::free(data);
        data = nullptr;
    }
};