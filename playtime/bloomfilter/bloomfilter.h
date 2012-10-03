// Copyright (c) 2012 Craig Wright (kungfucraig@gmail.com)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
// Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <boost/dynamic_bitset.hpp>

/*!
  This class implements a templatized Bloom Filter.
  @see http://en.wikipedia.org/wiki/Bloom_filter

  @param T is the input type the Bloom Filter operates on.

  @param HashFunction is a hash function that returns a vector of independent hashes of the
  input, each of which is then used to address the bits in the Bloom Filter. The hash function
  must operate on T.
 */
template<typename T, typename HashFunction>
class BloomFilter
{
   public:

      BloomFilter(unsigned int numbits, HashFunction hf); 

      //! Destructor
      ~BloomFilter() = default;

      //! Insert an element into the set.
      void insert(T const& t);

      //! Determine if the set contains the given element.
      bool contains(T const& t);

      //! Used for comparing performance with std::set
      bool find(T const& t){return this->contains(t);}

   private:
      const unsigned int numbits_;
      HashFunction hf_;
      boost::dynamic_bitset<> bits_;

      BloomFilter(BloomFilter const&) = delete;
      BloomFilter& operator=(BloomFilter const&) = delete;
};

template<typename T, typename HashFunction>
BloomFilter<T, HashFunction>::BloomFilter(unsigned int numbits, HashFunction hf) :
   numbits_(numbits), bits_(numbits), hf_(hf)
{
}

template<typename T, typename HashFunction>
void BloomFilter<T, HashFunction>::insert(T const& t)
{
   std::vector<uint64_t> hashValues = hf_(t);
   std::for_each(hashValues.begin(), hashValues.end(),
                 [this](uint64_t n){this->bits_[n%this->numbits_]=1;});
}

template<typename T, typename HashFunction>
bool BloomFilter<T, HashFunction>::contains(T const& t)
{
   std::vector<uint64_t> hashValues = hf_(t);
   auto iter = hashValues.begin();
   while ( iter != hashValues.end() && this->bits_[*iter % this->numbits_] ) ++iter; 
   return iter == hashValues.end();
}
