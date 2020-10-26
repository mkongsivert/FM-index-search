/**
 * \file bitvector.hpp
 *
 * \authors Mackenzie Kong-Sivert
 *
 * \brief Declares the bit_vector, rank_support, and select_support classes.
 */

#ifndef BITSTRING_HPP_INCLUDED
#define BITSTRING_HPP_INCLUDED 1

#include <cstddef>
#include <string>
#include <list>
#include <iterator>
#include <iostream>
#include <fstream>
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
public:
    /**
     * \brief Default constructor
     *
     * \note Will not be used; only exists for compilation
     */
    bit_vector();
    /**
     * \brief Parameterized constructor
     *
     * \note
     */
    bit_vector(std::string seq);

    uint64_t size();
    uint64_t num_bytes();
    std::string dec_to_str(uint8_t n);
    void print();

    uint8_t* bytes_;

private:
    uint64_t size_;
    uint64_t num_bytes_;

    /**
     * \class rank_support
     * \brief Class / structure that “wraps” the underlying bit-vector.
     */
};

class rank_support {
public:
        
    std::string dec_to_str(uint8_t n);
    rank_support(bit_vector bits);

    /**
    * \brief Find the number of 1s in a given bit_vector object from indices
    *           0 to i (inclusive)
    *
    * \param i   The index for which we want to find the rank
    *
    * \remarks rank1(i) + rank(0) = i
    */
    uint64_t rank1(uint64_t i);

    /**
    * \brief Find the number of 0s in a given bit_vector object from indices
    *           0 to i (inclusive)
    *
    * \param i   The index for which we want to find the rank
    *
    * \remarks rank1(i) + rank(0) = i
    */
    uint64_t rank0(uint64_t i);
    uint64_t overhead();
    void print();
    void save(std::string& fname);
    void load(std::string& fname);

    uint64_t size();

private:
    /**
     * \brief
     *      The associated bit vector
     */
    bit_vector bits_;
    uint64_t size_;
    uint64_t s_;
    uint64_t s_arr_len_;
    uint64_t b_;
    uint64_t b_arr_len_;

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

    uint64_t get_bit_i(uint64_t i);
};

class select_support {
public:
    select_support(rank_support r_supp);

    uint64_t select1_help(uint64_t i, uint64_t n, uint64_t m);
    uint64_t select0_help(uint64_t i, uint64_t n, uint64_t m);

    /**
    * \brief Given i, find the ith 1 in a given bitstring
    *
    * \param i   The ordinal number of 1s we want to find
    *
    * \remarks This is essentially implemented using binary search.
    */
    uint64_t select1(uint64_t i);

    /**
    * \brief Given i, find the ith 0 in a given bitstring
    *
    * \param i   The ordinal number of 0s we want to find
    *
    * \remarks This is essentially implemented using binary search.
    */
    uint64_t select0(uint64_t i);
    uint64_t overhead();
    void print();
    void save(std::string& fname);
    void load(std::string& fname);
private:
    rank_support r_supp_;
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