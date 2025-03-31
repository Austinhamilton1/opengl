#include "Shader.h"

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>

//clean up
gl::Shader::~Shader() {
    glDeleteProgram(program);
}

//read the data from a file into a string
static std::string readFile(std::string filename) {
    std::ifstream inputFile(filename); //open the file for reading
    std::string data;

    if(inputFile.is_open()) {
        std::string line;
        while(std::getline(inputFile, line))
            data += line + "\n"; //add each line to the data string
        inputFile.close(); //close the file
    }

    return data; //return the data in the file
}

//read in the source for the vertex shader from a file
int gl::Shader::setVertexSource(std::string filename) {
    vertexSource = readFile(filename);
    
    //signifies error in reading file or empty file
    if(vertexSource.empty())
        return -1;
    return 0;
}

//read in the source for the fragment shader from a file
int gl::Shader::setFragmentSource(std::string filename) {
    fragmentSource = readFile(filename);

    //signifies error in reading file or empty file
    if(fragmentSource.empty())
        return -1;
    return 0;
}

//compile the shader program with the vertex shader and fragment shader
gl::CompileResult gl::Shader::compile() {
    //temporarily create the vertex and fragment shaders
    unsigned int vertexShader, fragmentShader;

    //create the vertex shader and compile it
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexSourceString = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceString, NULL);
    glCompileShader(vertexShader);

    //check for errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        return VERTEX_COMPILATION_ERROR;
    }

    //create the fragment shader and compile it
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentSourceString = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceString, NULL);
    glCompileShader(fragmentShader);

    //check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glDeleteShader(vertexShader);
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        return FRAGMENT_COMPILATION_ERROR;
    }

    //create and link the shader program
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    //check for errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        return PROGRAM_LINK_ERROR;
    }

    //clean up unnecessary shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return SUCCESS;
}

void gl::Shader::use() {
    glUseProgram(program);
}