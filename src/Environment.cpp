#include "Environment.h"
#include "Shader.h"
#include "Buffer.h"
#include "GraphicsObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

gl::Environment::Environment(int width, int height) {
    //initialize the environment
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window and set the current context to the window
    window = glfwCreateWindow(width, height, "Graphics Window", NULL, NULL);
    if(window == NULL) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    //initialize glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return;
    }

    //set the data display/coordinates setting
    glViewport(0, 0, width, height);

    //update the viewport when the window is resized
    glfwSetFramebufferSizeCallback(window, gl::Environment::framebuffer_size_callback);
}

//clean up
gl::Environment::~Environment() {
    //explicitly delete all the scenes
    //so that when we delete objects, the context is still valid
    for(const auto& scene : scenes) {
        scene->~Scene();
    }

    glfwTerminate();
}

//process keyboard/mouse input
void gl::Environment::processInput() {
    //exit the window if the user presses the ESC key
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//add a scene to the environment
void gl::Environment::addScene(std::shared_ptr<gl::Scene> scene) {
    scenes.push_back(scene);
}

//add a render callback to the environment
void gl::Environment::addCallback(void (*callback)(Environment *)) {
    renderCallbacks.push_back(callback);
}

//render loop
void gl::Environment::render() {
    while(!glfwWindowShouldClose(window)) {
        //input
        processInput();

        //clear the screen with a greenish color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //run any render callbacks that need to be run
        for(auto& callback : renderCallbacks)
            callback(this);

        //render all scenes in the environment
        for(auto& scene : scenes)
            scene->render();

        //swap the buffers and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}