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
    uint64_t counter = 0;
    uint8_t curr = 0;
    for (std::string::iterator itr=seq.begin(); itr!=seq.end(); ++itr)
    {
        curr = curr*2 + std::stoi(*itr);
        if (counter%8==7)
        {
            bytes_.push_back(curr);
            curr = 0;
        }
        ++counter;
    }
    size_ = counter;
    if (counter%8 != 0)
    {
        uint64_t pad = 8 - (counter%8);
        curr = curr* pow(2, pad);
        bytes_.push_back(curr);
    } 
}

uint64_t bit_vector::size()
{
    return size_;
}

rank_support::rank_support(bit_vector bits) :
        size_{bits.size()}
{
    
}

ChunkyString::iterator ChunkyString::begin()
{
    return iterator(0, chunks_.begin());
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