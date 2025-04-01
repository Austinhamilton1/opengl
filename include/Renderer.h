#pragma once

#include "Scene.h"
#include "Shader.h"
#include "GraphicsObject.h"

#include <memory>

namespace gl {
    class Renderer {
    private:
        unsigned int VAO;
        std::shared_ptr<Scene> scene;
        std::shared_ptr<Shader> shader;
        
    public:
        Renderer(std::shared_ptr<Shader> shader);
        ~Renderer() {};

        void allocate();
        void renderObject(std::shared_ptr<GraphicsObject> object);
        void renderScene();
        void clear();

        void setScene(std::shared_ptr<Scene> scene) { this->scene = scene; };
    };
}