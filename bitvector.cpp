/**
 * \file chunkystring.cpp
 *
 * \authors the fantastical falcon_kangaroo
 *
 * \brief Implements the ChunkyString class.
 */

#include "bitvector.hpp"

#include <string>
#include <sstream>
#include <math.h>

bit_vector::bit_vector(std::string seq)
{
    num_bytes_ = ceil(float(seq.length())/8.0);
    bytes = new uint8_t[num_bytes_]
    uint64_t counter = 0;
    uint8_t curr = 0;
    for (uint64_t i=0; i<=seq.length(); ++i)
    {
        curr = curr*2 + std::stoi(str[i]);
        if (i%8==7)
        {
            bytes_[(i-7)/8] = curr;
            curr = 0;
        }
    }
    size_ = str.length();
    if (size_%8 != 0)
    {
        uint64_t pad = 8 - (counter%8);
        curr = curr* pow(2, pad);
        bytes_.[-1] = curr;
    } 
}

uint64_t bit_vector::size()
{
    return size_;
}

uint64_t bit_vector::num_bytes()
{
    return num_bytes_;
}

int64_t rank_support::rank_helper(uint64_t n, uint64_t i, uint64_t b)
{
    uint64_t msb = (n >= pow(2,b-1) ? 1 : 0)
    if (i == 0)
    {
        return msb
    }
    else
    {
        return msb + rank_helper(n-(msb*pow(2,b-1)), i-1, b-1);
    }
}

rank_support::rank_support(bit_vector bits) :
        size_{bits.size()}
{
    uint64_t s_ = ceil(pow(log2(size_), 2)/2);
    uint64_t b_ = ceil(log2(size_)/2);

    loopCount = 0;
    sCount = 0;
    bCount = 0;
    for (auto itr = bits.begin(); itr != bits.end(); ++itr)
    {
        if (loopCount%b_ == 0)
        {
            Rb_.push_back(dCount);
        }
        if (loopCount%s_ == 0)
        {
            Rs_.push_back(sCount);
            dCount = 0; // reset b entries for every s entry
        }
        ++loopCount;
    }

    // Build matrix separately
    Rp_ = new uint64_t*[pow(2,b)];
    for (uint64_t i = 0; i < pow(2,b); ++i)
    {
        Rp_[i] = new uint64_t[b];
        for (uint64_t j = 0; j < b; ++j)
        {
            Rp_[i][j] = rank_helper(i,j,b);
        }
    }
}

uint64_t rank_support::get_bit_i(uint64_t i)
{
    byte = bytes_[floor(float(i)/8.0)];
    pos = i%8;
    return floor(float(byte)/float(pow(2,7-pos))) % 2;
}

uint64_t rank_support::rank1(uint64_t i)
{
    i = 0 // bitstring type
    for (k = i; k < i+b_; ++k)
    {
        i = 2*i + get_bit_i(k)
    }
    j = i%b_ // index within bitstring
    // TODO: Maybe clean this up?
    return Rs_[floor(float(i)/float(s_))] + Rb_[floor(float(i)/float(b_))] + Rp_[i][j];
}

uint64_t rank_support::rank0(uint64_t i)
{
    return i - rank1(i);
}

uint64_t rank_support::overhead()
{
    
}

void rank_support::save(string& fname)
{
    
}

void rank_support::load(string& fname)
{
    
}

// ChunkyString& ChunkyString::operator+=(const ChunkyString& rhs)
// {
//     // If this is empty, use the assignment operator to copy rhs into this
//     if(this->size_ == 0) {
//         *this = rhs;
//         return *this;
//     }

//     // create a copy of rhs
//     ChunkyString newRhs{rhs};

//     // save an iterator to one before the current end of chunks
//     chunklist_iter_t seam = --chunks_.end();

//     // append the two lists
//     chunks_.splice(chunks_.end(), newRhs.chunks_);

//     // check if the two chunks at the seam of the two lists can merge
//     // and if so, merge them
//     tryMergeRight(seam);

//     // update size
//     size_ += rhs.size_;

//     return *this;
// }

// bool ChunkyString::operator==(const ChunkyString& rhs) const
// {
//     if(size_ != rhs.size_) {
//         return false;
//     }

//     for(auto it = begin(), rhsIt = rhs.begin(); it != end(); ++it, ++rhsIt) {
//         if(*it != *rhsIt) {
//             return false;
//         }
//     }
//     return true;
// }

// bool ChunkyString::operator!=(const ChunkyString& rhs) const
// {
//     return !(*this == rhs);
// }

// std::ostream& ChunkyString::print(std::ostream& out) const
// {
//     for(auto it = begin(); it != end(); ++it) {
//         out << *it;
//     }

//     return out;
// }