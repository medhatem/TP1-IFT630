
#include <iostream>
#include "philo.h"
#include <thread>
int main()
{

   Philo pp(5);
   //std::thread first(pp.take,0);
   
   pp.take(0);
   pp.take(1);
   pp.take(2);
   pp.drop(0);
   pp.take(3);
   pp.drop(2);

    std::cout << "Hello World!\n";


}



