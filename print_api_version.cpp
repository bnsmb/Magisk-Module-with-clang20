#include <iostream>  // include the input-output stream library

// Macros to convert the macro value to a string
#define STR(x) #x
#define XSTR(x) STR(x)

int main() {
    std::cout << "__ANDROID_API__ = " << XSTR(__ANDROID_API__) << std::endl;								   
    return 0;  // indicate successful completion of the program
}


