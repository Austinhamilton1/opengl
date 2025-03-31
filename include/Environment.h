#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gl {
    class Environment {
    private:
        GLFWwindow *window;

    public:
        Environment(int width, int height);
        ~Environment();

        void processInput();
        void render();
        
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    };
}
