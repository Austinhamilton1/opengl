#pragma once

#include "Types.h"

#include <string>

namespace gl {
    class Shader {
    private:
        unsigned int program;
        std::string vertexSource, fragmentSource;
        
        int success;
        char infoLog[512];

    public:
        Shader() {};
        ~Shader();

        int setVertexSource(std::string filename);
        int setFragmentSource(std::string filename);
        CompileResult compile();
        void use();

        std::string getInfoLog() { return std::string(infoLog); };
    };
}