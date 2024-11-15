#include <cstdio>
#include <cstdlib>
#include <iostream>

int main() {
    int a = 060;
    int b = 60;
    int c = 0x60;

    printf("C style\n");
    printf("symbol\toctal\tdecimal\thex\n");
    printf("%6c\t%5o\t%7d\t%3x\n", a, a, a, a);
    printf("%6c\t%5o\t%+7d\t%3x\n", b, b, b, b);
    printf("%-6c\t%-5o\t%-7d\t%-3x\n", c, c, c, c);

    std::cout << "\nC++ style" << std::endl;
    std::cout << "symbol\toctal\tdecimal\thex" << std::endl;
    std::cout.width(6);
    std::cout << (char)a;
    std::cout.width(7);
    std::cout << std::oct << a;
    std::cout.width(10);
    std::cout << std::dec << a;
    std::cout.width(4);
    std::cout << std::hex << a << std::endl;

    std::cout << std::showpos;
    std::cout.width(6);
    std::cout << (char)b;
    std::cout.width(7);
    std::cout << std::oct << b;
    std::cout.width(10);
    std::cout << std::dec << b;
    std::cout.width(4);
    std::cout << std::hex << b << std::endl;

    std::cout << std::noshowpos << std::left;
    std::cout.width(8);
    std::cout << (char)c;
    std::cout.width(8);
    std::cout << std::oct << c;
    std::cout.width(8);
    std::cout << std::dec << c;
    std::cout.width(3);
    std::cout << std::hex << c << std::endl;

    return EXIT_SUCCESS;
}
