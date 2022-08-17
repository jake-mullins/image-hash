#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<int> ar = {1,2,3,4,5};

    std::vector<int>::iterator ptr;

    std::cout << *ar.begin() << " " << *ar.end() << std::endl;

    for(ptr = ar.begin(); ptr < ar.end(); ++ptr) {
        std::cout << *ptr << std::endl;
    }

    return 0;
}