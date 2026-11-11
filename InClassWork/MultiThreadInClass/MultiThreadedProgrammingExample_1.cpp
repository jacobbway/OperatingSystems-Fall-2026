#include <iostream>
#include <thread>

void greeting(void)
{
    std::cout << "Hello, WORLD\n";
    std::cout << "This is thread: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    std::thread babysFirstThread(greeting);

    babysFirstThread.join();

    std::cout << "By Main Thread: " << std::this_thread::get_id() << std::endl;
    return 0;    
}


// g++ yourprogram.cpp -o yourprogramexe -fopenmp - lpthread
// g++ yourprogram.cpp -o yourprogramexe -lpthread