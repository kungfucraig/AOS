#include <iostream>

struct ReadWrite
{
      static void echo(){std::cerr << "ReadWrite.\n";}
};

struct ReadOnly
{
      static void echo(){std::cerr << "ReadOnly.\n";}
};

template<class ReturnType, typename AccessPolicy>
class Functor
{
      void getMore(ReturnType& x, ReturnType& y){get(x);get(y);}
};

template<typename AccessPolicy>
class Functor<double, AccessPolicy>
{
   public:
      void get(double& x){std::cerr << "Getting double.\n";  AccessPolicy::echo(); x=1.23;}
};

template<typename AccessPolicy>
class Functor<int, AccessPolicy>
{
   public:
      void get(int& x){std::cerr << "Getting int.\n"; AccessPolicy::echo(); x=123;}
};


int main()
{
   Functor<double, ReadOnly> f1;
   Functor<double, ReadWrite> f2;
   Functor<int, ReadOnly> f3;
   Functor<int, ReadWrite> f4;

   double x = 0;
   f1.get(x); std::cerr << x << "\n";
   f2.get(x); std::cerr << x << "\n";
   //f1.getMore(0.0, 1.0); does not compile

   int y;
   f3.get(y); std::cerr << y << "\n";
   f4.get(y); std::cerr << y << "\n";
   
}
