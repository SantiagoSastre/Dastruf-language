#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "token_type.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "dastruf.hpp"


//-----------------------------------------Private-----------------------------------------------------
void Dastruf::run(const std::string &source) {
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.scan_tokens();
    for (Token token : tokens)
    {
        std::cout << token.to_string() << std::endl;
    }

}
bool Dastruf::had_error = false;
    //-----------------------------------------Public-----------------------------------------------------
void Dastruf::run_file(std::string path) {
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
void Dastruf::run_prompt() {
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
void Dastruf::error(int line, const std::string &message) {
    had_error = true;
    std::cerr << "[line " << line << "] Error" <<  ": " << message << "\n";
}






