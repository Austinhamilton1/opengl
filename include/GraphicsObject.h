#pragma once

#include "Types.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>
#include <glm/glm.hpp>

namespace gl {
    class GraphicsObject {
    private:
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<Shader> shader;
        std::vector<std::function<void(GraphicsObject *)>> renderCallbacks;

        glm::mat4 referenceFrame;

    public:
        GraphicsObject() : vertexBuffer(nullptr), shader(nullptr), referenceFrame(1.0f) {};
        ~GraphicsObject() {};

        //mutators
        void setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) { this->vertexBuffer = vertexBuffer; };
        void setShader(std::shared_ptr<Shader> shader) { this->shader = shader; };

        //accessors
        std::shared_ptr<VertexBuffer> getVertexBuffer() { return vertexBuffer; };
        std::shared_ptr<Shader> getShader() { return shader; };
        glm::mat4 getReferenceFrame() { return referenceFrame; };

        void addCallback(std::function<void(GraphicsObject *)> callback);
        void allocateBuffers();

        //transformations
        void transform(glm::mat4 transformation);
        void translate(glm::vec3 translation);
        void rotate(float radians, glm::vec3 axis);
        void scale(glm::vec3 scaleFactor);

        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

        void render();
    };
}