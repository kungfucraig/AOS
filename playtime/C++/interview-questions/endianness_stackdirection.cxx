#include <iostream>
int main()
{
   int i = 0x1;
   char* ic = reinterpret_cast<char*>(&i);
   int j;
   std::cerr << "Stack grows " << (&j>&i ? "UP" : "DOWN") << "\n";
   std::cerr << (*ic ? "Little" : "Big") << " Endian\n";
}
