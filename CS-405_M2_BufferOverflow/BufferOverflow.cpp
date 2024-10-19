// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

#include <cstring>  // For strlen
#include <limits>   // For std::numeric_limits

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    const std::string account_number = "CharlieBrown42";
    char user_input[20];
    bool input_valid = false;

    // Loop until valid input is received (less than 19 characters)
    while (!input_valid)
    {
        std::cout << "Enter a value (max 19 characters): ";

        // Use std::cin.getline() to safely handle user input and avoid overflow, cin was not working correctly.
        std::cin.getline(user_input, sizeof(user_input));

        // Check if the input failed (indicating that too many characters were entered)
        if (std::cin.fail())
        {
            std::cin.clear(); // Clear the error flag
            /* Credit to: https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n */
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the rest of the input
            std::cout << "Warning: Input was too long. Please enter 19 characters or less." << std::endl;
        }
        else
        {
            input_valid = true;  // Valid input was entered
        }
    }

    // Display the valid input and the account number
    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;

    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

void f(signed int si_a, signed int si_b) {
    signed int sum;
    if (((si_b > 0) && (si_a > (INT_MAX - si_b))) ||
        ((si_b < 0) && (si_a < (INT_MIN - si_b)))) {
        /* Handle error */
    }
    else {
        sum = si_a + si_b;
    }
    /* ... */
}