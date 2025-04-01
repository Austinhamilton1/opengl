#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>

#include "Scene.h"

namespace gl {
    class Environment {
    private:
        GLFWwindow *window;
        std::vector<std::shared_ptr<Scene>> scenes;
        std::vector<std::function<void(Environment *)>> renderCallbacks;

    public:
        Environment(int width, int height);
        ~Environment();
        
        inline std::vector<std::shared_ptr<Scene>> getScenes() { return scenes; };

        void processInput();
        void addScene(std::shared_ptr<Scene> scene);
        void addCallback(std::function<void(Environment *)>);
        void setup();
        void render();
        
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    };
}
