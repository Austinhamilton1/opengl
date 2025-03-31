#pragma once

#include "Types.h"
#include "Buffer.h"
#include "Shader.h"

#include <memory>
#include <vector>

namespace gl {
    class GraphicsObject {
    private:
        std::shared_ptr<Buffer<float>> vertexBuffer;
        std::shared_ptr<Buffer<unsigned int>> indexBuffer;
        std::shared_ptr<Shader> shader;
        std::vector<void (*)(GraphicsObject *)> renderCallbacks;

    public:
        GraphicsObject() : vertexBuffer(nullptr), indexBuffer(nullptr), shader(nullptr) {};
        ~GraphicsObject() {};

        //mutators
        void setVertexBuffer(std::shared_ptr<Buffer<float>> vertexBuffer) { this->vertexBuffer = vertexBuffer; };
        void setIndexBuffer(std::shared_ptr<Buffer<unsigned int>> indexBuffer) { this->indexBuffer = indexBuffer; };
        void setShader(std::shared_ptr<Shader> shader) { this->shader = shader; };
        
        //accessors
        std::shared_ptr<Buffer<float>> getVertexBuffer() { return vertexBuffer; };
        std::shared_ptr<Buffer<unsigned int>> getIndexBuffer() { return indexBuffer; };
        std::shared_ptr<Shader> getShader() { return shader; };

        void addCallback(void (*callback)(GraphicsObject *));

        void render();
    };
}