#include <iostream>

int main()
{
   typedef unsigned long long Handle;
   typedef unsigned int uint;
   const uint BITS_IN_BYTE=8;
   const uint SHIFT_LENGTH = sizeof(uint)*BITS_IN_BYTE;

   std::cerr << "Size of long long is: " << sizeof(Handle) << "\n";
   std::cerr << "Size of long is: " << sizeof(uint) << "\n";

   const uint top = 1;
   const uint bottom = 100;
   
   Handle h=0;
   h = h|top;
   std::cerr << "After first or: " << h << "\n";
   h<<=SHIFT_LENGTH;
   std::cerr << "After first shift: " << h << "\n";
   h=h|bottom;
   std::cerr << "After second or: " << h << "\n";


   uint topout = 0;
   uint bottomout = 0;

   bottomout = h;// we implicitly truncate top 32 bits
   std::cerr << "Bottom is: " << bottomout << "\n";

   topout = h>>SHIFT_LENGTH;
   std::cerr << "Top is: " << topout << "\n";
}
