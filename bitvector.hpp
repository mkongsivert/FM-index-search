/**
 * \file chunkystring.hpp
 *
 * \authors CS 70 given code, with additions by the fantastical falcon_kangaroo
 *
 * \brief Declares the ChunkyString class.
 */

#ifndef BITSTRING_HPP_INCLUDED
#define BITSTRING_HPP_INCLUDED 1

#include <cstddef>
#include <string>
#include <list>
#include <iterator>
#include <iostream>
#include <type_traits>

/**
 * \class BitString
 * \brief Represents a string of bits
 *
 * \details TODO
 *
 * \remarks
 *   TODO
 */
class bit_vector {
    template <typename Element, typename BitvecIterator>
    class Iterator;
public:
    /**
     * \brief Parameterized constructor
     *
     * \note Runs in constant time.
     */
    bit_vector(std::string seq);

    uint64_t size();
    uint64_t num_bytes();

private:
    uint64_t size_;
    uint64_t num_bytes_;
    uint64_t s_;
    uint64_t b_;

    uint8_t* bytes_;

    /**
     * \class rank_support
     * \brief Class / structure that “wraps” the underlying bit-vector.
     */

    // // these functions help us implement the relational operators (see below)
    // template <typename Element, typename ChunklistIterator>
    // friend bool operator==(
    //         const ChunkyString::Iterator<Element, ChunklistIterator>& lhs,
    //         const ChunkyString::Iterator<Element, ChunklistIterator>& rhs);
    
    // template <typename Element, typename ChunklistIterator>
    // friend bool operator!=(
    //         const ChunkyString::Iterator<Element, ChunklistIterator>& lhs,
    //         const ChunkyString::Iterator<Element, ChunklistIterator>& rhs);
};

class rank_support {
public:
        
    /// Returns a singular value.
    /// \note It is undefined behavior to use this for anything but
    ///       assigning from another iterator.
    rank_support(bit_vector bits);

    /**
    * \brief Split a chunk into two different chunks.
    *
    * \param it   An iterator to the character that will become the first
    *              character of the new chunk.
    *
    * \remarks
    *      This will call tryMergeRight() on the newly-inserted chunk.
    */
    uint64_t rank1(uint64_t i);
    uint64_t rank0(uint64_t i);
    uint64_t overhead();
    void save(string& fname);
    void load(string& fname);

private:
    /**
     * \brief
     *      The size of the associated bit vector
     */
    uint64_t size_;

    /**
    * \brief
    *       An array to help compute rank
    */
    uint64_t* Rs_;

    /**
    * \brief
    *       An array to help compute rank
    */
    uint64_t* Rb_;

    /**
    * \brief
    *       A matrix to help compute rank
    */
    uint64_t** Rp_;

    /**
    * \brief A helper function to find rank of numbers
    *
    * \param n   The number to be represented in binary
    *
    * \param i   The index we are counting up to
    *
    * \param b   The number of bits used to represent the number
    */
    uint64_t rank_helper(uint64_t n, uint64_t i, uint64_t b);

    uint64_t** rank_matrix(uint64_t b);

};

/**
 * \brief Print operator.
 * \remarks
 *   Like the ones above, it's just a wrapper around a member function
 *   that does the actual work, and we don't mind if people know that.
 *
inline std::ostream& operator<<(std::ostream& out, const ChunkyString& text)
{
    return text.print(out);
}*/

#endif // BITSTRING_HPP_INCLUDED