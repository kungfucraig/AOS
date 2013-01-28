
#include <iostream>

template<typename T1, typename T2>
void foo(T1 const& t1, T2 const& t2)
{
   std::cerr << "In foo<T1, T2>(" << t1 << ", " << t2 << ")\n";
}

// This is illegal.
// template<typename T2>
// void foo<int, T2>(int t1, T2 const& t2)
// {
//    std::cerr << "In foo<int, T2>(" << t1 << ", " << t2 << ")\n";
// }

template<typename T1, typename T2>
struct Bar
{
      void operator()(T1 const& t1, T2 const& t2)
      {
         std::cerr << "In Bar<T1, T2>(" << t1 << ", " << t2 << ")\n";
      }
};


template<typename T2>
struct Bar<int, T2>
{
      void operator()(int t1, T2 const& t2)
      {
         std::cerr << "In Bar<int, T2>(" << t1 << ", " << t2 << ")\n";
      }
};


template<typename T1, typename T2>
void bar(T1 const& t1, T2 const& t2)
{
   Bar<T1, T2> b;
   b(t1, t2);
}


int main()
{
   foo(1,"str");
   bar(1,"str");
   bar(1.0,"str");

   // Output:
   //    In foo<T1, T2>(1, str)
   //    In Bar<int, T2>(1, str)
   //    In Bar<T1, T2>(1, str)
}

