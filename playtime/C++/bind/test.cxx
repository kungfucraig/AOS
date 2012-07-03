#include <string>
#include <iostream>

#include <boost/bind.hpp>

enum Status{SUCCESS, FAILURE};


class Bar
{
   public:
      Status doit(int source, std::string const& key, double& output)
      {
         output = source + key.length();
         return SUCCESS;
      }
};
static Bar b;

template<class F>
Status foo(int source,
           std::string const& key,
           F f)
{
   f(b);
   return SUCCESS;
}

int main()
{
   int source = 10;
   std::string const& key = "xyz";
   double output;

   b.doit(source, key, output);
   std::cerr << "First run: " << output << "\n";

   output = 0;
   Status s = foo(source, key, boost::bind(&Bar::doit, _1, source, key, output));
   std::cerr << "Second run: " << output << "\n";



}
