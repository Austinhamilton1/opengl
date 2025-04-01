#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>

#include "Renderer.h"

namespace gl {
    class Environment {
    private:
        GLFWwindow *window;
        std::vector<std::shared_ptr<Renderer>> renderers;
        std::vector<std::function<void(Environment *)>> renderCallbacks;

    public:
        Environment(int width, int height);
        ~Environment();
        
        inline std::vector<std::shared_ptr<Renderer>> getRenderers() { return renderers; };
        inline GLFWwindow *getWindow() { return window; };

        void processInput();
        void addRenderer(std::shared_ptr<Renderer> renderer);

        void addCallback(std::function<void(Environment *)>);
        void setup();
        void render();
        
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    };
}
