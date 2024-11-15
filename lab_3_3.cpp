#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

int main() {
    std::string one = "Gibberish";
    char two[] = "Gibberish";

    std::cout << "one: " << one << std::endl;
    std::cout << "two: " << two << std::endl;

    std::cout << "\nModify both strings\n\n";

    one[4] = '\0';
    two[4] = '\0';

    std::cout << "one: " << one << std::endl;
    std::cout << "Length of one: " << one.size() << std::endl;
    std::cout << "Sizeof(one): " << sizeof(one) << std::endl << std::endl;

    std::cout << "two: " << two << std::endl;
    std::cout << "Length of two: " << strlen(two) << std::endl;
    std::cout << "Sizeof(two): " << sizeof(two) << std::endl;

    return EXIT_SUCCESS;
}
