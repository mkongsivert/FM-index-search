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
    // Forward declaration of private class.

public:
    /**
     * \brief Parameterized constructor
     *
     * \note Runs in constant time.
     */
    bit_vector(std::string seq);
    
    uint64_t size();

private:
    uint64_t size_;

    std::vector<uint8_t> bytes_;

    /**
     * \class rank_support
     * \brief Class / structure that “wraps” the underlying bit-vector.
     */
    //template <typename Element, typename ChunklistIterator>
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
    friend class bit_vector;

    /**
     * \brief
     *      The size of the associated bit vector
     */
    uint64_t size_;

    /**
    * \brief
    *       An array to help compute rank
    */
    std::vector<uint8_t> Rs_;

    /**
    * \brief
    *       An array to help compute rank
    */
    std::vector<uint8_t> Rb_;

    /**
    * \brief
    *       An array to help compute rank
    */
    std::vector<uint8_t> Rp_;

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