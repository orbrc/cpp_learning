#include <iostream>

#include "algo/ArraySearch.h"

int main() {
    const int first[] = {1, 2, 4, 6, 7, 8, 9, 12, 16};
    const int second[] = {1, 2, 4, 6, 7, 8, 9, 12, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

    std::cout << search::binarySearch(first, std::size(first), 9) << std::endl;
    std::cout << search::binarySearch(first, std::size(first), 3) << std::endl;
    std::cout << search::binarySearch(first, std::size(first), 4) << std::endl;
    std::cout << search::binarySearch(first, std::size(first), 7) << std::endl;
    std::cout << search::binarySearch(first, std::size(first), 16) << std::endl;

    std::cout << search::binarySearch(second, std::size(second), 1) << std::endl;
    std::cout << search::binarySearch(second, std::size(second), 256) << std::endl;
    std::cout << search::binarySearch(second, std::size(second), 12) << std::endl;
    std::cout << search::binarySearch(second, std::size(second), 56) << std::endl;
    std::cout << search::binarySearch(second, std::size(second), 1) << std::endl;

    std::cout << search::linearSearch(first, std::size(first), 3) << std::endl;
    std::cout << search::linearSearch(first, std::size(first), 4) << std::endl;
    std::cout << search::linearSearch(first, std::size(first), 7) << std::endl;
    std::cout << search::linearSearch(first, std::size(first), 16) << std::endl;
    std::cout << search::linearSearch(second, std::size(second), 1) << std::endl;

    return 0;
}
