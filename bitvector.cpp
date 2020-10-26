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
#include <fstream>
#include <math.h>

bit_vector::bit_vector() :
        size_{0}, num_bytes_{0}
{
    bytes_ = NULL;
}

bit_vector::bit_vector(std::string seq)
{
    num_bytes_ = ceil(float(seq.length())/8.0);
    bytes_ = new uint8_t[num_bytes_];
    uint64_t counter = 0;
    uint8_t curr = 0;
    for (uint64_t i=0; i<=seq.length(); ++i)
    {
        curr = curr*2 + int(seq[i]);
        if (i%8==7)
        {
            bytes_[(i-7)/8] = curr;
            curr = 0;
        }
    }
    size_ = seq.length();

    // Add padding if necessary
    if (size_%8 != 0)
    {
        uint64_t pad = 8 - (counter%8);
        curr = curr* pow(2, pad);
        bytes_[num_bytes_-1] = curr;
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

void bit_vector::print()
{
    std::string bitstr;
    for (uint64_t i = 0; i < num_bytes_; ++i)
    {
        bitstr += dec_to_str(bytes_[i]);
    }
    std::cout << "Bitstring: " << bitstr << std::endl;
    std::cout << "Size: " << std::to_string(size_) << std::endl;
}

std::string rank_support::dec_to_str(uint8_t n)
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

uint64_t rank_support::rank_helper(uint64_t n, uint64_t i, uint64_t b)
{
    uint64_t msb = (n >= pow(2,b-1) ? 1 : 0);
    if (i == 0)
    {
        return msb;
    }
    else
    {
        return msb + rank_helper(n-(msb*pow(2,b-1)), i-1, b-1);
    }
}

rank_support::rank_support(bit_vector bits) :
        bits_{bits}, size_{bits.size()}
{
    s_ = pow(log2(size_), 2)/2;
    b_ = log2(size_)/2;

    uint64_t sCount = 0;
    uint64_t bCount = 0;
    uint64_t *sArray = new uint64_t[size_/s_];
    uint64_t *bArray = new uint64_t[size_/b_];
    for (uint64_t i = 0; i < bits.num_bytes(); ++i)
    {
        std::string this_byte = dec_to_str(bits.bytes_[i]);
        for (uint64_t j = 0; j < 8; ++j)
        {
            uint64_t index = 8*i+j;
            if (index%b_ == 0)
            {
                bArray[index/b_] = bCount;
            }
            if (index%s_ == 0)
            {
                sArray[index/s_] = sCount;
                bCount = 0; // reset b entries for every s entry
            }
            sCount += this_byte[j]=='1' ? 1 : 0;
            bCount += this_byte[j]=='1' ? 1 : 0;
        }
    }
    Rs_ = sArray;
    Rb_ = bArray;

    // Build matrix separately
    Rp_ = new uint64_t*[int(pow(2,b_))];
    for (uint64_t i = 0; i < pow(2,b_); ++i)
    {
        Rp_[i] = new uint64_t[b_];
        for (uint64_t j = 0; j < b_; ++j)
        {
            Rp_[i][j] = rank_helper(i,j,b_);
        }
    }
}

uint64_t rank_support::get_bit_i(uint64_t i)
{
    uint8_t byte = bits_.bytes_[int(float(i)/8.0)];
    uint8_t pos = i%8;
    return int(float(byte)/pow(2,7-pos)) % 2;
}

uint64_t rank_support::rank1(uint64_t i)
{
    uint8_t n = 0; // bitstring type
    uint64_t j = i%b_; // index within bitstring
    for (uint64_t k = i-j; k < i-j+b_; ++k)
    {
        n = 2*n + get_bit_i(k);
    }
    // TODO: Maybe clean this up?
    return *(Rs_+(i/s_)) + *(Rb_+(i/b_)) + Rp_[n][j];
}

uint64_t rank_support::rank0(uint64_t i)
{
    return i - rank1(i);
}

void rank_support::print()
{
    bits_.print();

    std::cout << "\nR_p:";
    for (uint64_t a = 0; a < pow(2,b_); ++a)
    {
        for (uint64_t b = 0; b < b_; ++b)
        {
            std::cout << Rp_[a][b];
            std::cout << (b < b_-1 ? ", " : "");
        }
        std::cout << std::endl;
        std::cout << (a < pow(2,b_)-1 ? "    " : "");
    }

    std::cout << "R_s: ";

    for (uint64_t i = 0; i <= (size_/s_); ++i)
    {
        std::cout << *(Rs_+i) << ", ";
    }

    std::cout << "\nR_b: ";
    for (uint64_t j = 0; j <= (size_/b_); ++j)
    {
        std::cout << *(Rb_+j) << ", ";
    }
    std::cout << "\ns: " << s_ << "\nb: " << b_ << std::endl;
    std::cout << "\nOverhead:" + std::to_string(overhead()) << std::endl;
}

uint64_t rank_support::overhead()
{
    return sizeof(this)*8; // sizeof returns size in bytes
}

void rank_support::save(std::string& fname)
{
    std::ofstream myfile(fname, std::ofstream::out);
    //myfile << print();
    myfile.close();
}

void rank_support::load(std::string& fname)
{
    // TODO: write
}

uint64_t rank_support::size()
{
    return bits_.size();
}

select_support::select_support(rank_support r_supp) :
    r_supp_{r_supp}
{
    // nothing to do here
}

uint64_t select_support::select1_help(uint64_t i, uint64_t n, uint64_t m)
{
    uint64_t mid = (n+m)/2;
    uint64_t midRank = r_supp_.rank1(mid);
    
    if (midRank == i)
    {
        return mid;
    }
    else if ((m-n) < 1)
    {
        std::cout << "ERROR: desired index not found";
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
    uint64_t mid = (n+m)/2;
    uint64_t midRank = r_supp_.rank0(mid);
    
    if (midRank == i)
    {
        return mid;
    }
    else if ((m-n) < 1)
    {
        std::cout << "ERROR: desired index not found";
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
    return sizeof(this)*8;
}

void select_support::print()
{
    r_supp_.print();
}

void select_support::save(std::string& fname)
{
    std::ofstream myfile;
    myfile.open (fname);
    //myfile << print();
    myfile.close();
}

void select_support::load(std::string& fname)
{
    // TODO: write
}

int main()
{
    bit_vector testVec = bit_vector("11101011001101010001110011001101011001101101001111011111011001010010101000010010");
    testVec.print();
    
    rank_support testRank = rank_support(testVec);
    testRank.print();
    std::cout << "Rank for i=30: " << testRank.rank1(30) << std::endl;
    return 0;
}
