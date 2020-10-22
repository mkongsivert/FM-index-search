/**
 * \file bitvector.cpp
 *
 * \authors Mackenzie Kong-Sivert
 *
 * \brief Implements the bit_vector, rank_support, and select_support classes.
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

    // Add padding if necessary
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

std::string bit_vector::dec_to_str(uint8_t n)
{
    if (n <= 1)
    {
        return std::to_string(n);
    }
    else
    {
        return dec_to_str(n/2) + std::to_string(n%2);
    }
}

std::string bit_vector::print()
{
    std::string bitstr = '';
    for (uint64_t i = 0; i < num_bytes_; ++i)
    {
        bitstr += dec_to_str(bytes_[i]);
    }
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

std::string rank_support::print()
{
    std::string output = "Bitstring: " + bits_.print()
    output += "\nSize: " + std::to_string(bits_.size()) + "\n\n";
    output += "\nR_s: " + to_string(*Rs_) + "\nR_b: " + to_string(*R_b)
    output += "s: " + to_string(s_) + "\nb: " + to_string(b_) + "\n\n";
    output += "Overhead:" + to_string(overhead());
    return output;
}

uint64_t rank_support::overhead()
{
    // TODO: write
    return 0;
}

void rank_support::save(string& fname)
{
    ofstream myfile;
    myfile.open (fname);
    myfile << print();
    myfile.close();
}

void rank_support::load(string& fname)
{
    // TODO: write
}

uint64_t rank_support::size()
{
    return bits_.size();
}

uint64_t select_support::select1_help(uint64_t i, uint64_t n, uint64_t m)
{
    mid = (n+m)/2
    midRank = r_supp_.rank1(mid)
    
    if (midRank == i)
    {
        return mid;
    }
    else if ((m-n) < 1)
    {
        cout << "ERROR: desired index not found"
        return 0;
    }
    else if (midRank < i)
    {
        return select1_help(i, n, mid);
    }
    else
    {
        return select1_help(i, mid, m);
    }
}

uint64_t select_support::select1(uint64_t i)
{
    return select1_help(i, 0, r_supp_.size());
}

uint64_t select_support::select0_help(uint64_t i, uint64_t n, uint64_t m)
{
    mid = (n+m)/2
    midRank = r_supp_.rank0(mid)
    
    if (midRank == i)
    {
        return mid;
    }
    else if ((m-n) < 1)
    {
        cout << "ERROR: desired index not found"
        return 0;
    }
    else if (midRank < i)
    {
        return select0_help(i, n, mid);
    }
    else
    {
        return select0_help(i, mid, m);
    }
}

uint64_t select_support::select0(uint64_t i)
{
    return select0_help(i, 0, r_supp_.size());
}

uint64_t select_support::overhead()
{
    // TODO: write
}

void select_support::save(string& fname)
{
    // TODO: write
}

void select_support::load(string& fname)
{
    // TODO: write
}

// bool bit_vector::operator==(const bit_vector& rhs) const
// {
//   
// }

// bool bit_vector::operator!=(const bit_vector& rhs) const
// {
//     return !(*this == rhs);
// }

// std::ostream& bit_vector::print(std::ostream& out) const
// {
//     for(auto it = begin(); it != end(); ++it) {
//         out << *it;
//     }
//     return out;
// }