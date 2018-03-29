#pragma once

template <typename T> class bit;

namespace std
{
template <class T> void swap(bit<T> &&lhs, bit<T> &&rhs) noexcept
{
  bool tmp = rhs;
  rhs = (bool)lhs;
  lhs = tmp;
}
}

#include <cassert>
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class bit_sequence;

template <typename T> T ceil_divide(const T &t1, const T &t2) noexcept
{
  return t1 / t2 + T(t1 % t2 > 1);
}

template <typename T> class bit
{
public:
  bit(int bit_n, T &parent_bitset)
      : m_bit_num(bit_n), m_parent_bitset(&parent_bitset)
  {
  }
  bit(const bit &) = default;
  bit(bit &&) = default;
  bit &operator=(const bit &) = default;
  bit &operator=(bit &&) = default;
  ~bit() = default;

  bit &operator=(bool rhs) noexcept
  {
    const auto bit_mask = ~(((T)1) << m_bit_num);
    *m_parent_bitset &= bit_mask;
    *m_parent_bitset |= (T)rhs << m_bit_num;
    assert((bool)(*this) == rhs);
    return *this;
  }

  operator bool() const noexcept
  {
    const auto bit_mask = (((T)1) << m_bit_num);
    return (bit_mask & (*m_parent_bitset)) != 0;
  }

private:
  int m_bit_num;
  T *m_parent_bitset;
};

struct bit_iterator
    : public std::iterator<std::random_access_iterator_tag, bit<uint64_t>>
{
  bit_iterator(const bit_iterator &) = default;
  bit_iterator(bit_iterator &&) = default;
  bit_iterator &operator=(const bit_iterator &) = default;
  bit_iterator &operator=(bit_iterator &&) = default;

  bit_iterator(int n, bit_sequence &bits) : m_bit_num(n), m_bits(&bits) {}
  bit_iterator operator--() noexcept
  {
    m_bit_num--;
    return *this;
  }
  bit_iterator operator++() noexcept
  {
    m_bit_num++;
    return *this;
  }

  bit_iterator operator++(int)noexcept
  {
    auto tmp = *this;
    m_bit_num++;
    return tmp;
  }
  friend bool operator<(const bit_iterator &lhs,
                        const bit_iterator &rhs) noexcept
  {
    return lhs.m_bit_num < rhs.m_bit_num;
  }
  friend bool operator==(const bit_iterator &lhs,
                         const bit_iterator &rhs) noexcept
  {
    return lhs.m_bit_num == rhs.m_bit_num;
  }
  friend bool operator!=(const bit_iterator &lhs,
                         const bit_iterator &rhs) noexcept
  {
    return !(lhs == rhs);
  }
  friend bit_iterator operator+(const bit_iterator &lhs, uint64_t n) noexcept
  {
    return bit_iterator(lhs.m_bit_num + n, *lhs.m_bits);
  }
  friend bit_iterator operator-(const bit_iterator &lhs, uint64_t n) noexcept
  {
    return bit_iterator(lhs.m_bit_num - n, *lhs.m_bits);
  }

  friend std::ptrdiff_t operator-(const bit_iterator &lhs,
                                  const bit_iterator &rhs) noexcept
  {
    return lhs.m_bit_num - rhs.m_bit_num;
  }

  bit<uint64_t> operator*() noexcept;

  uint64_t m_bit_num;
  bit_sequence *m_bits;
};

class bit_sequence
{
public:
  bit_sequence(int size) : m_size(size), m_bits(size / 64 + 1, false) {}
  bit_sequence(int size, const std::string &start_value) : bit_sequence(size)
  {
    int pos = 0;
    for (auto itr = start_value.cbegin(); itr != start_value.cend(); itr++)
    {
      if (*itr == '0' || *itr == '1')
      {
        (*this)[pos] = (*itr == '1');
        assert(((bool)(*this)[pos] == (*itr == '1')));
        pos++;
      }
      else
      {
        throw std::invalid_argument("Bit can only be '0' or '1'!");
      }
    }
  }
  bit_sequence(const bit_iterator &begin, const bit_iterator &end)
      : bit_sequence(end - begin)
  {
    for (long i = 0; i < end - begin; i++)
    {
      (*this)[i] = (bool)*(begin + i);
    }
  }

  void append(const bit_iterator &begin, const bit_iterator &end) noexcept
  {
    uint64_t orig_size = m_size;
    const auto additional_bits = end - begin;
    assert(additional_bits >= 0);
    m_size += additional_bits;

    while (m_bits.size() < ceil_divide(m_size, (uint64_t)64ull))
    {
      m_bits.push_back((uint64_t)0);
    }

    for (int i = 0; i < additional_bits; i++)
    {
      (*this)[orig_size + i] = (bool)*(begin + i);
      // assert((*this)[orig_size + i] == *(begin + i));
    }
  }

  int n_bits() const noexcept { return m_size; }

  friend bit_sequence operator+(const bit_sequence &lhs,
                                const bit_sequence &rhs) noexcept;

  friend int bits_difference(const bit_sequence &lhs, size_t lhs_offset,
                             const bit_sequence &rhs, size_t rhs_offset,
                             size_t n_bits) noexcept
  {
    int diff = 0;
    for (size_t i = 0; i < n_bits / 64; i++)
    {
       uint64_t diff_bits = lhs.m_bits[lhs_offset + i] ^ rhs.m_bits[rhs_offset + i];
       __popcnt(diff_bits);
    }
  }

  bit<uint64_t> operator[](size_t i) noexcept
  {
    /* if (i >= m_size)
     {
       throw std::out_of_range(std::to_string(i));
     } */
    return bit<uint64_t>(i % 64, m_bits[i / 64]);
  }

  bit_iterator begin() noexcept { return bit_iterator(0, *this); }
  bit_iterator end() noexcept { return bit_iterator(m_size, *this); }

  void print() noexcept
  {
    for (auto b : (*this))
    {
      std::cout << (bool)b;
    }
    std::cout << std::endl;
  }

private:
  uint64_t m_size;
  std::vector<uint64_t> m_bits;
};

bit_sequence operator+(const bit_sequence &lhs,
                       const bit_sequence &rhs) noexcept
{
  bit_sequence res(lhs.n_bits() + 64);
  bool carry = false;
  size_t i = 0;
  const auto size = lhs.m_bits.size();
  for (; i < size; i++)
  {
    unsigned long long sum;
    auto new_carry =
        __builtin_uaddll_overflow(lhs.m_bits[i], rhs.m_bits[i], &sum);
    new_carry |= __builtin_uaddll_overflow(sum, carry, &sum);

    res.m_bits[i] = sum;
    carry = new_carry;
  }
  res.m_bits[i] = (int)carry;
  return res;
}

bit<uint64_t> bit_iterator::operator*() noexcept
{
  return (*m_bits)[m_bit_num];
}
