#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <math.h>

#include "Types.h"
#include "Scene.h"
#include "Buffer.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Environment.h"

void sinTriangleCallback(gl::GraphicsObject *triangle) {
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    auto shader = triangle->getShader();
    shader->sendVector<float>("ourColor", 4, 4, 0.0f, greenValue, 0.0f, 1.0f);
}

int main(int argc, char *argv[]) {
    //create the environment
    gl::Environment env(800, 600);

    //scene with a single triangle
    std::shared_ptr<gl::Scene> rectangleScene = std::make_shared<gl::Scene>();
    
    //generate the vertices
    std::shared_ptr<gl::Buffer<float>> vertices = std::make_shared<gl::Buffer<float>>(gl::VERTEX, gl::STATIC);
    vertices->addData(6, 6, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f); //top right
    vertices->addData(6, 6, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f); //bottom right
    vertices->addData(6, 6, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f); //bottom left
    vertices->addData(6, 6, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f); //top left
    vertices->sendData();
    vertices->setLayout(0, 3, 6 * sizeof(float), 0);
    vertices->setLayout(1, 3, 6 * sizeof(float), 3 * sizeof(float));

    std::shared_ptr<gl::Buffer<unsigned int>> indexes = std::make_shared<gl::Buffer<unsigned int>>(vertices->getVAO(), gl::INDEX, gl::STATIC);
    indexes->addData(1, 3, 0, 1, 2);
    indexes->addData(1, 3, 0, 2, 3);
    indexes->sendData();

    //create the shader
    std::shared_ptr<gl::Shader> shader = std::make_shared<gl::Shader>();
    shader->setVertexSource("shaders/basic.vert.glsl");
    shader->setFragmentSource("shaders/basic.frag.glsl");
    shader->compile();

    //create the triangle object and add it to the scene
    std::shared_ptr<gl::GraphicsObject> rectangle = std::make_shared<gl::GraphicsObject>();
    rectangle->setVertexBuffer(vertices);
    rectangle->setIndexBuffer(indexes);
    rectangle->setShader(shader);
    rectangleScene->set("rectangle", rectangle);

    env.addScene(rectangleScene);
    env.render();
    return 0;
}