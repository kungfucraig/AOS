#include <boost/shared_ptr.hpp>
#include <iostream>

class Foo
{
   public:
      ~Foo(){std::cerr << "Destructed.\n";}
};

int main()
{
   {
      boost::shared_ptr<const Foo> f2;
      {
         boost::shared_ptr<Foo> f1(new Foo());
         std::cerr << f1 << ", " << f2 << "\n";
         f2 = f1;
         std::cerr << f1 << ", " << f2 << "\n";
      }
      const Foo* fPtr = f2.get();
      f2.reset();
      std::cerr << "Going out of scope.\n";
   }
   std::cerr << "Done.\n";
}
