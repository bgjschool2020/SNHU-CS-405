// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>


class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Application Logic Exception Occurred. ";
    }
};

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;

    // Throw any standard exception
    throw std::runtime_error("Application Logic Error");

    return true;
}

void do_custom_application_logic()
{
    // Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    } 
    catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    }
    

    // Throw a custom exception derived from std::exception
    //  and catch it explicitly in main
    std::cout << "Leaving Custom Application Logic." << std::endl;
    throw CustomException();


}

float divide(float num, float den)
{
    // Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) {
        throw std::invalid_argument("Error: Division by zero");
    }

    return (num / den);
}

void do_division() noexcept
{
    //  create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Division exception caught: " << e.what() << std::endl;
    }
}

int main()
{
    try {
    std::cout << "Exceptions Tests!" << std::endl;

    // Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.
    do_division();
    do_custom_application_logic();

    }
    catch (const CustomException& e) {
        std::cerr << "Runtime exception caught in main(): " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Standard exception caught in main(): " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught in main(). " << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu