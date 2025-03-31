#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Types.h"
#include "Environment.h"
#include "Shader.h"

#include <iostream>

int main(int argc, char *argv[]) {

    gl::Environment env(800, 600);
    env.render();
    return 0;

    //rectangle vertices
    float firstVertices[] = {
        //first rectangle
        0.0f, 1.0f, 0.0f, //top right
        0.0f, 0.0f, 0.0f, //bottom right
        -1.0f, 0.0f, 0.0f, //bottom left
        -1.0f, 1.0f, 0.0f //top left
    };

    //rectangle vertices
    float secondVertices[] = {
        1.0f, 0.0f, 0.0f, //top right
        1.0f, -1.0f, 0.0f, //bottom right
        0.0f, -1.0f, 0.0f, //bottom left
        0.0f, 0.0f, 0.0f //top left
    };

    //rectangle indices
    unsigned int indices[] = {
        0, 1, 3, //first triangle
        1, 2, 3 //second triangle
    };

    //vertex objects
    unsigned int VAOs[2], VBOs[2], EBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);

    //bind the first object
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    //bind the second object
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    //create the shader
    gl::Shader shader;
    if(shader.setVertexSource("shaders/basic.vert.glsl") < 0) {
        std::cout << "Could not read vertex shader" << std::endl;
        return -1;
    }
    if(shader.setFragmentSource("shaders/basic.frag.glsl") < 0) {
        std::cout << "Could not read fragment shader" << std::endl;
        return -1;
    }
    
    //compile the shader
    gl::CompileResult result = shader.compile();
    if(result != gl::SUCCESS) {
        std::cout << "Could not compile shader" << std::endl;
        std::cout << shader.getInfoLog() << std::endl;
        return -1;
    }

    return 0;
}