#include <iostream>
#include "ThreadPool.hpp"

int	main(void)
{
  FourCheese::ThreadPool	pool(5);
  std::string			lol;
  int				i = 0;

  pool.launchTask("Encore du travaille");  
  pool.launchTask("Encore du travaille");
  pool.launchTask("Encore du travaille");
  while (i < 3)
    {
      while (!pool.getResult(lol));
      std::cout << lol << std::endl;
      i++;
    }
  return (0);
}
