#include "dastruf.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Usage: Dastruf [script]\n";
        exit(64);
    }
    else if (argc == 2) {
        Dastruf::run_file(argv[1]);
    }
    else {
        Dastruf::run_prompt();
    }
    return 0;
};