#ifndef DASTRUF_HPP
#define DASTRUF_HPP

#include <string>


namespace Dastruf {

    void run(const std::string &source);

    void run_file(std::string path);

    void run_prompt();

    void error(int line, const std::string &message);

    extern bool had_error;

}

#endif