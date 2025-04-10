#include <iomanip>
#include <iostream>
#include "../Random.h"
using namespace std;

int main()
{
    // create rand object using default distribution
    Random rand;

    // create rand object using defined distribution bounds
    Random customRand(1, 100);

    // Generate a number using a generator with system clock seed
    int x = rand();

    // Generate a number using the default debug seed
    int y = rand(true);

    // Change the seed of the debug generator
    Random::ChangeDebugSeed(2);

    // Change the bounds of number generation
    customRand.ChangeBounds(1, 6);

    
    // -------------------- showcase of functions --------------------
    cout << setfill('.');

    // Using system clock seed (at start of program)
    cout << left << setw(35) << "Seed based on system clock: " << " ";
    for (int i = 0; i < 10; i++)
    {
        std::cout << rand() << " ";
    }
    cout << "\n\n";

    // Changing bounds of numbers that can be generated
    rand.ChangeBounds(1, 6);
    cout << left << setw(35) << "Using different bounds (1-6): " << " ";
    for (int i = 0; i < 10; i++)
    {
        cout << rand() << " ";
    }
    cout << "\n\n";

    // Using debug seed, numbers generated will always be the same
    cout << left << setw(35) << "Default debug seed of 0: " << " ";
    for (int i = 0; i < 10; i++)
    {
        cout << rand(true) << " ";
    }
    cout << "\n\n";

    // debug number generator w/ different seed
    Random::ChangeDebugSeed(1000);
    cout << left << setw(35) << "Debug seed of 1000: " << " ";
    for (int i = 0; i < 10; i++)
    {
        cout << rand(true) << " ";
    }
    cout << "\n\n";

    return 0;
}