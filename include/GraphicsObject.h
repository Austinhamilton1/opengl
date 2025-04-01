#pragma once

#include "Types.h"
#include "VertexBuffer.h"
#include "Shader.h"

#include <memory>
#include <vector>
#include <functional>

namespace gl {
    class GraphicsObject {
    private:
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<Shader> shader;
        std::vector<std::function<void(GraphicsObject *)>> renderCallbacks;

    public:
        GraphicsObject() : vertexBuffer(nullptr), shader(nullptr) {};
        ~GraphicsObject() {};

        //mutators
        void setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) { this->vertexBuffer = vertexBuffer; };
        void setShader(std::shared_ptr<Shader> shader) { this->shader = shader; };
        
        //accessors
        std::shared_ptr<VertexBuffer> getVertexBuffer() { return vertexBuffer; };
        std::shared_ptr<Shader> getShader() { return shader; };

        void addCallback(std::function<void(GraphicsObject *)> callback);

        void render();
    };
}