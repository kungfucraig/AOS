#include "spooky.h"
#include <vector>
#include <boost/bind.hpp>

class MultiHash
{
   public:

      //! Construct a hash functor capable of returning k independent hash values
      //! for a given input.
      template<class SeedGenerator>
      MultiHash(unsigned int k, SeedGenerator gen)  
      {
         seeds_.reserve(k);
         std::generate_n(std::back_inserter(seeds_), k, gen);
      }

      //! Hash the input.
      std::vector<uint64_t> operator()(uint64_t input) const
      {
         std::vector<uint64_t> out;
         out.reserve(seeds_.size());
         // See http://www.burtleburtle.net/bob/hash/spooky.html
         auto f = boost::bind(SpookyHash::Hash64, &input, sizeof(uint64_t), _1);
         std::transform(seeds_.begin(), seeds_.end(), std::back_inserter(out), f);
         return out;
      }
   private:
      std::vector<uint64_t> seeds_;
};


