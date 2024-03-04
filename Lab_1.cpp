#include <iostream>
#include <cstdlib>
#include <ctime> 

int main() {
    const int size1 = 17;
    const int size2 = 111;

    int Array1[size1];
    int Array2[size2];

    std::cout << "Registers:\n";

    
    srand(time(nullptr));

    std::cout << "Starting array1: ";
    for (int i = 0; i < size1; ++i) {
        Array1[i] = rand() % 2;
        std::cout << Array1[i] << " ";
    }

    std::cout << "\nStarting array2: ";
    for (int i = 0; i < size2; ++i) {
        Array2[i] = rand() % 2;
        std::cout << Array2[i] << " ";
    }

    std::cout << std::endl;

    int index = 0;

    std::cout << "Final array1: ";

     for (int i = 0; i < size1; ++i) {
        int byte = Array1[13] ^ Array2[16];
        std::cout << byte << " ";

        Array1[i] = Array1[i-1];
        Array1[0] = byte;
    }

    std::cout << std::endl;

    return 0;
}
