#include "Environment.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    glfwTerminate();
}

//process keyboard/mouse input
void gl::Environment::processInput() {
    //exit the window if the user presses the ESC key
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//render loop
void gl::Environment::render() {
    while(!glfwWindowShouldClose(window)) {
        //input
        processInput();

        //swap the buffers and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}