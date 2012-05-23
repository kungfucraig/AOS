
// Local
#include "bloomfilter.h"
#include "multihash.h"

// STL
#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <ctime>

// AOS Utility
#include <timer.h>

template<class Container, class Generator>
void insert(Container& cont, unsigned int numvalues, Generator& gen)
{
   for ( unsigned int i = 0; i < numvalues; ++i )
   {
      cont.insert(gen());
   }
}

template<class Container, class Generator>
void find(Container& cont, unsigned int numvalues, Generator gen)
{
   for ( unsigned int i = 0; i < numvalues; ++i )
   {
      cont.find(gen());
   }
}

// void performanceHelper(BloomFilter<int, MultiHash>& bf,
//                        std::set<int>& theset,
//                        {
// }

void performanceTest(unsigned int numvalues, unsigned int numbits, MultiHash mh)
{

   {
      BloomFilter<int, MultiHash> bf(numbits, mh);
      std::set<int> theset;
      {
         std::mt19937 bfgen;
         std::mt19937 setgen;
         clock_t bftime = timeFunction(insert<BloomFilter<int, MultiHash>, std::mt19937>, bf, numvalues, bfgen);
         clock_t settime = timeFunction(insert<std::set<int>, std::mt19937>, theset, numvalues, setgen);
         std::cerr << "Random Insert - BF Time: " << bftime << " Set Time: " << settime << "\n";
      }

      {
         std::mt19937 bfgen;
         std::mt19937 setgen;
         clock_t bftime = timeFunction(find<BloomFilter<int, MultiHash>, std::mt19937>, bf, 2*numvalues, bfgen);
         clock_t settime = timeFunction(find<std::set<int>, std::mt19937>, theset, 2*numvalues, setgen);
         std::cerr << "Same Random Find - BF Time: " << bftime << " Set Time: " << settime << "\n";
      }
   }


   {
      BloomFilter<int, MultiHash> bf(numbits, mh);
      std::set<int> theset;
      {
         unsigned int i = 0;
         auto lf = [&i](){return ++i;};
         clock_t bftime = timeFunction(insert<BloomFilter<int, MultiHash>, decltype(lf)>,
                                       bf,
                                       numvalues,
                                       lf);

         i = 0;
         clock_t settime = timeFunction(insert<std::set<int>, decltype(lf)>,
                                        theset,
                                        numvalues,
                                        lf);

         std::cerr << "Sequential Insert - BF Time: " << bftime << " Set Time: " << settime << "\n";
      }

      {
         unsigned int i = 0;
         auto lf = [&i](){return ++i;};
         clock_t bftime = timeFunction(find<BloomFilter<int, MultiHash>, decltype(lf)>,
                                       bf,
                                       numvalues,
                                       lf);

         i = 0;
         clock_t settime = timeFunction(find<std::set<int>, decltype(lf)>,
                                        theset,
                                        numvalues,
                                        lf);

         std::cerr << "Sequential Find - BF Time: " << bftime << " Set Time: " << settime << "\n";
      }
    }
}

void probTest(unsigned int numvalues, unsigned int numbits, MultiHash mh)
{
   BloomFilter<int, MultiHash> bf(numbits, mh);
   std::set<int> theset;
   std::mt19937 gen1;
   std::mt19937 gen2;
   insert(bf, numvalues, gen1);
   insert(theset, numvalues, gen2);


   std::mt19937 gen3;
   gen3.seed(time(0));
   const int totalChecked = 10000000;
   int numfalsepos = 0;
   int numfound = 0;
   int numnotfound = 0;

   for ( int i = 0; i < totalChecked; ++i )
   {
      int n = gen3();
      bool setfound = theset.find(n) != theset.end();
      bool bffound = bf.find(n);

      if ( setfound && bffound  ) ++numfound;
      else if ( setfound && !bffound ) std::cerr << "BADNESS.\n";
      else if ( !setfound && bffound ) ++numfalsepos;
      else ++numnotfound;
   }

   std::cerr << "PROB 1\n";
   std::cerr << "Found: " << numfound << ", Not Found: " << numnotfound << ", False Pos: " << numfalsepos << "\n";
   std::cerr << "False Pos Ratio: " << double(numfalsepos)/double(numnotfound) << "\n";
}

void probTest2(unsigned int numvalues, unsigned int numbits, MultiHash mh)
{
   BloomFilter<int, MultiHash> bf(numbits, mh);
   std::set<int> theset;

   int i = 0;
   auto gen = [&i](){return i++;};
   insert(bf, numvalues, gen);
   i = 0;
   insert(theset, numvalues, gen);

   const int totalChecked = 10000000;
   int numfalsepos = 0;
   int numfound = 0;
   int numnotfound = 0;

   // All should be negative.
   for ( int i = numbits; i < totalChecked+numbits; ++i )
   {
      int n = i;
      bool setfound = theset.find(n) != theset.end();
      bool bffound = bf.find(n);

      if ( setfound && bffound  ) ++numfound;
      else if ( setfound && !bffound ) std::cerr << "BADNESS.\n";
      else if ( !setfound && bffound ) ++numfalsepos;
      else ++numnotfound;
   }

   std::cerr << "PROB 2\n";
   std::cerr << "Found: " << numfound << ", Not Found: " << numnotfound << ", False Pos: " << numfalsepos << "\n";
   std::cerr << "False Pos Ratio: " << double(numfalsepos)/double(numnotfound) << "\n";
}

 
int main()
{
   std::mt19937 seedGen;
   MultiHash mh(10, seedGen);

   const unsigned int numvalues = 1000000;
   const unsigned int numbits = 9585058; // -(numvalues * ln (probability of false positive) / ln(2)^2)
   // using 1% for prob. of false positive.

   performanceTest(numvalues, numbits, mh);
   probTest(numvalues, numbits, mh);
   probTest2(numvalues, numbits, mh);
   


}

