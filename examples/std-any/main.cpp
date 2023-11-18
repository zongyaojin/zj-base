#include "ZjLogMacroExtensions.hpp"
#include <any>
#include "eigen3/Eigen/Dense"
#include <iostream>

void func(const std::any input)
{
    try {
        auto d = std::any_cast<double>(input);
        std::cout << d << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cout << "e: " << e.what() << std::endl;
        std::cout << input.type().name() << std::endl;
        std::cout << input.has_value() << std::endl;
    }
}


void func2(std::any input)
{
    try {
        double* d = std::any_cast<double*>(input);
        std::cout << *d << std::endl;

        *d = 3.14; // Modifying the referenced std::any
    } catch (const std::bad_any_cast& e) {
        std::cout << "e: " << e.what() << std::endl;
        std::cout << input.type().name() << std::endl;
        std::cout << input.has_value() << std::endl;
    }
}


int main()
{
    // std::string a = "2";
    // int a = 123;
    double a = 1.23;
    func(a);

    func2(&a);

    std::cout << a << std::endl;
    return 0;
}