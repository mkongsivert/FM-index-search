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
    no_bytes = ceil(float(seq.length())/8.0);
    bytes = new uint8_t[no_bytes]
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

std::vector<std::vector<uint64_t>> rank_support::rank_matrix(uint64_t b)
{
    std::vector<std::vector<uint64_t>> mat;
    for (uint64_t i = 0; i <= pow(2,b); ++i)
    {
        std::vector<uint64_t> row;
        for (uint64_t j = 0; j <= b; ++j)
        {
            row.push_back(rank_helper(i,j,b));
        }
        mat.push_back(row);
    }
    return mat;
}

rank_support::rank_support(bit_vector bits) :
        size_{bits.size()}
{
    uint64_t s = ceil(pow(log2(size_), 2)/2);
    uint64_t d = ceil(log2(size_)/2);

    loopCount = 0;
    sCount = 0;
    dCount = 0;
    for (auto itr = bits.begin(); itr != bits.end(); ++itr)
    {
        if (loopCount%d == 0)
        {
            Rd_.push_back(dCount);
        }
        if (loopCount%s == 0)
        {
            Rs_.push_back(sCount);
            dCount = 0; // reset d entries for every s entry
        }
        ++loopCount;
    }
}

uint64_t rank_support::rank1(uint64_t i)
{
    
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