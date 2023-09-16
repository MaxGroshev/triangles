#include <iostream>

int func () {
    int var = 7;
    switch (var) {
        case 1:
            std::cout << "Hello\n";
            break;
        // default:
        //     std::cout << "Hell\n";
    }

    std::cout << "Hello\n";
}

int main () {
    std::cout << "Hello\n";
    func ();
    // return 0;
}


