#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <math.h>
#include <iostream>

#include "Types.h"
#include "Scene.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Environment.h"
#include "Texture.h"
#include "Renderer.h"

int main(int argc, char *argv[]) {
    //create the environment
    gl::Environment env(800, 600);

    //scene with a single triangle
    std::shared_ptr<gl::Scene> rectangleScene = std::make_shared<gl::Scene>();
    
    //create the textures
    std::shared_ptr<gl::Texture> crateTexture = std::make_shared<gl::Texture>(gl::REPEAT, gl::LINEAR);
    crateTexture->loadImage("textures/container.jpg", gl::RGB, gl::RGB);
    std::shared_ptr<gl::Texture> faceTexture = std::make_shared<gl::Texture>(gl::REPEAT, gl::LINEAR);
    faceTexture->loadImage("textures/awesomeface.png", gl::RGB, gl::RGBA);

    //generate the vertices
    std::shared_ptr<gl::VertexBuffer> vertices = std::make_shared<gl::VertexBuffer>(gl::STATIC);
    vertices->addData(8, 8, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f); //top right
    vertices->addData(8, 8, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f); //bottom right
    vertices->addData(8, 8, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f); //bottom left
    //vertices->addData(8, 8, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f); //top right
    //vertices->addData(8, 8, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f); //bottom left
    vertices->addData(8, 8, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f); //top left
    vertices->setLayout(0, 3, 8 * sizeof(float), 0);
    vertices->setLayout(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    vertices->setLayout(2, 2, 8 * sizeof(float), 6 * sizeof(float));
    vertices->setTexture(0, crateTexture);
    vertices->setTexture(1, faceTexture);

    std::shared_ptr<gl::IndexBuffer> indexes = std::make_shared<gl::IndexBuffer>(gl::STATIC);
    indexes->addData(3, 0, 1, 2);
    indexes->addData(3, 0, 2, 3);
    vertices->setIndexBuffer(indexes);

    //create the shader
    std::shared_ptr<gl::Shader> shader = std::make_shared<gl::Shader>();
    shader->setVertexSource("shaders/transform.vert.glsl");
    shader->setFragmentSource("shaders/texture.frag.glsl");
    shader->compile();
    shader->sendScalar<int>("texture1", 0);
    shader->sendScalar<int>("texture2", 1);

    //create the spinner object and add it to the scene
    std::shared_ptr<gl::GraphicsObject> spinner = std::make_shared<gl::GraphicsObject>();
    spinner->setVertexBuffer(vertices);
    rectangleScene->set("spinner", spinner);

    //create the scaler object and add it to the scene
    std::shared_ptr<gl::GraphicsObject> scaler = std::make_shared<gl::GraphicsObject>();
    scaler->setVertexBuffer(vertices);
    rectangleScene->set("scaler", scaler);

    //spin the spinner
    spinner->addCallback([](gl::GraphicsObject *obj) {
        glm::mat4 transformation(1.0f);
        transformation = glm::translate(transformation, glm::vec3(0.5f, -0.5f, 0.0f));
        transformation = glm::rotate(transformation, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        obj->transform(transformation);
    });

    //scale the scaler
    scaler->addCallback([](gl::GraphicsObject *obj) {
        float scaleFactor = abs(sin((float)glfwGetTime()));
        glm::mat4 transformation(1.0f);
        transformation = glm::translate(transformation, glm::vec3(-0.5f, 0.5f, 0.0f));
        transformation = glm::scale(transformation, glm::vec3(scaleFactor, scaleFactor, 0.0f));
        obj->transform(transformation);
    });

    std::shared_ptr<gl::Renderer> renderer = std::make_shared<gl::Renderer>(shader);
    renderer->setScene(rectangleScene);
    
    //render the window
    env.addRenderer(renderer);
    env.render();
    return 0;
}