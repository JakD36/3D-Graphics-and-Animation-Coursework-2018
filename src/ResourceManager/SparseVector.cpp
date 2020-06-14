////
//// Created by Jack Davidson on 03/06/2020.
////
//
//#include "SparseVector.h"
//
//
//
////template <class T>
////SparseVector<T>::SparseVector() noexcept {}
////
////template <class T>
////SparseVector<T>::SparseVector(const SparseVector& cp) noexcept
////{
////    m_keyToIndex = cp.m_keyToIndex;
////    m_data = cp.m_data;
////}
//
//template <class T>
//SparseVector<T>::SparseVector(std::initializer_list<T> il) noexcept {
//    m_length = il.size();
//    m_keyToIndex.reserve(m_length);
//    m_data.reserve(m_length);
//    for(T x : il)
//    {
//        push_back(x);
//    }
//}
//
//template <class T>
//T& SparseVector<T>::operator[](const size_t &index) noexcept{
//    return m_data[index];
//}
//
//template <class T>
//size_t SparseVector<T>::Add(const T &x) {
//    for(int i = 0; i < m_data.size(); ++i)
//    {
//        if(m_keyToIndex[i] == -1)
//        {
//            m_keyToIndex[i] = m_length;
//            m_indexToKey.push_back(i);
//            m_data.push_back(x);
//            ++m_length;
//            return m_keyToIndex[i];
//        }
//    }
//    m_keyToIndex.push_back(m_length);
//    m_data.push_back(x);
//    m_indexToKey.push_back(m_length);
//    ++m_length;
//    return m_length-1;
//}
//
//template <class T>
//void SparseVector<T>::Remove(size_t n) {
//    size_t index = m_keyToIndex[n];
//
//    size_t lastIndex = m_length-1;
//    std::swap(m_data[index],m_data[lastIndex]);
//    m_data.erase(lastIndex);
//
//    m_keyToIndex[n] = -1; // show no value stored at this key
//    size_t tmpKey = m_indexToKey[lastIndex]; // Get key for moved entry
//    m_keyToIndex[tmpKey] = index; // Reassign our key for moved data to its new location
//
//    m_indexToKey[index] = tmpKey; // Reassign the data index its new key
//    m_indexToKey.pop_back();
//    --m_length;
//}
//
//template <class T>
//size_t SparseVector<T>::size(){
//    return m_length;
//}
//
//template <class T>
//T& SparseVector<T>::At(size_t key){
//    size_t index = m_keyToIndex[key];
//    return m_data[index];
//}