#pragma once

#include "Types.h"

#include <string>
#include <vector>
#include <cstdarg>

namespace gl {
    class Shader {
    private:
        unsigned int program;
        std::string vertexSource, fragmentSource;
        
        int success;
        char infoLog[512];

    public:
        Shader() {};
        ~Shader() {};

        int setVertexSource(std::string filename);
        int setFragmentSource(std::string filename);
        CompileResult compile();
        void use();

        std::string getInfoLog() { return std::string(infoLog); };

        template<typename T> void sendScalar(std::string uniformName, T scalar);
        template<typename T> void sendVector(std::string uniformName, int elementSize, int count, ...);
        void sendMatrix(std::string uniformName, int x, int y, float *matrix);
    };

    //sends a float to the shader
    template<> inline void Shader::sendScalar<float>(std::string uniformName, float scalar) {
        int uniformLocation = glGetUniformLocation(program, uniformName.c_str());
        glUseProgram(program);
        glUniform1f(uniformLocation, scalar);
    }

    //sends an int to the shader
    template<> inline void Shader::sendScalar<int>(std::string uniformName, int scalar) {
        int uniformLocation = glGetUniformLocation(program, uniformName.c_str());
        glUseProgram(program);
        glUniform1i(uniformLocation, scalar);
    }

    //sends an unsigned int to the shader
    template<> inline void Shader::sendScalar<unsigned int>(std::string uniformName, unsigned int scalar) {
        int uniformLocation = glGetUniformLocation(program, uniformName.c_str());
        glUseProgram(program);
        glUniform1ui(uniformLocation, scalar);
    }

    //send a vector of floats to the shader
    template<> inline void Shader::sendVector<float>(std::string uniformName, int elementSize, int count, ...) {
        //make sure the number of values passed is valid
        if(count % elementSize != 0)
            return;
        
        //the data to send
        std::vector<float> data;
        
        //read in the arguments
        va_list args;
        va_start(args, count);
        for(int i = 0; i < count; i++) {
            double value = va_arg(args, double);
            data.push_back(static_cast<float>(value));
        }
        va_end(args);

        //get the uniform location and set the active program to this program
        int uniformLocation = glGetUniformLocation(program, uniformName.c_str());
        glUseProgram(program);

        //send the data to the shader
        int elementCount = count / elementSize;
        if(elementSize == 1)
            glUniform1fv(uniformLocation, elementCount, data.data());
        else if(elementSize == 2)
            glUniform2fv(uniformLocation, elementCount, data.data());
        else if(elementSize == 3)
            glUniform3fv(uniformLocation, elementCount, data.data());
        else if(elementSize == 4)
            glUniform4fv(uniformLocation, elementCount, data.data());
    }

    //send a vector of ints to the shader
    template<> inline void Shader::sendVector<int>(std::string uniformName, int elementSize, int count, ...) {
        //make sure the number of values passed is valid
        if(count % elementSize != 0)
            return;

        //the data to send
        std::vector<int> data;

        //read in the arguments
        va_list args;
        va_start(args, count);
        for(int i = 0; i < count; i++) {
            double value = va_arg(args, int);
            data.push_back(value);
        }
        va_end(args);

        //get the uniform location and set the active program to this program
        int uniformLocation = glGetUniformLocation(program, uniformName.c_str());
        glUseProgram(program);

        //send the data to the shader
        int elementCount = count / elementSize;
        if(elementSize == 1)
            glUniform1iv(uniformLocation, elementCount, data.data());
        else if(elementSize == 2)
            glUniform2iv(uniformLocation, elementCount, data.data());
        else if(elementSize == 3)
            glUniform3iv(uniformLocation, elementCount, data.data());
        else if(elementSize == 4)
            glUniform4iv(uniformLocation, elementCount, data.data());
    }

    //send a vector of unsigned ints to the shader
    template<> inline void Shader::sendVector<unsigned int>(std::string uniformName, int elementSize, int count, ...) {
        //make sure the number of values passed is valid
        if(count % elementSize != 0)
            return;

        //the data to send
        std::vector<unsigned int> data;

        //read in the arguments
        va_list args;
        va_start(args, count);
        for(int i = 0; i < count; i++) {
            double value = va_arg(args, unsigned int);
            data.push_back(value);
        }
        va_end(args);

        //get the uniform location and set the active program to this program
        int uniformLocation = glGetUniformLocation(program, uniformName.c_str());
        glUseProgram(program);

        //send the data to the shader
        int elementCount = count / elementSize;
        if(elementSize == 1)
            glUniform1uiv(uniformLocation, elementCount, data.data());
        else if(elementSize == 2)
            glUniform2uiv(uniformLocation, elementCount, data.data());
        else if(elementSize == 3)
            glUniform3uiv(uniformLocation, elementCount, data.data());
        else if(elementSize == 4)
            glUniform4uiv(uniformLocation, elementCount, data.data());
    }

    //send a matrix of floats to the shader
    inline void Shader::sendMatrix(std::string uniformName, int x, int y, float *matrix) {
        //get the uniform location and set the active program to this program
        int uniformLocation = glGetUniformLocation(program, uniformName.c_str());
        glUseProgram(program);

        if(x == 2 && y == 2)
            glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 2 && y == 3)
            glUniformMatrix2x3fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 2 && y == 4)
            glUniformMatrix2x4fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 3 && y == 2)
            glUniformMatrix3x2fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 3 && y == 3)
            glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 3 && y == 4)
            glUniformMatrix3x4fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 4 && y == 2)
            glUniformMatrix4x2fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 4 && y == 3)
            glUniformMatrix4x3fv(uniformLocation, 1, GL_FALSE, matrix);
        if(x == 4 && y == 4)
            glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, matrix);
    }
}