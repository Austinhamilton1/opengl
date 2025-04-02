#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <math.h>
#include <random>

#include "Types.h"
#include "Scene.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Environment.h"
#include "Texture.h"
#include "Renderer.h"
#include "Generate.h"

float elapsedTime;

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

int main(int argc, char *argv[]) {
    //create the environment
    gl::Environment env(800, 600);

    //scene with a single triangle
    auto scene = std::make_shared<gl::Scene>();
    auto camera = std::make_shared<gl::Camera>();
    camera->setSpeed(10.0f);
    camera->setTorque(2.0f);
    env.setCamera(camera);
    
    //create the textures
    auto crateTexture = std::make_shared<gl::Texture>(gl::REPEAT, gl::LINEAR);
    crateTexture->loadImage("textures/container.jpg", gl::RGB, gl::RGB);
    auto faceTexture = std::make_shared<gl::Texture>(gl::REPEAT, gl::LINEAR);
    faceTexture->loadImage("textures/awesomeface.png", gl::RGB, gl::RGBA);

    //generate the vertices
    auto vertices = gl::Generate::cube(10, 10, 10, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
    vertices->setTexture(0, crateTexture);
    vertices->setTexture(1, faceTexture);

    //create the shader
    auto shader = std::make_shared<gl::Shader>();
    shader->setVertexSource("shaders/3d.vert.glsl");
    shader->setFragmentSource("shaders/texture.frag.glsl");
    shader->compile();
    shader->sendScalar<int>("texture1", 0);
    shader->sendScalar<int>("texture2", 1);

    //create 10 spinning cubes
    std::vector<std::shared_ptr<gl::GraphicsObject>> spinners;
    for(int i = 0; i < 10; i++) {
        auto spinner = std::make_shared<gl::GraphicsObject>();
        spinner->setVertexBuffer(vertices);

        //set the spinner in a random location
        spinner->setPosition(glm::vec3(randomFloat(-20.0f, 20.0f), randomFloat(-20.0f, 20.f), randomFloat(-20.0f, 0.0f)));

        //add the object to the scene
        std::string key = "spinner_" + i;
        scene->set(key, spinner);

        //add a callback to the object to make it spin
        spinner->addCallback([](gl::GraphicsObject *obj) {
            obj->rotate(elapsedTime * glm::radians(50.0f), glm::vec3(0.5, 1.0f, 0.0f));
        });
    }

    auto renderer = std::make_shared<gl::Renderer>(shader);
    renderer->setScene(scene);

    env.addCallback([](gl::Environment *env) {
        elapsedTime = env->getClock().elapsedTime;
    });
    
    //render the window
    env.addRenderer(renderer);
    env.render();
    return 0;
}