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
    SparseVector() noexcept {m_length = 0;}
//    SparseVector(const SparseVector& cp) noexcept; // Copy

    SparseVector(std::initializer_list<T> il) noexcept
    {
        m_length = il.size();
        m_keyToIndex.reserve(m_length);
        m_data.reserve(m_length);
        for(T x : il)
        {
            push_back(x);
        }
    }

    T& operator[](const size_t& index) noexcept
    {
        return m_data[index];
    }

    size_t Add(const T &x)
    {
        for(int i = 0; i < m_data.size(); ++i)
        {
            if(m_keyToIndex[i] == -1)
            {
                m_keyToIndex[i] = m_length;
                m_indexToKey.push_back(i);
                m_data.push_back(x);
                ++m_length;
                return m_keyToIndex[i];
            }
        }
        m_keyToIndex.push_back(m_length);
        m_data.push_back(x);
        m_indexToKey.push_back(m_length);
        ++m_length;
        return m_length-1;
    }

    void Remove(size_t n){
        size_t index = m_keyToIndex[n];

        size_t lastIndex = m_length-1;
        std::swap(m_data[index],m_data[lastIndex]);
        m_data.erase(begin(m_data)+lastIndex);//-1);

        m_keyToIndex[n] = -1; // show no value stored at this key
        size_t tmpKey = m_indexToKey[lastIndex]; // Get key for moved entry
        m_keyToIndex[tmpKey] = index; // Reassign our key for moved data to its new location

        m_indexToKey[index] = tmpKey; // Reassign the data index its new key
        m_indexToKey.pop_back();
        --m_length;
    }

    size_t size()
    {
        return m_length;
    }

    T& At(size_t key)
    {
        size_t index = m_keyToIndex[key];
        return m_data[index];
    }
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SPARSEVECTOR_H
