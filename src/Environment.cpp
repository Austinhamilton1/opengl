#include "Environment.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

gl::Environment *gl::Environment::self;

void gl::Environment::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    self->width = width;
    self->height = height;
}

gl::Environment::Environment(int width, int height) {
    self = this;
    
    //initialize the environment
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //set the width and height of the environment
    this->width = width;
    this->height = height;

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
    
    //enable z-buffer depth testing
    glEnable(GL_DEPTH_TEST);

    //update the viewport when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //set input for mouse scrolling
    glfwSetScrollCallback(window, scroll_callback);
}

//clean up
gl::Environment::~Environment() {
    //explicitly delete all the scenes
    //so that when we delete objects, the context is still valid
    for(auto renderer : renderers) {
        renderer->clear();
    }

    glfwTerminate();
}

//process keyboard/mouse input
void gl::Environment::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera->moveLeft(clock.elapsedTime);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera->moveRight(clock.elapsedTime);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera->moveUp(clock.elapsedTime);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->moveDown(clock.elapsedTime);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->rotateUp(clock.elapsedTime);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->rotateDown(clock.elapsedTime);
		return;
	}
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->rotateLeft(clock.elapsedTime);
        return;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->rotateRight(clock.elapsedTime);
        return;
    }
}

void gl::Environment::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(yoffset > 0) {
        self->camera->moveForward(25 * self->clock.elapsedTime);
        return;
    }
    if(yoffset < 0) {
        self->camera->moveBackwards(25 * self->clock.elapsedTime);
        return;
    }
}

//add a scene to the environment
void gl::Environment::addRenderer(std::shared_ptr<gl::Renderer> renderer) {
    renderers.push_back(renderer);
}

//add a render callback to the environment
void gl::Environment::addCallback(std::function<void(Environment *)> callback) {
    renderCallbacks.push_back(callback);
}

//render loop
void gl::Environment::render() {
    float left = -20.0f;
    float right = 20.0f;
    float bottom = -20.0f;
    float top = 20.0f;

    float aspectRatio;
    float nearPlane = 1.0f;
    float farPlane = 100.0f;
    float fieldOfView = 60.0f;

    camera->setPosition(glm::vec3(0.0f, 5.0f, 20.0f));
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 referenceFrame(1.0f);
    
    //allocate anything in the renderers
    for(auto renderer : renderers) {
        renderer->allocate();
    }

    while(!glfwWindowShouldClose(window)) {
        //advance the clock
        clock.tick();

        //input
        processInput();

        //clear the screen with a greenish color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = camera->lookForward();
        if(width >= height)
            aspectRatio = (float)width / (height * 1.0f);
        else
            aspectRatio = (float)height / (width * 1.0f);
        projection = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

        //render all scenes in the environment
        for(auto& renderer : renderers) {
            renderer->setView(view);
            renderer->setProjection(projection);
            renderer->renderScene(camera);
        }
        
        //run any render callbacks that need to be run
        for(auto& callback : renderCallbacks)
            callback(this);

        //swap the buffers and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}