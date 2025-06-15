#include <iostream>
#include "BigReal.h" // Include the header file with the BigReal class
#include "Bigreal.cpp"
int main() {
    BigReal num1("632145269.3698745");
    BigReal num2("254789631.3698747"); // Initialize using string
    BigReal num3("-632145269.3698745");
    BigReal num4("-254789631.3698747"); // Initialize using string
    BigReal num5("50000000.555");
    BigReal num6("-3.0");
    // Test addition operator +
    BigReal sum1 = num1 + num2;
    std::cout << "Addition result: " << sum1 << std::endl;

    BigReal sum2 = num1 + num3;
    std::cout << "Addition result: " << sum2 << std::endl;

    BigReal sum3 = num5 + num6;
    std::cout << "Addition result: " << sum3 << std::endl;

    // Test subtraction operator -
    BigReal diff1 = num1 - num2;
    std::cout << "Subtraction result: " << diff1 << std::endl;

    BigReal diff2 = num1 - num4;
    std::cout << "Subtraction result: " << diff2 << std::endl;

    BigReal diff3 = num4 - num1;
    std::cout << "Subtraction result: " << diff3 << std::endl;

    // Test less than operator <
    bool isLess = num1 < num2;
    std::cout << "Less than: " << isLess << std::endl;

    // Test greater than operator >
    bool isGreater = num1 > num2;
    std::cout << "Greater than: " << isGreater << std::endl;

    // Test equality operator ==
    bool isEqual = num5 == num6;
    std::cout << "Equality: " << isEqual << std::endl;

    // Test isValid for valid numbers
    bool isValid1 = num1.isValid("632145269.3698745");
    std::cout << "isValid for num1: " << isValid1 << std::endl;

    bool isValid2 = num2.isValid("+ 254789631.3698747");
    std::cout << "isValid for invalid: " << isValid2 << std::endl;

    // Test isValid for invalid numbers
    bool isValid3 = num1.isValid("abc"); // Invalid input
    std::cout << "isValid for invalid input: " << isValid3 << std::endl;

    bool isValid4 = num2.isValid("1.2.3"); // Invalid input
    std::cout << "isValid for invalid input: " << isValid4 << std::endl;

    return 0;
}