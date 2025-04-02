#pragma once

#include "Scene.h"
#include "Shader.h"
#include "GraphicsObject.h"
#include "Camera.h"

#include <memory>
#include <glm/glm.hpp>

namespace gl {
    class Renderer {
    private:
        unsigned int VAO;
        std::shared_ptr<Scene> scene;
        std::shared_ptr<Shader> shader;
        glm::mat4 view;
        glm::mat4 projection;
        
    public:
        Renderer(std::shared_ptr<Shader> shader);
        ~Renderer() {};

        void allocate();
        void renderObject(std::shared_ptr<GraphicsObject> object);
        void renderScene(std::shared_ptr<Camera> camera);
        void clear();

        void setScene(std::shared_ptr<Scene> scene) { this->scene = scene; };
        void setView(glm::mat4 view) { this->view = view; };
        void setProjection(glm::mat4 projection) { this->projection = projection; };
    };
}