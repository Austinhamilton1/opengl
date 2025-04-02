#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>

#include "Camera.h"
#include "Renderer.h"

namespace gl {
    struct Timer {
        float currentTime, lastTime, elapsedTime;
        Timer() : currentTime(0), lastTime(0), elapsedTime(0) {};
        void tick() {
            lastTime = currentTime;
            currentTime = (float)glfwGetTime();
            elapsedTime = currentTime - lastTime;
        }
    };

    class Environment {
    private:
        GLFWwindow *window;
        int width, height;
        Timer clock;
        std::shared_ptr<Camera> camera;
        std::vector<std::shared_ptr<Renderer>> renderers;
        std::vector<std::function<void(Environment *)>> renderCallbacks;
        static Environment *self;

    public:
        Environment(int width, int height);
        ~Environment();
        
        inline std::vector<std::shared_ptr<Renderer>> getRenderers() { return renderers; };
        inline GLFWwindow *getWindow() { return window; };

        void processInput();
        void addRenderer(std::shared_ptr<Renderer> renderer);

        void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; };
        std::shared_ptr<Camera> getCamera() { return camera; };
        void setWidth(int width) { this->width = width; };
        void setHeight(int height) { this->height = height; };
        Timer getClock() { return clock; };

        void addCallback(std::function<void(Environment *)>);
        void setup();
        void render();

        static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    };
}
