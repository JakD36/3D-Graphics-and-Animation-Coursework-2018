//
// Created by Jack Davidson on 03/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SPARSEVECTOR_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SPARSEVECTOR_H

#include <vector>

template <class T>
class SparseVector {
private:
    std::vector<size_t> m_keyToIndex;
    std::vector<size_t> m_indexToKey;
    std::vector<T> m_data;

    size_t m_length;
public:
//    SparseVector() noexcept;
//    SparseVector(const SparseVector& cp) noexcept; // Copy

    SparseVector(std::initializer_list<T> il) noexcept;

    T& operator[](const size_t& index) noexcept;

    size_t Add(const T &x);
    void Remove(size_t n);

    size_t size();

    T& At(size_t key);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SPARSEVECTOR_H
