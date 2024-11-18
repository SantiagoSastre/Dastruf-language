#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "token_type.hpp"
#include "token.hpp"
#include "lexer.hpp"

namespace Dastruf {
    //-----------------------------------------Private-----------------------------------------------------
    void run(const std::string &source) {
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.scan_tokens();
        for (Token token : tokens)
        {
            std::cout << token.to_string() << std::endl;
        }

    }
    bool had_error = false;
     //-----------------------------------------Public-----------------------------------------------------
    void run_file(std::string path) {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file)
        {
            std::cerr << "Error: Could not open file " << path << std::endl;
            exit(65);
        }
        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        file.close();
        run(content);
        if (had_error)
                exit(65);
        }
    void run_prompt() {
        std::cout << "Dastruf v0.0.1\n";
        std::string line;
         while (true)
        {
            std::cout << ">";
            if (!std::getline(std::cin, line))
            {

                break;
            }

            run(line);
            had_error = false;
        }
    }
    void error(int line, const std::string &message) {
        had_error = true;
        std::cerr << "[line " << line << "] Error" <<  ": " << message << "\n";
    }


}




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