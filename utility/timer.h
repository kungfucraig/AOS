#include <ctime>

//! Return the number of clock ticks a function takes to execute.
//! \see http://www.cplusplus.com/reference/clibrary/ctime/clock/
template<typename F, typename ...Args>
clock_t timeFunction(F f, Args&& ...args)
{
   auto begin = clock();
   f(std::forward<Args>(args)...);
   auto end = clock();
   return end-begin;
}
