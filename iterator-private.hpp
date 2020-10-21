/**
 * \file iterator-private.hpp
 *
 * \authors Mackenzie Kong-Sivert
 *
 * \brief Implements templated functions for the bit_vector::Iterator class
 */


template <typename Element, typename BitvecIterator>
bit_vector::Iterator<Element, BitvecIterator>::Iterator() :
        index_{0}, byteIt_{BitvecIterator{}}
{
    // nothing more to do here
}

// template <typename Element, typename BitvecIterator>
// bit_vector::Iterator<Element, BitvecIterator>::Iterator(
//             const Iterator<value_type,chunklist_iter_t>& i) :
//             index_{i.index_}, byteIt_{i.byteIt_}
// {
//     // nothing more to do here
// }

template <typename Element, typename BitvecIterator>
bit_vector::Iterator<Element, BitvecIterator>::Iterator(
        uint64_t index, BitvecIterator ByteIt) :
        index_{index}, byteIt_{ByteIt}
{
    // nothing more to do here
}

template <typename Element, typename BitvecIterator>
bit_vector::Iterator<Element, BitvecIterator>&
    bit_vector::Iterator<Element, BitvecIterator>::operator++()
{
    ++index_;
    if(index_ >= 8) { // move to a new byte after 8 bits
        index_ = 0;
        ++byteIt_;
    }

    return *this;
}

template <typename Element, typename BitvecIterator>
bit_vector::Iterator<Element, BitvecIterator>&
    bit_vector::Iterator<Element, BitvecIterator>::operator--()
{
    if(index_ == 0) {
        --byteIt_;
        index_ = 8;
    }

    --index_;

    return *this;
}


template <typename Element, typename BitvecIterator>
typename bit_vector::Iterator<Element, BitvecIterator>::reference
    bit_vector::Iterator<Element, BitvecIterator>::operator*() const
{
    uint8_t frac = pow(2, (7-index_))
    uint8_t n = *byteIt_;
    return floor(n/frac)%2; // return the ith most significant bit of the byte
}

template <typename Element, typename BitvecIterator>
bool  bit_vector::Iterator<Element, BitvecIterator>::operator==(
        const Iterator<Element, BitvecIterator>& rhs) const
{
    return index_ == rhs.index_ && byteIt_ == rhs.byteIt_;
}

template <typename Element, typename BitvecIterator>
bool  bit_vector::Iterator<Element, BitvecIterator>::operator!=(
        const Iterator<Element, BitvecIterator>& rhs) const
{
    return !(*this == rhs);
}