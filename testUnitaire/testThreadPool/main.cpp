#include "ThreadPool.hpp"

int	main(void)
{
  FourCheese::ThreadPool	pool(5);

  pool.launchTask("Yop");
  pool.launchTask("Yop");
  pool.launchTask("Yop");
  return (0);
}
